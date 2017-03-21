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
#include "../includes/matrix.hpp"
#include <typeinfo>
#include <string>
#include <complex.h>
#include <limits.h>
#include <cmath>

BOOST_AUTO_TEST_SUITE(Constructor)
BOOST_AUTO_TEST_CASE (constructors_working) {
	//empty constructor
	Matrix<int> TestMatrix1;
	BOOST_CHECK(TestMatrix1.getRowSize() == 0);
	
	//resizes the matrix dimensions
	Matrix<int> TestMatrix2(5, 3);
	BOOST_CHECK((unsigned int)TestMatrix2.getRowSize() == TestMatrix2.getRowSize());
	BOOST_CHECK( (TestMatrix2.getRowSize() == 5) && (TestMatrix2.getColSize() == 3) );
	// for(unsigned int i = 0; i < 5; i++) {
	// 	BOOST_CHECK((unsigned int)TestMatrix2.mat[i].size() == TestMatrix2.getColSize());
	// }
	//copy constructor
	Matrix<int> TestMatrix3(2, 2);
	TestMatrix3.setVal(0, 0, 1); 
	TestMatrix3.setVal(0, 1, 2);
	TestMatrix3.setVal(1, 0, 3);
	TestMatrix3.setVal(1, 1, 4);
	Matrix<int> TestMatrix4(TestMatrix3);
	BOOST_CHECK( TestMatrix4.getRowSize() == TestMatrix4.getRowSize());
	BOOST_CHECK( (TestMatrix4.getRowSize() == 2) && (TestMatrix4.getColSize() == 2) );
	// for(unsigned int i = 0; i < 2; i++) {
	// 	BOOST_CHECK((unsigned int)TestMatrix4.mat[i].size() == TestMatrix4.getColSize());
	// }
	for(unsigned int i = 0; i < 2; i++) {
		for(unsigned int j = 0; j < 2; j++) {
			//std::cout << TestMatrix4.getVal(i, j) << ' ' << TestMatrix3.getVal(i, j) << std::endl;
			BOOST_CHECK(TestMatrix3.getVal(i, j) == TestMatrix4.getVal(i, j));		}
	}
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(VariableType)
BOOST_AUTO_TEST_CASE (type_check) {
	
	//unsigned int is accepted
	Matrix<int> M(1,1);
	M.setVal(0, 0, 1);
	std::string type = typeid(M.getVal(0, 0)).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");
	
	//char is rejected
	Matrix<char> M1(1,1);
	M1.setVal(0, 0, 'a');
	type = typeid(M1.getVal(0, 0)).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");	
	
	//string is rejected
	Matrix<std::string> M2(1,1);
	M2.setVal(0, 0, "foo");
	type = typeid(M2.getVal(0, 0)).name();
	BOOST_CHECK(type == "i" || type == "l" || type == "x" || type == "f" || type == "d" || type == "St7complexIiE" || type == "St7complexIlE" || type == "St7complexIxE" || type == "St7complexIfE" || type == "St7complexIdE");
}
BOOST_AUTO_TEST_SUITE_END()


//matrix addition


BOOST_AUTO_TEST_SUITE(Matrix_Addition)
BOOST_AUTO_TEST_CASE (Matrix_Sum_Int) {

	Matrix<int> TestMatrix1(3, 2), TestMatrix2(3, 2), TestMatrix3(3, 2), TestMatrix4(3, 2);
	TestMatrix1.setVal(0, 0, 1);TestMatrix1.setVal(0, 1, 2);
	TestMatrix1.setVal(1, 0, 3);TestMatrix1.setVal(1, 1, 4);
	TestMatrix1.setVal(2, 0, 5);TestMatrix1.setVal(2, 1, 6);
	
	TestMatrix2.setVal(0, 0, 2);TestMatrix2.setVal(0, 1, -4);
	TestMatrix2.setVal(1, 0,-3);TestMatrix2.setVal(1, 1, -5);
	TestMatrix2.setVal(2, 0, 7);TestMatrix2.setVal(2, 1, 1000);

	TestMatrix3.setVal(0, 0, 3);TestMatrix3.setVal(0, 1, -2);
	TestMatrix3.setVal(1, 0, 0);TestMatrix3.setVal(1, 1, -1);
	TestMatrix3.setVal(2, 0, 12);TestMatrix3.setVal(2, 1, 1006);
	
	// TestMatrix1 = {{1, 2 }, {3, 4}, {5, 6}};
	// TestMatrix2 = {{2, -4} ,{-3 , -5} , {7, 1000}};
	// TestMatrix3 = {{3, -2}, {0, -1}, {12, 1006}};

	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.getRowSize() == TestMatrix2.getRowSize());
	BOOST_CHECK(TestMatrix1.getColSize() == TestMatrix2.getColSize());

	if((TestMatrix1.getRowSize() != TestMatrix2.getRowSize()) || (TestMatrix1.getColSize() != TestMatrix2.getColSize()))
		return;

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(unsigned int i = 0; i < TestMatrix4.getRowSize(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.getColSize(); j++) {
			//overflow check
			BOOST_CHECK( (double) (fabs( ( double ) TestMatrix1.getVal(i, j) + (double)TestMatrix2.getVal(i, j))) <= INT_MAX);
			//computed value check
			BOOST_CHECK(TestMatrix4.getVal(i, j) == TestMatrix3.getVal(i, j));
		}
	}
}
BOOST_AUTO_TEST_CASE (Matrix_Sum_long_long) {

	Matrix<long long> TestMatrix1(3, 2), TestMatrix2(3, 2), TestMatrix3(3, 2), TestMatrix4(3, 2);
	TestMatrix1.setVal(0, 0, (long long)1e18);TestMatrix1.setVal(0, 1, (long long)2e6);
	TestMatrix1.setVal(1, 0, 3);TestMatrix1.setVal(1, 1, 4);
	TestMatrix1.setVal(2, 0, 5);TestMatrix1.setVal(2, 1, (long long)6e8);
	
	TestMatrix2.setVal(0, 0, (long long)2e18);TestMatrix2.setVal(0, 1, -(long long)4e6);
	TestMatrix2.setVal(1, 0,-3);TestMatrix2.setVal(1, 1, -5);
	TestMatrix2.setVal(2, 0, 7);TestMatrix2.setVal(2, 1, (long long)1000e8);

	TestMatrix3.setVal(0, 0, (long long)2e18);TestMatrix3.setVal(0, 1, -(long long)2e6);
	TestMatrix3.setVal(1, 0, 0);TestMatrix3.setVal(1, 1, -1);
	TestMatrix3.setVal(2, 0, 12);TestMatrix3.setVal(2, 1, (long long)1006e8);
	
	// TestMatrix1 = {{(long long)1e18, (long long)2e6 }, {3, 4}, {5, (long long)6e8}};
	// TestMatrix2 = {{(long long)2e18, (long long)-4e6} ,{-3 , -5} , {7, (long long)1000e8}};
	// TestMatrix3 = {{(long long)2e18, (long long)-2e6}, {0, -1}, {12, (long long)1006e8}};
	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.getRowSize() == TestMatrix2.getRowSize());
	BOOST_CHECK(TestMatrix1.getColSize() == TestMatrix2.getColSize());
	if((TestMatrix1.getRowSize() != TestMatrix2.getRowSize()) || (TestMatrix1.getColSize() != TestMatrix2.getColSize()))
		return;

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(unsigned int i = 0; i < TestMatrix4.getRowSize(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.getColSize(); j++) {
			//overflow check
			BOOST_CHECK( (unsigned long long) (fabs( ( double) TestMatrix1.getVal(i, j) + (double)TestMatrix2.getVal(i, j))) <= LLONG_MAX);
			//computed value check
			BOOST_CHECK(TestMatrix4.getVal(i, j) == TestMatrix3.getVal(i, j));
		}
	}
}
BOOST_AUTO_TEST_CASE (Matrix_Sum_float) {

	Matrix<float> TestMatrix1(1, 1), TestMatrix2(1, 1), TestMatrix3(1, 1), TestMatrix4(1, 1);
	TestMatrix1.setVal(0, 0, 1.231);
	TestMatrix2.setVal(0, 0, 2.52);
	TestMatrix3.setVal(0, 0, 3.751);
	
	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.getRowSize() == TestMatrix2.getRowSize());
	BOOST_CHECK(TestMatrix1.getColSize() == TestMatrix2.getColSize());

	if((TestMatrix1.getRowSize() != TestMatrix2.getRowSize()) || (TestMatrix1.getColSize() != TestMatrix2.getColSize()))
		return ;

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(unsigned int i = 0; i < TestMatrix4.getRowSize(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.getColSize(); j++) {
			//overflow check
			BOOST_CHECK( (double) (fabs( ( double ) TestMatrix1.getVal(i, j) + ( double )TestMatrix2.getVal(i, j))) <= (3.40282347e+38F));
			//computed value check
			BOOST_CHECK(TestMatrix4.getVal(i, j) == TestMatrix3.getVal(i, j));
		}
	}	
}
BOOST_AUTO_TEST_CASE (Matrix_Sum_complex) {

	Matrix< std::complex<double> > TestMatrix1(2, 1), TestMatrix2(2, 1), TestMatrix3(2, 1), TestMatrix4(2, 1);
	
	TestMatrix1.setVal(0, 0, std::complex<double>(1, 1.2));
	TestMatrix1.setVal(1, 0, std::complex<double>(2, 1.3));
	
	TestMatrix2.setVal(0, 0, std::complex<double>(-1, 9.2));
	TestMatrix2.setVal(1, 0, std::complex<double>(2.9, 1.1));

	TestMatrix3.setVal(0, 0, std::complex<double>(0, 10.4));
	TestMatrix3.setVal(1, 0, std::complex<double>(4.9, 2.4));
	// TestMatrix1 = {{std::complex<double>(1, 1.2)}, {std::complex<double>(2, 1.3)}};
	// TestMatrix2 = {{std::complex<double>(-1, 9.2)}, {std::complex<double>(2.9, 1.1)}};
	// TestMatrix3 = {{std::complex<double>(0, 10.4)}, {std::complex<double>(4.9, 2.4)}};
	
	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.getRowSize() == TestMatrix2.getRowSize());
	BOOST_CHECK(TestMatrix1.getColSize() == TestMatrix2.getColSize());

	if((TestMatrix1.getRowSize() != TestMatrix2.getRowSize()) || (TestMatrix1.getColSize() != TestMatrix2.getColSize()))
		return;

	TestMatrix4 = TestMatrix1 + TestMatrix2;

	for(unsigned int i = 0; i < TestMatrix4.getRowSize(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.getColSize(); j++) {
			//taking a precision error of 1e-13
			BOOST_CHECK(fabs(TestMatrix4.getVal(i, j).real() - TestMatrix3.getVal(i, j).real()) <= 1e-13);
			BOOST_CHECK(fabs(TestMatrix4.getVal(i, j).imag() - TestMatrix3.getVal(i, j).imag()) <= 1e-13);
		}
	}	
}
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(Matrix_Multiplication)
BOOST_AUTO_TEST_CASE (Matrix_Multiplication_complex) {

	Matrix< std::complex<unsigned int > > TestMatrix1(2, 2), TestMatrix2(2, 2), TestMatrix3(2, 2), TestMatrix4(2, 2);
	TestMatrix1.setVal(0, 0, std::complex<int>(1, 1));TestMatrix1.setVal(0, 1, std::complex<int>(2, 3));
	TestMatrix1.setVal(1, 0, std::complex<int>(1, -1));TestMatrix1.setVal(1, 1, std::complex<int>(2, -4));
	
	TestMatrix2.setVal(0, 0, std::complex<int>(0, 1));TestMatrix2.setVal(0, 1, std::complex<int>(0, -7));
	TestMatrix2.setVal(1, 0, std::complex<int>(0, 8));TestMatrix2.setVal(1, 1, std::complex<int>(9, 3));

	TestMatrix3.setVal(0, 0, std::complex<int>(-25, 17));TestMatrix3.setVal(0, 1, std::complex<int>(16, 26));
	TestMatrix3.setVal(1, 0, std::complex<int>(33, 17));TestMatrix3.setVal(1, 1, std::complex<int>(23, -37));

	
	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.getColSize() == TestMatrix2.getRowSize());

	if(TestMatrix1.getColSize() != TestMatrix2.getRowSize())
		return;

	TestMatrix4 = TestMatrix1 * TestMatrix2;

	for(unsigned int i = 0; i < TestMatrix4.getRowSize(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.getColSize(); j++) {
			//computed value check
			BOOST_CHECK(TestMatrix4.getVal(i, j) == TestMatrix3.getVal(i, j));
		}
	}
}

