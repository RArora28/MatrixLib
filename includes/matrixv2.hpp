/*  
	Boost Competency Test (Gsoc '17)
	Author : Rishabh Arora
	Institute: IIIT Hyderabad
*/

/*
	Uses expression templates for Matrix operations like + and *
*/

#ifndef _TEMP_HPP
#define _TEMP_HPP

#include <vector>

template <class subType>
class Expression {
public:
	// returns const reference of the actual type of this expression 
	inline const subType &self(void) const {
		return *static_cast<const subType*>(this);
	} 
};

/* temperory class to store a pair of matrix and expression_to_be_evaluated */
template <class OP, class E1, class E2>
class BinaryOP: public Expression < BinaryOP < OP, E1, E2 > > {
public:
  const E1& l;
  const E2& r;

  BinaryOP(const E1& l, const E2& r): l(l), r(r) {}
 
  inline auto Eval() const {
    return OP::op(l.Eval(), r.Eval());
  }
};

template <class ElementType>
class Matrix : public Expression < Matrix < ElementType > >{
private:
	unsigned int row_size, col_size;
	std::vector< std::vector < ElementType > > mat;

public:
	Matrix ();
	Matrix (const unsigned int r_s, const unsigned int c_s);
	Matrix (const Matrix<ElementType> &M);
	Matrix (Matrix<ElementType> &&M);

	template <class T>
	inline Matrix<ElementType>& operator = (const Expression<T>& _x);
	template <class T>
	inline void operator += (const Expression<T>& _x);

	ElementType getVal(unsigned int row,unsigned int col);
	ElementType setVal(const unsigned int row, const unsigned int col, const ElementType value);
	unsigned int getRowSize();
	unsigned int getColSize();
	std::vector<std::vector < ElementType > > Eval () const;

	~Matrix();
};
	

class add{
public: 
  template < class T>
  inline static std::vector < std::vector < T> > op(std::vector < std::vector < T> > a, std::vector < std::vector < T> > b) {
    std::vector < std::vector < T > > X;
    /* Dimension Check */
    if (a.size() != b.size() || a[0].size() != b[0].size()) {
    	std::cerr << "Invalid Operation: Incompatible dimensions for Matrix Addition" << std::endl;
    	return X;
    }

   	X.resize(a.size());
   	for (unsigned int i = 0; i < a.size(); i++) {
   		X[i].resize(a[0].size());
   	}

   	for (unsigned int i = 0; i < a.size(); i++) {
   		for(unsigned int j = 0; j < a[0].size(); j++) {
   			X[i][j] = a[i][j] + b[i][j];
   		}
   	}
	return X;
  }
};

class mul{
public: 
  template < class T>
  inline static std::vector < std::vector < T> > op(std::vector < std::vector < T> > a, std::vector < std::vector < T> > b) {
    std::vector < std::vector < T > > X;
    /* Dimension Check */
    if (a[0].size() != b.size()) {
    	std::cerr << "Invalid Operation: Incompatible dimensions for Matrix Multiplication" << std::endl;
    	return X;
    }

   	X.resize(a.size());
   	for (unsigned int i = 0; i < a.size(); i++) {
   		X[i].resize(b[0].size());
   	}
		
   	for (unsigned int i = 0; i < a.size(); i++) {
	    for (unsigned int j = 0; j < b[0].size(); j++) {
		    X[i][j] = 0;
            for (unsigned int k = 0; k < a.size(); k++)
                X[i][j] += a[i][k] * b[k][j];
        }
    }

	return X;
  }
};

/* operations on the matrix class */
/* temporary class to generate the expression template for operation OP */
template <class OP, class E1, class E2 >
inline BinaryOP<OP, E1, E2> operate(const Expression<E1>& l, const Expression<E2>& r) {
  return BinaryOP<OP, E1, E2>(l.self(), r.self());
}

/* Addition operation overload */
template < class E1, class E2 >
inline BinaryOP<add, E1, E2> operator+ (const Expression<E1>& l, const Expression<E2>& r) {
  return operate<add>(l, r);
}

/* Multiply operation overload */
template < class E1, class E2 >
inline BinaryOP<mul, E1, E2> operator* (const Expression<E1>& l, const Expression<E2>& r) {
  return operate<mul>(l, r);
}

template <class ElementType>
template <class T>
inline Matrix<ElementType>& Matrix<ElementType>::operator = (const Expression<T>& _x) {
	const T& x = _x.self();
    mat = x.Eval();
    return *this;
}

template <class ElementType>
template <class T>
inline void Matrix<ElementType>::operator += (const Expression<T>& _x) {
	const T& x = _x.self();
    std::vector<std::vector<ElementType> > X = x.Eval();
    for (unsigned int i = 0; i < row_size; i++) {
    	for(unsigned int j = 0; j < col_size; j++){
    		mat[i][j] += X[i][j];
    	}    
    }

    return;
}




/* constructor declarations */
/* empty matrix initialised */
template <class ElementType>
Matrix<ElementType>::Matrix () {
	row_size = col_size = 0;
}

/*
	set the dimensions of the matrix 
	all values are set to 0
*/
template <class ElementType>
Matrix<ElementType>::Matrix (const unsigned int r_s, const unsigned int c_s) {
	row_size = r_s;
	col_size = c_s;
	mat.resize(row_size);
	for(unsigned int i = 0; i < row_size; i++) {
		mat[i].resize(col_size);
	}
}

/* 
	copy constructor 
	deepcopy performed
	Additional time of O(row*col) used
*/
template <class ElementType> 
Matrix<ElementType>::Matrix (const Matrix<ElementType> &M)  {
	row_size = M.row_size;
	col_size = M.col_size;
	mat.resize(row_size);
	for(unsigned int i = 0; i < row_size; i++) {
		mat[i].resize(col_size);
	}
	for(unsigned int i = 0; i < row_size; i++) {
		for(unsigned int j = 0; j < col_size; j++) {
			mat[i][j] = M.mat[i][j];
		}
	}	 
}

/* destructor declaration */
template <class ElementType> 
Matrix<ElementType>::~Matrix () {
	mat.clear();
} 

/* Matrix: Class functions */
template <class ElementType>
ElementType Matrix<ElementType>::getVal(const unsigned int row, const unsigned int col) {
	return mat[row][col];
}  
template <class ElementType>
ElementType Matrix<ElementType>::setVal(const unsigned int row, const unsigned int col, const ElementType value) {
	return mat[row][col] = value;
}
template <class ElementType>
unsigned int Matrix<ElementType>::getRowSize() {
	return row_size;
}
template <class ElementType>
unsigned int Matrix<ElementType>::getColSize() {
	return col_size;
}
template <class ElementType>
std::vector<std::vector < ElementType> > Matrix<ElementType>::Eval() const {
	return mat;
}

#endif