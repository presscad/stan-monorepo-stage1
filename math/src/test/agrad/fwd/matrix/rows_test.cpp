#include <stan/math/matrix/rows.hpp>
#include <gtest/gtest.h>
#include <stan/agrad/fwd/matrix/typedefs.hpp>
#include <stan/agrad/var.hpp>

TEST(AgradFwdMatrix,rows_vector) {
  using stan::agrad::vector_fd;
  using stan::agrad::row_vector_fd;
  using stan::math::rows;

  vector_fd v(5);
  v << 0, 1, 2, 3, 4;
  EXPECT_EQ(5U, rows(v));
  
  v.resize(0);
  EXPECT_EQ(0U, rows(v));
}
TEST(AgradFwdMatrix,rows_rowvector) {
  using stan::agrad::row_vector_fd;
  using stan::math::rows;

  row_vector_fd rv(5);
  rv << 0, 1, 2, 3, 4;
  EXPECT_EQ(1U, rows(rv));

  rv.resize(0);
  EXPECT_EQ(1U, rows(rv));
}
TEST(AgradFwdMatrix,rows_matrix) {
  using stan::agrad::matrix_fd;
  using stan::math::rows;

  matrix_fd m(2,3);
  m << 0, 1, 2, 3, 4, 5;
  EXPECT_EQ(2U, rows(m));
  
  m.resize(0,2);
  EXPECT_EQ(0U, rows(m));
}
TEST(AgradFwdFvarVarMatrix,rows_vector) {
  using stan::agrad::vector_fv;
  using stan::agrad::row_vector_fv;
  using stan::math::rows;

  vector_fv v(5);
  v << 0, 1, 2, 3, 4;
  EXPECT_EQ(5U, rows(v));
  
  v.resize(0);
  EXPECT_EQ(0U, rows(v));
}
TEST(AgradFwdFvarVarMatrix,rows_rowvector) {
  using stan::agrad::row_vector_fv;
  using stan::math::rows;

  row_vector_fv rv(5);
  rv << 0, 1, 2, 3, 4;
  EXPECT_EQ(1U, rows(rv));

  rv.resize(0);
  EXPECT_EQ(1U, rows(rv));
}
TEST(AgradFwdFvarVarMatrix,rows_matrix) {
  using stan::agrad::matrix_fv;
  using stan::math::rows;

  matrix_fv m(2,3);
  m << 0, 1, 2, 3, 4, 5;
  EXPECT_EQ(2U, rows(m));
  
  m.resize(0,2);
  EXPECT_EQ(0U, rows(m));
}
TEST(AgradFwdFvarFvarMatrix,rows_vector) {
  using stan::agrad::vector_ffd;
  using stan::agrad::row_vector_ffd;
  using stan::math::rows;

  vector_ffd v(5);
  v << 0, 1, 2, 3, 4;
  EXPECT_EQ(5U, rows(v));
  
  v.resize(0);
  EXPECT_EQ(0U, rows(v));
}
TEST(AgradFwdFvarFvarMatrix,rows_rowvector) {
  using stan::agrad::row_vector_ffd;
  using stan::math::rows;

  row_vector_ffd rv(5);
  rv << 0, 1, 2, 3, 4;
  EXPECT_EQ(1U, rows(rv));

  rv.resize(0);
  EXPECT_EQ(1U, rows(rv));
}
TEST(AgradFwdFvarFvarMatrix,rows_matrix) {
  using stan::agrad::matrix_ffd;
  using stan::math::rows;

  matrix_ffd m(2,3);
  m << 0, 1, 2, 3, 4, 5;
  EXPECT_EQ(2U, rows(m));
  
  m.resize(0,2);
  EXPECT_EQ(0U, rows(m));
}
