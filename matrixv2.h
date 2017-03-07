#ifndef MATRIXV2_INCLUDE
#define MATRIXV2_INCLUDE

#include <vector>

template <class ElementType>
class Matrix;

template <class ElementType>
class BinaryAdd {
	public:
	const Matrix<ElementType> &l; 
	const Matrix<ElementType> &r;
	BinaryAdd(const Matrix<ElementType> &l, const Matrix<ElementType> &r) : l(l) ,r(r) {}
};

template <class ElementType>
class BinaryMult {
	public:
	const Matrix<ElementType> &l; 
	const Matrix<ElementType> &r;
	BinaryMult(const Matrix<ElementType> &l, const Matrix<ElementType> &r) : l(l) ,r(r) {}
};

template <class ElementType>
class Matrix {

	public:
	int row_size, col_size;
	std::vector< std::vector <ElementType > > mat;
	
	//constructors for user specific initialisations
	Matrix(void) {}
		
	Matrix(int r_s, int c_s) : row_size(r_s), col_size(c_s) {
		mat.resize(row_size);
		for(int i = 0; i < row_size; i++) {
			mat[i].resize(col_size);
		}
	}

	Matrix(const Matrix<ElementType> &M) : row_size(M.row_size), col_size(M.col_size), mat(M.mat) {}

	//temporary structure to store 
	inline Matrix &operator=(const BinaryAdd<ElementType> &X) {
		row_size = X.l.row_size;
		col_size = X.l.col_size;
		assert(X.l.col_size == X.r.col_size && X.l.row_size == X.r.row_size);
		for(int i = 0; i < row_size; i++) {
			for(int j = 0; j < col_size; j++) {
				mat[i][j] = X.l.mat[i][j] + X.r.mat[i][j];
			}
		}
		//the destination is returned so no over head memory cost
		return *this;
	}

	inline Matrix &operator=(const BinaryMult<ElementType> &X) {
		row_size = X.l.row_size;
		col_size = X.r.col_size;

		//to check if matrix multiplication is dimensionally possible
		assert(X.l.col_size == X.r.row_size);

		//alocating O(row*col) additional memory to find the resultant
		//O(n^3) time complexity
		for (int i = 0; i < row_size; i++) {
		    for (int j = 0; j < col_size; j++) {
			    mat[i][j] = 0;
	            for (int k = 0; k < X.l.col_size; k++)
	                mat[i][j] += X.l.mat[i][k] * X.r.mat[k][j];
	        }
	    }
	    //the destination is returned so no over head memory cost
		return *this;
	}
};

template <class ElementType>
inline BinaryAdd<ElementType> operator+(const Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	return BinaryAdd<ElementType>(M1, M2);
}

template <class ElementType>
inline BinaryMult<ElementType> operator*(const Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	return BinaryMult<ElementType>(M1, M2);
}

#endif