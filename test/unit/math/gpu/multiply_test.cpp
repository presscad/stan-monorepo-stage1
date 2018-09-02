#include <stan/math/prim/mat.hpp>
#include <stan/math/gpu/copy.hpp>
#include <stan/math/gpu/multiply.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <gtest/gtest.h>
#include <algorithm>
#ifdef STAN_OPENCL
boost::random::mt19937 rng;

#define  EXPECT_MATRIX_NEAR(A, B, DELTA) \
          for (int i = 0; i < A.size(); i++)  \
            EXPECT_NEAR(A(i), B(i), DELTA);

TEST(MathMatrix, vector_row_vector) {
  stan::math::vector_d v(3);
  stan::math::row_vector_d rv(3);
  stan::math::matrix_gpu v_gpu(v);
  stan::math::matrix_gpu rv_gpu(rv);
  stan::math::matrix_gpu m_gpu(1, 1);
  EXPECT_NO_THROW(m_gpu = stan::math::multiply(rv_gpu, v_gpu));
}

TEST(MathMatrix, one_dim_zero_matrix) {
  stan::math::matrix_d m0(5, 0);
  stan::math::matrix_d m1(0, 3);

  stan::math::matrix_gpu m0_gpu(m0);
  stan::math::matrix_gpu m1_gpu(m1);
  EXPECT_NO_THROW(stan::math::multiply(m0_gpu, m1_gpu));

  EXPECT_NO_THROW(stan::math::multiply(m0_gpu, 2.0));
  EXPECT_NO_THROW(stan::math::multiply(2.0, m0_gpu));

  EXPECT_NO_THROW(stan::math::multiply(m1_gpu, 2.0));
  EXPECT_NO_THROW(stan::math::multiply(2.0, m1_gpu));
}

TEST(MathMatrix, zero_result_matrix) {
  stan::math::matrix_d m0(0, 5);
  stan::math::matrix_d m1(5, 0);

  stan::math::matrix_gpu m0_gpu(m0);
  stan::math::matrix_gpu m1_gpu(m1);
  EXPECT_NO_THROW(stan::math::multiply(m0_gpu, m1_gpu));
}

TEST(MathMatrix, zero_size_input_matrix) {
  stan::math::matrix_d m0(0, 0);
  stan::math::matrix_d m1(0, 0);

  stan::math::matrix_gpu m0_gpu(m0);
  stan::math::matrix_gpu m1_gpu(m1);
  EXPECT_NO_THROW(stan::math::multiply(m0_gpu, m1_gpu));

  EXPECT_NO_THROW(stan::math::multiply(m0_gpu, 2.0));
  EXPECT_NO_THROW(stan::math::multiply(2.0, m0_gpu));
}

TEST(MathMatrix, non_matching_dim_excpetion) {
  stan::math::matrix_d m0(5, 3);
  stan::math::matrix_d m1(2, 6);

  stan::math::matrix_gpu m0_gpu(m0);
  stan::math::matrix_gpu m1_gpu(m1);
  EXPECT_THROW(stan::math::multiply(m0_gpu, m1_gpu), std::invalid_argument);
}

TEST(MathMatrix, multiply_scalar) {
  stan::math::vector_d v(25);
  stan::math::vector_d v_gpu_res(25);
  stan::math::row_vector_d rv(25);
  stan::math::row_vector_d rv_gpu_res(25);
  stan::math::matrix_d m(5, 5);
  stan::math::matrix_d m_gpu_res(5, 5);

  for (int i = 0; i < v.size(); i++)
    v(i) = stan::math::normal_rng(0.0, 5.0, rng);
  for (int i = 0; i < rv.size(); i++)
    rv(i) = stan::math::normal_rng(0.0, 5.0, rng);
  for (int i = 0; i < m.size(); i++)
    m(i) = stan::math::normal_rng(0.0, 5.0, rng);

  stan::math::matrix_gpu v_gpu(v);
  v_gpu = stan::math::multiply(v_gpu, 2.0);
  stan::math::copy(v_gpu_res, v_gpu);

  stan::math::matrix_gpu rv_gpu(rv);
  rv_gpu = stan::math::multiply(rv_gpu, 2.0);
  stan::math::copy(rv_gpu_res, rv_gpu);

  stan::math::matrix_gpu m_gpu(m);
  m_gpu = stan::math::multiply(m_gpu, 2.0);
  stan::math::copy(m_gpu_res, m_gpu);

  v = v * 2.0;
  rv = rv * 2.0;
  m = m * 2.0;

  EXPECT_MATRIX_NEAR(v, v_gpu_res, 1e-10);
  EXPECT_MATRIX_NEAR(rv, rv_gpu_res, 1e-10);
  EXPECT_MATRIX_NEAR(m, m_gpu_res, 1e-10);
}

