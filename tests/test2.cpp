//Contains Unit tests for the Matrix libraries matrixv1.h matrixv2.h
//Types of exceptions and errors addressed
//Constructor working 
//logical errors in matrix operations
//variable type errors
//overflow errors
//dimensional errors correspoing to operations
//use the command ./test  --log_level=all to see the error report

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../matrixv2.h"
#include <typeinfo>
#include <string>
#include <complex.h>
#include <limits.h>
#include <cmath>


BOOST_AUTO_TEST_SUITE(Constructor)
BOOST_AUTO_TEST_CASE (constructors_working) {
	//empty constructor
	Matrix<int> TestMatrix1;
	BOOST_CHECK(TestMatrix1.mat.size() == 0);
	
	//resizes the matrix dimensions
	Matrix<int> TestMatrix2(5, 3);
	BOOST_CHECK((int)TestMatrix2.mat.size() == TestMatrix2.row_size);
	BOOST_CHECK( (TestMatrix2.row_size == 5) && (TestMatrix2.col_size == 3) );
	for(int i = 0; i < 5; i++) {
		BOOST_CHECK((int)TestMatrix2.mat[i].size() == TestMatrix2.col_size);
	}
	
	//copy constructor
	Matrix<int> TestMatrix3(2, 2);
	TestMatrix3.mat = {{1, 2}, {3, 4}};
	Matrix<int> TestMatrix4(TestMatrix3);
	BOOST_CHECK((int)TestMatrix4.mat.size() == TestMatrix4.row_size);
	BOOST_CHECK( (TestMatrix4.row_size == 2) && (TestMatrix4.col_size == 2) );
	for(int i = 0; i < 2; i++) {
		BOOST_CHECK((int)TestMatrix4.mat[i].size() == TestMatrix4.col_size);
	}
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			BOOST_CHECK(TestMatrix3.mat[i][j] == TestMatrix4.mat[i][j]);
		}
	}
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(VariableType)
BOOST_AUTO_TEST_CASE (type_check) {
	
	//int is accepted
	Matrix<int> M(1,1);
	M.mat[0][0] = 1;
	std::string type = typeid(M.mat[0][0]).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");
	
	//char is rejected
	Matrix<char> M1(1,1);
	M1.mat[0][0] = 'a';
	type = typeid(M1.mat[0][0]).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");	
	
	//string is rejected
	Matrix<std::string> M2(1,1);
	M2.mat[0][0] = "foo";
	type = typeid(M2.mat[0][0]).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");
}
BOOST_AUTO_TEST_SUITE_END()


