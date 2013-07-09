#include <stan/agrad/fwd/matrix/sum.hpp>
#include <gtest/gtest.h>
#include <stan/math/matrix/sum.hpp>
#include <stan/math/matrix/typedefs.hpp>
#include <stan/agrad/fwd/matrix/typedefs.hpp>
#include <stan/agrad/fwd/fvar.hpp>
#include <stan/agrad/var.hpp>

using stan::agrad::fvar;
using stan::agrad::var;
TEST(AgradFwdMatrix, sum_vector) {
  using stan::math::sum;
  using stan::math::vector_d;
  using stan::agrad::vector_fd;

  vector_d d(6);
  vector_fd v(6);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
   v(4).d_ = 1.0;
   v(5).d_ = 1.0;
  
  fvar<double> output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_);
  EXPECT_FLOAT_EQ( 0.0, output.d_);
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_);  
  EXPECT_FLOAT_EQ( 6.0, output.d_);

  d.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_);
  EXPECT_FLOAT_EQ(0.0, sum(v).d_);
}
TEST(AgradFwdMatrix, sum_rowvector) {
  using stan::math::sum;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fd;

  row_vector_d d(6);
  row_vector_fd v(6);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
   v(4).d_ = 1.0;
   v(5).d_ = 1.0;
  
  fvar<double> output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_);
  EXPECT_FLOAT_EQ( 0.0, output.d_);
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_);  
  EXPECT_FLOAT_EQ( 6.0, output.d_);

  d.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_);
  EXPECT_FLOAT_EQ(0.0, sum(v).d_);
}
TEST(AgradFwdMatrix, sum_matrix) {
  using stan::math::sum;
  using stan::math::matrix_d;
  using stan::agrad::matrix_fd;

  matrix_d d(2, 3);
  matrix_fd v(2, 3);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0,0).d_ = 1.0;
   v(0,1).d_ = 1.0;
   v(0,2).d_ = 1.0;
   v(1,0).d_ = 1.0;
   v(1,1).d_ = 1.0;
   v(1,2).d_ = 1.0;
  
  fvar<double> output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_);
  EXPECT_FLOAT_EQ( 0.0, output.d_);
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_);
  EXPECT_FLOAT_EQ( 6.0, output.d_);

  d.resize(0, 0);
  v.resize(0, 0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_);
  EXPECT_FLOAT_EQ(0.0, sum(v).d_);
}
TEST(AgradFwdFvarVarMatrix, sum_vector) {
  using stan::math::sum;
  using stan::math::vector_d;
  using stan::agrad::vector_fv;

  vector_d d(6);
  vector_fv v(6);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
   v(4).d_ = 1.0;
   v(5).d_ = 1.0;
  
  fvar<var> output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());
  EXPECT_FLOAT_EQ( 0.0, output.d_.val());
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());  
  EXPECT_FLOAT_EQ( 6.0, output.d_.val());

  d.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_.val());
  EXPECT_FLOAT_EQ(0.0, sum(v).d_.val());
}
TEST(AgradFwdFvarVarMatrix, sum_rowvector) {
  using stan::math::sum;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fv;

  row_vector_d d(6);
  row_vector_fv v(6);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
   v(4).d_ = 1.0;
   v(5).d_ = 1.0;
  
  fvar<var> output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());
  EXPECT_FLOAT_EQ( 0.0, output.d_.val());
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());  
  EXPECT_FLOAT_EQ( 6.0, output.d_.val());

  d.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_.val());
  EXPECT_FLOAT_EQ(0.0, sum(v).d_.val());
}
TEST(AgradFwdFvarVarMatrix, sum_matrix) {
  using stan::math::sum;
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;

  matrix_d d(2, 3);
  matrix_fv v(2, 3);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0,0).d_ = 1.0;
   v(0,1).d_ = 1.0;
   v(0,2).d_ = 1.0;
   v(1,0).d_ = 1.0;
   v(1,1).d_ = 1.0;
   v(1,2).d_ = 1.0;
  
  fvar<var> output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());
  EXPECT_FLOAT_EQ( 0.0, output.d_.val());
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());
  EXPECT_FLOAT_EQ( 6.0, output.d_.val());

  d.resize(0, 0);
  v.resize(0, 0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_.val());
  EXPECT_FLOAT_EQ(0.0, sum(v).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, sum_vector) {
  using stan::math::sum;
  using stan::math::vector_d;
  using stan::agrad::vector_ffd;

  vector_d d(6);
  vector_ffd v(6);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
   v(4).d_ = 1.0;
   v(5).d_ = 1.0;
  
  fvar<fvar<double> > output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());
  EXPECT_FLOAT_EQ( 0.0, output.d_.val());
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());  
  EXPECT_FLOAT_EQ( 6.0, output.d_.val());

  d.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_.val());
  EXPECT_FLOAT_EQ(0.0, sum(v).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, sum_rowvector) {
  using stan::math::sum;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffd;

  row_vector_d d(6);
  row_vector_ffd v(6);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
   v(4).d_ = 1.0;
   v(5).d_ = 1.0;
  
  fvar<fvar<double> > output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());
  EXPECT_FLOAT_EQ( 0.0, output.d_.val());
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());  
  EXPECT_FLOAT_EQ( 6.0, output.d_.val());

  d.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_.val());
  EXPECT_FLOAT_EQ(0.0, sum(v).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, sum_matrix) {
  using stan::math::sum;
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffd;

  matrix_d d(2, 3);
  matrix_ffd v(2, 3);
  
  d << 1, 2, 3, 4, 5, 6;
  v << 1, 2, 3, 4, 5, 6;
   v(0,0).d_ = 1.0;
   v(0,1).d_ = 1.0;
   v(0,2).d_ = 1.0;
   v(1,0).d_ = 1.0;
   v(1,1).d_ = 1.0;
   v(1,2).d_ = 1.0;
  
  fvar<fvar<double> > output;
  output = sum(d);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());
  EXPECT_FLOAT_EQ( 0.0, output.d_.val());
                   
  output = sum(v);
  EXPECT_FLOAT_EQ(21.0, output.val_.val());
  EXPECT_FLOAT_EQ( 6.0, output.d_.val());

  d.resize(0, 0);
  v.resize(0, 0);
  EXPECT_FLOAT_EQ(0.0, sum(d));
  EXPECT_FLOAT_EQ(0.0, sum(v).val_.val());
  EXPECT_FLOAT_EQ(0.0, sum(v).d_.val());
}
