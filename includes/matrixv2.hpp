/*  
	Boost Competency Test (Gsoc '17)
	Author : Rishabh Arora
	Institute: IIIT Hyderabad
*/

/**
  * Uses expression templates for Matrix operations like + and *
  *Lazy / delayed evaluation of expressions
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

template <class T>
class Matrix : public Expression < Matrix < T > >{
private:
	size_t row_size, col_size;
	std::vector< std::vector < T > > mat;

public:
	Matrix ();
	Matrix (const size_t r_s, const size_t c_s);
	Matrix (const Matrix<T> &M);
	Matrix (Matrix<T> &&M);

	template <class T>
	inline Matrix<T>& operator = (const Expression<T>& _x);
	template <class T>
	inline void operator += (const Expression<T>& _x);

	T getVal(size_t row,size_t col);
	T setVal(const size_t row, const size_t col, const T value);
	size_t getRowSize();
	size_t getColSize();
	std::vector<std::vector < T > > Eval () const;

	~Matrix();
};
	

class add{
public: 
  template < class T>
  inline static std::vector < std::vector < T> > op(std::vector < std::vector < T> > a, std::vector < std::vector < T> > b) {
    
    // Lambda for matrix addition and dimension check

    auto Mat_add = [](auto a, auto b){ 
	    std::vector < std::vector < T > > X;
	    if (a.size() != b.size() || a[0].size() != b[0].size()) {
	    	std::cerr << "Invalid Operation: Incompatible dimensions for Matrix Addition" << std::endl;
	    	return X;
	    }
	   	X.resize(a.size());
	   	for (size_t i = 0; i < a.size(); i++) {
	   		X[i].resize(a[0].size());
	   	}
	   	for (size_t i = 0; i < a.size(); i++) {
	   		for(size_t j = 0; j < a[0].size(); j++) {
	   			X[i][j] = a[i][j] + b[i][j];
	    	}
	   	}
		return X;
	};

	return Mat_add(a, b);
  }
};

class mul{
public: 
  template < class T>
  inline static std::vector < std::vector < T> > op(std::vector < std::vector < T> > a, std::vector < std::vector < T> > b) {
    
    // Lambda for multiplicatoin tadded
    auto Mat_mul = [](auto a, auto b) {
	    std::vector < std::vector < T > > X;
	    /* Dimension Check */
	    if (a[0].size() != b.size()) {
	    	std::cerr << "Invalid Operation: Incompatible dimensions for Matrix Multiplication" << std::endl;
	    	return X;
	    }

	   	X.resize(a.size());
	   	for (size_t i = 0; i < a.size(); i++) {
	   		X[i].resize(b[0].size());
	   	}
			
	   	for (size_t i = 0; i < a.size(); i++) {
		    for (size_t j = 0; j < b[0].size(); j++) {
			    X[i][j] = 0;
	            for (size_t k = 0; k < a.size(); k++)
	                X[i][j] += a[i][k] * b[k][j];
	        }
	    }

		return X;
	};
	return Mat_mul(a, b);
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

template <class T>
template <class T>
inline Matrix<T>& Matrix<T>::operator = (const Expression<T>& _x) {
	const T& x = _x.self();
    mat = x.Eval();
    return *this;
}

/* Operator for += in Matrices */
template <class T>
template <class T>
inline void Matrix<T>::operator += (const Expression<T>& _x) {
	
	const T& x = _x.self();
    std::vector<std::vector<T> > X = x.Eval();
    

    for (size_t i = 0; i < row_size; i++) {
    	for(size_t j = 0; j < col_size; j++){
    		mat[i][j] += X[i][j];
    	}    
    }

    return;
}

/* constructor declarations */
/* empty matrix initialised */
template <class T>
Matrix<T>::Matrix () {
	row_size = col_size = 0;
}

/*
	set the dimensions of the matrix 
	all values are set to 0
*/
template <class T>
Matrix<T>::Matrix (const size_t r_s, const size_t c_s) {
	row_size = r_s;
	col_size = c_s;
	mat.resize(row_size);
	for(size_t i = 0; i < row_size; i++) {
		mat[i].resize(col_size);
	}
}
/* 
	copy constructor 
	deepcopy performed
	Additional time of O(row*col) used
*/
template <class T> 
Matrix<T>::Matrix (const Matrix<T> &M)  {
	row_size = M.row_size;
	col_size = M.col_size;
	mat.resize(row_size);
	for(size_t i = 0; i < row_size; i++) {
		mat[i].resize(col_size);
	}
	for(size_t i = 0; i < row_size; i++) {
		for(size_t j = 0; j < col_size; j++) {
			mat[i][j] = M.mat[i][j];
		}
	}	 
}

/* destructor declaration */
template <class T> 
Matrix<T>::~Matrix () {
	mat.clear();
} 

/* Matrix: Class functions */
template <class T>
T Matrix<T>::getVal(const size_t row, const size_t col) {
	return mat[row][col];
}  
template <class T>
T Matrix<T>::setVal(const size_t row, const size_t col, const T value) {
	return mat[row][col] = value;
}
template <class T>
size_t Matrix<T>::getRowSize() {
	return row_size;
}
template <class T>
size_t Matrix<T>::getColSize() {
	return col_size;
}
template <class T>
std::vector<std::vector < T> > Matrix<T>::Eval() const {
	return mat;
}

#endif