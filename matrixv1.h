//Matrix class that calculates sum and product of 2 matrices using additional onsite memory

#ifndef MATRIXV1_INCLUDE
#define MATRIXV1_INCLUDE

#include <vector>
#include <type_traits>

template <class ElementType>
class Matrix {
public:
	int row_size, col_size;
	std::vector< std::vector <ElementType > > mat;
	Matrix(void) {}
	Matrix(int r_s, int c_s) : row_size(r_s), col_size(c_s) {
		mat.resize(row_size);
		for(int i = 0; i < row_size; i++) {
			mat[i].resize(col_size);
		}
	}
	Matrix(const Matrix<ElementType> &M) : row_size(M.row_size), col_size(M.col_size), mat(M.mat) {}
};

template <class ElementType>
inline Matrix<ElementType> operator+(const Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	//to check wheter the matrices have same dimensions
	assert(M1.row_size == M2.row_size);
	assert(M1.col_size == M2.col_size);
	//assert(std::is_integral<ElementType>::value||std::is_floating_point<ElementType>::value||std::izs_integral<ElementType>::value);
	//alocating O(row*col) additional memory to find the resultant
	Matrix<ElementType> res(M1.row_size, M1.col_size);
	for(int i = 0; i < M1.row_size; i++) {
		for(int j = 0; j < M1.col_size; j++) {
			res.mat[i][j] = M1.mat[i][j] + M2.mat[i][j];
		}
	}
	return res;
}

template <class ElementType>
inline Matrix<ElementType> operator*(const Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	//to check if matrix multiplication is dimensionally possible
	assert(M1.col_size == M2.row_size);

	//alocating O(row*col) additional memory to find the resultant
	//O(n^3) time complexity
	Matrix<ElementType> res(M1.row_size, M2.col_size);
	for (int i = 0; i < M1.row_size; i++) {
	    for (int j = 0; j < M2.col_size; j++) {
		    res.mat[i][j] = 0;
            for (int k = 0; k < M1.col_size; k++)
                res.mat[i][j] += M1.mat[i][k] * M2.mat[k][j];
        }
    }
    return res;
}

template <class ElementType>
inline void operator+=(Matrix<ElementType> &M1, const Matrix<ElementType> &M2) {
	//to check wheter the matrices have same dimensions
	assert(M1.row_size == M2.row_size);
	assert(M1.col_size == M2.col_size);
	//assert(std::is_integral<ElementType>::value||std::is_floating_point<ElementType>::value||std::izs_integral<ElementType>::value);
	//alocating O(row*col) additional memory to find the resultant
	for(int i = 0; i < M1.row_size; i++) {
		for(int j = 0; j < M1.col_size; j++) {
			M1.mat[i][j] = M1.mat[i][j] + M2.mat[i][j];
		}
	}
	return;
}

#endif