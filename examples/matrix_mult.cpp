#include <iostream>
#include "../includes/matrix.hpp"

int main(int argc, char **argv) {

	Matrix<double> M1(3, 1);
	Matrix<double> M3(1, 3);
	M1.setVal(0, 0, 1.2);
	M1.setVal(1, 0, 2.211);
	M1.setVal(2, 0, 3.289);
	M3.setVal(0, 0, 81.2);
	M3.setVal(0, 1, 25.5211);
	M3.setVal(0, 2, 31.2589);

	//Binary Multiplication
	Matrix<double> M4 = M1 * M3;	

	for(int i = 0; i < M4.getRowSize(); i++)
		for(int j = 0; j < M4.getColSize(); j++)
			//format : ObjectName.getVal(row, col) returns the value ObjectName.mat[row][col]
			std::cout << "value at cell " << i << ":" << j << "->" << M4.getVal(i, j) << std::endl;

	std::cout << std::endl;

	//multiple multiplications
	Matrix<double> M2(1, 1);
	M2.setVal(0, 0, 5);
	M4 = M2 * M3 * M1 ;

	for(int i = 0; i < M4.getRowSize(); i++)
		for(int j = 0; j < M4.getColSize(); j++)
			//format : ObjectName.getVal(row, col) returns the value ObjectName.mat[row][col]
			std::cout << "value at cell " << i << ":" << j << "->" << M4.getVal(i, j) << std::endl;

 	return 0; 

}