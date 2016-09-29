#include <stan/math/prim/mat.hpp>
#include <gtest/gtest.h>
#include <test/unit/math/prim/mat/fun/expect_matrix_eq.hpp>
#include <cstdlib>
#include <ctime>

using Eigen::Matrix;
using Eigen::Dynamic;
using std::rand;

TEST(MathMatrix, matrix_exp_1x1) {
    
    Matrix<double, Dynamic, Dynamic> m1(1,1), m2(1,1);
    m1 << 0;
    m2 << 1;

    expect_matrix_eq(m2, stan::math::matrix_exp(m1));
}

TEST(MathMatrix, matrix_exp_2x2) {

    // example from Moler & Van Loan, 2003
    Matrix<double, Dynamic, Dynamic> m1(2,2), m2(2,2);
    m1 << -49, 24, -64, 31;
    m2 << -.735759, .551819, -1.471518, 1.103638;

    expect_matrix_eq(m2, stan::math::matrix_exp(m1));
}

TEST(MathMatrix, matrix_exp_3x3) {

    // example from http://www.sosmath.com/matrix/expo/expo.html
    Matrix<double, Dynamic, Dynamic> m1(3,3), m2(3,3);
    m1 << 0, 1, 2, 0, 0, -1, 0, 0, 0;
    m2 << 1, 1, 1.5, 0, 1, -1, 0, 0, 1;

    expect_matrix_eq(m2, stan::math::matrix_exp(m1));
}

TEST(MathMatrix, matrix_exp_3x3_2) {

	Matrix<double, Dynamic, Dynamic> m1(3,3), m2(3,3);
	m1 << 89, -66, -18, 20, -14, -4, 360, -270, -73;
	m2 << 245.95891, -182.43047, -49.11821,
		  93.41549, -67.3433, -18.68310,
		  842.54120, -631.90590, -168.14036;

	expect_matrix_eq(m2, stan::math::matrix_exp(m1));
}

TEST(MathMatrix, matrix_exp_100x100) {
	
	int size = 100;
	srand(1); // set seed
    Matrix<double, Dynamic, Dynamic> S = Eigen::MatrixXd::Identity(size, size),
      I = Eigen::MatrixXd::Identity(size, size);
    int col1, col2;
	for(int i = 0; i < 5 * size; i++) {
		col1 = rand() % size;
		col2 = rand() % size;
		while(col1 == col2) col2 = rand() % size;
		S.col(col1) += S.col(col2) * std::pow(-1, rand());
	}
	Matrix<double, Dynamic, Dynamic> S_inv = stan::math::mdivide_right(I, S);
	Matrix<double, 1, Dynamic> diag_elements(size);
	diag_elements.setRandom();
    Matrix<double, 1, Dynamic> exp_diag_elements =
      stan::math::exp(diag_elements);
	
	Matrix<double, Dynamic, Dynamic> A =
      S * diag_elements.asDiagonal() * S_inv,
	  exp_A = S * exp_diag_elements.asDiagonal() * S_inv,
	  expm_A = stan::math::matrix_exp(A);

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if (std::abs(exp_A(i, j)) < 1e-10)
			  EXPECT_NEAR(exp_A(i, j), expm_A(i, j), 1e-11);
			else EXPECT_FLOAT_EQ(exp_A(i, j), expm_A(i, j));
		}
	}
}

TEST(MathMatrix, matrix_exp_exceptions) {

    using stan::math::matrix_exp;

    Matrix<double, Dynamic, Dynamic> m1(0,0), m2(1,2);

    EXPECT_THROW(matrix_exp(m1), std::invalid_argument);
    EXPECT_THROW(matrix_exp(m2), std::invalid_argument);   
}

TEST(MathMatrix, NOT_A_TEST_matrix_num_err) {

	// Code to showcase how dealing with very small
	// numbers ( < 1e-10) can increase the relative
	// error. That is why the conditions for small 
	// numbers are laxed (results agree within 1e-10,
	// as oppose to using relative error). 

    using stan::math::mdivide_right;

    Matrix<double, Dynamic, Dynamic> m(2, 2), exp_m(2, 2), D(2, 2),
      A(2, 2), exp_A(2, 2), D_m(2, 2), D_expm(2, 2);
    m << 1e-13, 0, 0, 1e-15;
    D << 1, 2, 3, 4;
    exp_m << exp(1e-13), 0, 0, exp(1e-15); 
    D_m = D * m;
    A = mdivide_right(D_m, D);
    D_expm = D * exp_m;

    /*     
    std::cout << std::endl;
    std::cout << mdivide_right(D_expm, D) << std::endl << std::endl;
    std::cout << stan::math::matrix_exp(A) << std::endl << std::endl;
    std::cout << stan::math::matrix_exp_pade(A) << std::endl << std::endl;
    */
}