TEST(MathMatrix, row_vector_vector) {
  stan::math::vector_d v(5);
  stan::math::row_vector_d rv(5);
  stan::math::matrix_d m0(1, 1);
  stan::math::matrix_d m0_gpu_res(1, 1);
  stan::math::matrix_d m1(5, 5);
  stan::math::matrix_d m1_gpu_res(5, 5);

  for (int i = 0; i < v.size(); i++)
    v(i) = stan::math::normal_rng(0.0, 5.0, rng);
  for (int i = 0; i < rv.size(); i++)
    rv(i) = stan::math::normal_rng(0.0, 5.0, rng);

  m0 = rv * v;
  m1 = v * rv;

  stan::math::matrix_gpu v_gpu(v);
  stan::math::matrix_gpu rv_gpu(rv);
  stan::math::matrix_gpu m0_gpu(1, 1);
  stan::math::matrix_gpu m1_gpu(5, 5);

  m0_gpu = stan::math::multiply(rv_gpu, v_gpu);
  m1_gpu = stan::math::multiply(v_gpu, rv_gpu);
  stan::math::copy(m0_gpu_res, m0_gpu);
  stan::math::copy(m1_gpu_res, m1_gpu);

  EXPECT_MATRIX_NEAR(m0, m0_gpu_res, 1e-10);
  EXPECT_MATRIX_NEAR(m1, m1_gpu_res, 1e-10);
}

TEST(AgradRevMatrix, multiply_small) {
  using stan::math::multiply;
  stan::math::matrix_d m1(3, 3);
  stan::math::matrix_d m2(3, 3);
  stan::math::matrix_d m3(3, 3);
  stan::math::matrix_d m3_gpu_res(3, 3);

  for (int i = 0; i < m1.size(); i++)
    m1(i) = stan::math::normal_rng(0.0, 5.0, rng);
  for (int i = 0; i < m2.size(); i++)
    m2(i) = stan::math::normal_rng(0.0, 5.0, rng);

  stan::math::matrix_gpu m11(m1);
  stan::math::matrix_gpu m22(m2);
  stan::math::matrix_gpu m33(m3);

  m3 = m1 * m2;

  m33 = stan::math::multiply(m11, m22);

  stan::math::copy(m3_gpu_res, m33);

  EXPECT_MATRIX_NEAR(m3, m3_gpu_res, 1e-10);
}

TEST(AgradRevMatrix, multiply_big) {
  using stan::math::multiply;
  int size = 512;
  stan::math::matrix_d m1(size, size);
  stan::math::matrix_d m2(size, size);
  stan::math::matrix_d m3(size, size);
  stan::math::matrix_d m3_gpu_res(size, size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      m1(i, j) = stan::math::normal_rng(0.0, 1.0, rng);
      m2(i, j) = stan::math::normal_rng(0.0, 1.0, rng);
    }
  }
  stan::math::matrix_gpu m11(m1);
  stan::math::matrix_gpu m22(m2);
  stan::math::matrix_gpu m33(size, size);

  m3 = m1 * m2;

  m33 = stan::math::multiply(m11, m22);

  stan::math::copy(m3_gpu_res, m33);

  EXPECT_MATRIX_NEAR(m3, m3_gpu_res, 1e-10);
}
#endif
