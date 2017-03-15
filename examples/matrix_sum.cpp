#include <iostream>
#include "../matrixv1.h"

int main(int argc, char *argv) {

	Matrix<double> M1(3, 1);
	Matrix<double> M3(3, 1);
	M1.setVal(0, 0, 1.2);
	M1.setVal(1, 0, 2.211);
	M1.setVal(2, 0, 3.289);
	M3.setVal(0, 0, 81.2);
	M3.setVal(1, 0, 25.5211);
	M3.setVal(2, 0, 31.2589);
	Matrix<double> M2(M1);
	Matrix<double> M4(3, 1);
	
	//binary additions
	M4 = M1 + M3;
	
	for(int i = 0; i < M4.getRowSize(); i++)
		for(int j = 0; j < M4.getColSize(); j++)
			//format : ObjectName.getVal(row, col) returns the value ObjectName.mat[row][col]
			std::cout << "value at cell " << i << ":" << j << "->" << M4.getVal(i, j) << std::endl;

	//multiple additions

	std::cout << std::endl;
	M4 = M1 + M2 + M3;

	for(int i = 0; i < M4.getRowSize(); i++)
		for(int j = 0; j < M4.getColSize(); j++)
			//format : ObjectName.getVal(row, col) returns the value ObjectName.mat[row][col]
			std::cout << "value at cell " << i << ":" << j << "->" << M4.getVal(i, j) << std::endl;

 	return 0; 

}