//matrix addition
BOOST_AUTO_TEST_SUITE(Matrix_Addition)
BOOST_AUTO_TEST_CASE (Matrix_Sum_int) {

	Matrix<int> TestMatrix1(3, 2), TestMatrix2(3, 2), TestMatrix3(3, 2), TestMatrix4(3, 2);
	TestMatrix1.mat = {{(int)1, 2 }, {3, 4}, {5, 6}};
	TestMatrix2.mat = {{(int)2, -4} ,{-3 , -5} , {7, 1000}};
	TestMatrix3.mat = {{(int)3, -2}, {0, -1}, {12, 1006}};

	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.row_size == TestMatrix2.row_size);
	BOOST_CHECK(TestMatrix1.col_size == TestMatrix2.col_size);

	if((TestMatrix1.row_size != TestMatrix2.row_size) || (TestMatrix1.col_size != TestMatrix2.col_size))
		return;

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(int i = 0; i < TestMatrix4.row_size; i++) {
		for(int j = 0; j < TestMatrix4.col_size; j++) {
			//overflow check
			BOOST_CHECK( (double) (fabs( ( double ) TestMatrix1.mat[i][j] + ( double )TestMatrix2.mat[i][j])) <= INT_MAX);
			//computed value check
			BOOST_CHECK(TestMatrix4.mat[i][j] == TestMatrix3.mat[i][j]);
		}
	}
}
BOOST_AUTO_TEST_CASE (Matrix_Sum_long_long) {

	Matrix<long long> TestMatrix1(3, 2), TestMatrix2(3, 2), TestMatrix3(3, 2), TestMatrix4(3, 2);
	TestMatrix1.mat = {{(long long)1e18, (long long)2e6 }, {3, 4}, {5, (long long)6e8}};
	TestMatrix2.mat = {{(long long)2e18, -(long long)4e6} ,{-3 , -5} , {7, (long long)1000e8}};
	TestMatrix3.mat = {{(long long)2e18, -(long long)2e6}, {0, -1}, {12, (long long)1006e8}};
	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.row_size == TestMatrix2.row_size);
	BOOST_CHECK(TestMatrix1.col_size == TestMatrix2.col_size);
	if((TestMatrix1.row_size != TestMatrix2.row_size) || (TestMatrix1.col_size != TestMatrix2.col_size))
		return;

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(int i = 0; i < TestMatrix4.row_size; i++) {
		for(int j = 0; j < TestMatrix4.col_size; j++) {
			//overflow check
			BOOST_CHECK( (double) (fabs( ( double ) TestMatrix1.mat[i][j] + ( double )TestMatrix2.mat[i][j])) <= LLONG_MAX);
		
			BOOST_CHECK(TestMatrix4.mat[i][j] == TestMatrix3.mat[i][j]);
		}
	}
}
BOOST_AUTO_TEST_CASE (Matrix_Sum_float) {

	Matrix<float> TestMatrix1(1, 1), TestMatrix2(1, 1), TestMatrix3(1, 1), TestMatrix4(1, 1);
	TestMatrix1.mat = {{1.231}};
	TestMatrix2.mat = {{2.52}};
	TestMatrix3.mat = {{3.751}};
	
	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.row_size == TestMatrix2.row_size);
	BOOST_CHECK(TestMatrix1.col_size == TestMatrix2.col_size);

	if((TestMatrix1.row_size != TestMatrix2.row_size) || (TestMatrix1.col_size != TestMatrix2.col_size))
		return ;

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(int i = 0; i < TestMatrix4.row_size; i++) {
		for(int j = 0; j < TestMatrix4.col_size; j++) {
			//overflow check
			BOOST_CHECK( (double) (fabs( ( double ) TestMatrix1.mat[i][j] + ( double )TestMatrix2.mat[i][j])) <= (3.40282347e+38F));
			//computed value check
			BOOST_CHECK(TestMatrix4.mat[i][j] == TestMatrix3.mat[i][j]);
		}
	}	
}
BOOST_AUTO_TEST_CASE (Matrix_Sum_complex) {

	Matrix< std::complex<double> > TestMatrix1(2, 1), TestMatrix2(2, 1), TestMatrix3(2, 1), TestMatrix4(2, 1);
	TestMatrix1.mat = {{std::complex<double>(1, 1.2)}, {std::complex<double>(2, 1.3)}};
	TestMatrix2.mat = {{std::complex<double>(-1, 9.2)}, {std::complex<double>(2.9, 1.1)}};
	TestMatrix3.mat = {{std::complex<double>(0, 10.4)}, {std::complex<double>(4.9, 2.4)}};
	
	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.row_size == TestMatrix2.row_size);
	BOOST_CHECK(TestMatrix1.col_size == TestMatrix2.col_size);

	if((TestMatrix1.row_size != TestMatrix2.row_size) || (TestMatrix1.col_size != TestMatrix2.col_size))
		return;

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(int i = 0; i < TestMatrix4.row_size; i++) {
		for(int j = 0; j < TestMatrix4.col_size; j++) {
			//taking a precision error of 1e-13
			BOOST_CHECK(fabs(TestMatrix4.mat[i][j].real() - TestMatrix3.mat[i][j].real()) <= 1e-13);
			BOOST_CHECK(fabs(TestMatrix4.mat[i][j].imag() - TestMatrix3.mat[i][j].imag()) <= 1e-13);
		}
	}	
}
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(Matrix_Multiplication)
BOOST_AUTO_TEST_CASE (Matrix_Multiplication_complex) {

	Matrix< std::complex<int > > TestMatrix1(2, 2), TestMatrix2(2, 2), TestMatrix3(2, 2), TestMatrix4(2, 2);
	TestMatrix1.mat = {{std::complex<int>(1, 1), std::complex<int>(2, 3)}, {std::complex<int>(1, -1), std::complex<int>(2, -4)}};
	TestMatrix2.mat = {{std::complex<int>(0, 1), std::complex<int>(0, -7)}, {std::complex<int>(0, 8), std::complex<int>(9, 3)}};
	TestMatrix3.mat = {{std::complex<int>(-25, 17), std::complex<int>(16, 26)}, {std::complex<int>(33, 17), std::complex<int>(23, -37)}};
	
	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.col_size == TestMatrix2.row_size);

	if(TestMatrix1.col_size != TestMatrix2.row_size)
		return;

	TestMatrix4 = TestMatrix1 * TestMatrix2;

	for(int i = 0; i < TestMatrix4.row_size; i++) {
		for(int j = 0; j < TestMatrix4.col_size; j++) {
			//computed value check
			BOOST_CHECK(TestMatrix4.mat[i][j] == TestMatrix3.mat[i][j]);
		}
	}
}

BOOST_AUTO_TEST_CASE (Matrix_Multiplication_int) {

	Matrix<int> TestMatrix1(2, 2), TestMatrix2(1, 3), TestMatrix3(1, 3), TestMatrix4(3, 1);
	TestMatrix1.mat = {{1, 3}, {1, -1}};
	TestMatrix2.mat = {{1, 0, -7}};
	TestMatrix3.mat = {{-25}, {16}, {33}};	

	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.col_size == TestMatrix2.row_size);

	if(TestMatrix1.col_size != TestMatrix2.row_size)
		return;
	
	TestMatrix4 = TestMatrix1 * TestMatrix2;
	
	for(int i = 0; i < TestMatrix4.row_size; i++) {
		for(int j = 0; j < TestMatrix4.col_size; j++) {
			//computed value check
			BOOST_CHECK(TestMatrix4.mat[i][j] == TestMatrix3.mat[i][j]);
		}
	}
}
BOOST_AUTO_TEST_SUITE_END()
