
#include <iostream>
#include "../matrixv1.h"

int main(int argc, char **argv) {

	//creates a matrix of size 0 X 0
	Matrix<int> M1;
	std::cout << "Row_size->" << M1.getRowSize() << ' ' << "Col_size->" << M1.getColSize() << std::endl;

	//creates a matrix of size 30 X 7
	Matrix<int> M2(30, 7);
	std::cout << "Row_size->" << M2.getRowSize() << ' ' << "Col_size->" << M2.getColSize() << std::endl;

	Matrix<double> M3(3, 1);
	//setting values of matrix
	//format : ObjectName.setVal(row, col, value) equivalent to ObjectName.mat[row][col] = value;
	M3.setVal(0, 0, 1.2);
	M3.setVal(1, 0, 2.211);
	M3.setVal(2, 0, 3.289);

	//copies matrix object M3 to M4
	Matrix<double> M4(M3);
	std::cout << "Row_size->" << M4.getRowSize() << ' ' << "Col_size->" << M4.getColSize() << std::endl;


	for(int i = 0; i < M4.getRowSize(); i++)
		for(int j = 0; j < M4.getColSize(); j++)
			//format : ObjectName.getVal(row, col) returns the value ObjectName.mat[row][col]
			std::cout << "value at cell " << i << ":" << j << "->" << M4.getVal(i, j) << std::endl;
		return 0; 
}