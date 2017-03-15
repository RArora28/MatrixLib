#include <iostream>
#include "../matrixv1.h"

int main(int argc, char *argv) {

	Matrix<double> M1(3, 1);
	Matrix<double> M3(1, 3);
	M1.setVal(0, 0, 1.2);
	M1.setVal(1, 0, 2.211);
	M1.setVal(2, 0, 3.289);
	M3.setVal(0, 0, 81.2);
	M3.setVal(0, 1, 25.5211);
	M3.setVal(0, 2, 31.2589);

	//Binary Multiplication
	M3 *= M1;

	//M1 is multiplied with updated M3
	M1 *= M3;

	std::cout << "M3:" << std::endl;
	for(int i = 0; i < M3.getRowSize(); i++)
		for(int j = 0; j < M3.getColSize(); j++)
			//format : ObjectName.getVal(row, col) returns the value ObjectName.mat[row][col]
			std::cout << "value at cell " << i << ":" << j << "->" << M3.getVal(i, j) << std::endl;
 
 	std::cout << "M1:" << std::endl;

	for(int i = 0; i < M1.getRowSize(); i++)
		for(int j = 0; j < M1.getColSize(); j++)
			//format : ObjectName.getVal(row, col) returns the value ObjectName.mat[row][col]
			std::cout << "value at cell " << i << ":" << j << "->" << M1.getVal(i, j) << std::endl;
 	
 	return 0; 

}