BOOST_AUTO_TEST_CASE (Matrix_Multiplication_Int) {

	Matrix<int> TestMatrix1(2, 2), TestMatrix2(1, 3), TestMatrix3(1, 3), TestMatrix4(3, 1);
	TestMatrix1.setVal(0, 0, 1);TestMatrix1.setVal(0, 1, 3);
	TestMatrix1.setVal(1, 0, 1);TestMatrix1.setVal(1, 1, -1);
	
	TestMatrix2.setVal(0, 0, 1);
	TestMatrix2.setVal(0, 1, 0);
	TestMatrix2.setVal(0, 2,-7);

	TestMatrix3.setVal(0, 0, -25);
	TestMatrix3.setVal(0, 1, 16);
	TestMatrix3.setVal(0, 2, 33);

	// TestMatrix1 = {{1, 3}, {1, -1}};
	// TestMatrix2 = {{1, 0, -7}};
	// TestMatrix3 = {{-25}, {16}, {33}};	

	//addition is possible dimensionally 
	BOOST_CHECK(TestMatrix1.getColSize() == TestMatrix2.getRowSize());

	if(TestMatrix1.getColSize() != TestMatrix2.getRowSize())
		return;
	
	TestMatrix4 = TestMatrix1 * TestMatrix2;
	
	for(unsigned int i = 0; i < TestMatrix4.getRowSize(); i++) {
		for(unsigned int j = 0; j < TestMatrix4.getColSize(); j++) {
			//computed value check
			BOOST_CHECK(TestMatrix4.getVal(i, j) == TestMatrix3.getVal(i, j));
		}
	}
}
BOOST_AUTO_TEST_SUITE_END()