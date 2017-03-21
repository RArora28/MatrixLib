#include <iostream>
#include "../includes/matrix.hpp"

int main(int argc, char **argv) {

	Matrix<double> M1(3, 1);
	Matrix<double> M3(3, 1);
	M1.setVal(0, 0, 1.2);
	M1.setVal(1, 0, 2.211);
	M1.setVal(2, 0, 3.289);
	M3.setVal(0, 0, 81.2);
	M3.setVal(1, 0, 25.5211);
	M3.setVal(2, 0, 31.2589);
	
	//binary additions
	M3 += M1;
	
	for(int i = 0; i < M3.getRowSize(); i++)
		for(int j = 0; j < M3.getColSize(); j++)
			//format : ObjectName.getVal(row, col) returns the value ObjectName.mat[row][col]
			std::cout << "value at cell " << i << ":" << j << "->" << M3.getVal(i, j) << std::endl;

 	return 0; 

}