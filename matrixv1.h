#ifndef MATRIXV1_INCLUDE
#define MATRIXV1_INCLUDE

#include <vector>

template <class ElementType>
class Matrix {
private:
	unsigned int row_size, col_size;
	std::vector< std::vector <ElementType > > mat;

public:
	Matrix ();
	Matrix (const unsigned int r_s, const unsigned int c_s);
	Matrix (const Matrix<ElementType> &M);
	Matrix (Matrix<ElementType> &&M);

	Matrix<ElementType> &operator = (Matrix<ElementType> &&M);
	Matrix<ElementType> &operator = (Matrix<ElementType> &M);

	ElementType getVal(const unsigned int row, const unsigned int col);
	ElementType setVal(const unsigned int row, const unsigned int col, const ElementType value);
	unsigned int getRowSize();
	unsigned int getColSize();

	template <class ElType>
	friend Matrix<ElType> operator + (const Matrix<ElType> &M1, const Matrix<ElType> &M2);
	template <class ElType>
	friend Matrix<ElType> operator * (const Matrix<ElType> &M1, const Matrix<ElType> &M2);
	template <class ElType>
	friend void operator += (Matrix<ElType> &M1, const Matrix<ElType> &M2);
	template <class ElType>
	friend void operator *= (Matrix<ElType> &M1, const Matrix<ElType> &M2);
	
	~Matrix();
};

//constructor declarations
template <class ElementType>
Matrix<ElementType>::Matrix () {
	row_size = col_size = 0;
}

template <class ElementType>
Matrix<ElementType>::Matrix (const unsigned int r_s, const unsigned int c_s) {
	row_size = r_s;
	col_size = c_s;
	mat.resize(row_size);
	for(unsigned int i = 0; i < row_size; i++) {
		mat[i].resize(col_size);
	}
}

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

template <class ElementType> 
Matrix<ElementType>::Matrix (Matrix<ElementType> &&M)  {
	row_size = std::move(M.row_size);
	col_size = std::move(M.col_size);
	mat = std::move(M.mat);	 
}

//destructor declaration
template <class ElementType> 
Matrix<ElementType>::~Matrix () {
	mat.clear();
} 

//class functions
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

template<class ElementType>
Matrix<ElementType>& Matrix<ElementType>::operator = (Matrix<ElementType> &&M) {
    row_size = std::move(M.row_size);
    col_size = std::move(M.col_size);
    mat = std::move(M.mat);
    std::cout << "move assigned" << std::endl;
    return *this;
}

template<class ElementType>
Matrix<ElementType>& Matrix<ElementType>::operator = (Matrix<ElementType> &M) {
    row_size = M.row_size;
    col_size = M.col_size;
    for(unsigned int i = 0; i < row_size; i++) {
    	for(unsigned int j = 0; j < row_size; j++) {
    		mat[i][j] = M.mat[i][j];
    	}
    }
    return *this;
}

//friend functions
template <class ElementType>
Matrix<ElementType> operator+ (const Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	//to check wheter the matrices have same dimensions
	if(M1.row_size != M2.row_size || M1.col_size != M2.col_size) {
		std::cerr << "Failed: Invalid matrix dimensions for addition" << std::endl;
		return M1;
	}
	//alocating O(row*col) additional memory to find the resultant
	Matrix<ElementType> res(M1.row_size, M1.col_size);
	for(unsigned int i = 0; i < M1.row_size; i++) {
		for(unsigned int j = 0; j < M1.col_size; j++) {
			res.mat[i][j] = M1.mat[i][j] + M2.mat[i][j];
		}
	}
	return res;
}

template <class ElementType>
Matrix<ElementType> operator* (const Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	//to check if matrix multiplication is dimensionally possible
	if( M1.col_size != M2.row_size) {
		std::cerr << "Failed: Invalid matrix dimensions for multiplication" << std::endl;
		return M1;
	}
	//alocating O(row*col) additional memory to find the resultant
	//O(n^3) time complexity
	Matrix<ElementType> res(M1.row_size, M2.col_size);
	for (unsigned int i = 0; i < M1.row_size; i++) {
	    for (unsigned int j = 0; j < M2.col_size; j++) {
		    res.mat[i][j] = 0;
            for (unsigned int k = 0; k < M1.col_size; k++)
                res.mat[i][j] += M1.mat[i][k] * M2.mat[k][j];
        }
    }
    return res;
}

template <class ElementType>
void operator+= (Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	//to check wheter the matrices have same dimensions
	if(M1.row_size != M2.row_size || M1.col_size != M2.col_size) {
		std::cerr << "Failed: Invalid matrix dimensions for addition" << std::endl;
		return;
	}
	for(unsigned int i = 0; i < M1.row_size; i++) {
		for(unsigned int j = 0; j < M1.col_size; j++) {
			M1.mat[i][j] = M1.mat[i][j] + M2.mat[i][j];
		}
	}
	return;
}

template <class ElementType>
inline void operator*=(Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	//to check wheter the matrices have same dimensions
	if(M1.col_size != M2.row_size)
		return;
	//alocating O(row*col) additional memory to find the resultant
	Matrix<ElementType> res(M1.row_size, M2.col_size);
	for (unsigned int i = 0; i < M1.row_size; i++) {
	    for (unsigned int j = 0; j < M2.col_size; j++) {
		    res.mat[i][j] = 0;
            for (unsigned int k = 0; k < M1.col_size; k++)
                res.mat[i][j] += M1.mat[i][k] * M2.mat[k][j];
        }
    }
    
    unsigned int r = M1.row_size, c = M2.col_size;
    for(unsigned int i = 0; i < M1.row_size; i++) {
    	M1.mat[i].clear();
    }
    M1.mat.clear();

    M1.mat.resize(r);
    M1.row_size = r;
    M1.col_size = c;
    for(unsigned int i = 0; i < r; i++) {
    	M1.mat[i].resize(c);
    }
    
    for(unsigned int i = 0; i < M1.row_size; i++) {
    	for(unsigned int j = 0; j < M1.col_size; j++) {
    		M1.mat[i][j] = res.mat[i][j];
    	}
    }
	return;
}

template <class ElementType> 
ElementType trace(Matrix<ElementType> &M) {
	auto t = 0;
	if( M.getRowSize() != M.getColSize()) {
		std::cerr << "Trace not defined for non-square matrices" << std::endl;
		return 0;
	}
	for(unsigned int i = 0; i < M.getRowSize(); i++) {
		t += M.getVal(i, i);
	}
	return t;
}

#endif