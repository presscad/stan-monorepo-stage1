#include <stan/math/fwd/mat/fun/determinant.hpp>
#include <gtest/gtest.h>
#include <stan/math/fwd/mat/fun/typedefs.hpp>
#include <stan/math/mix/mat/fun/typedefs.hpp>
#include <stan/math/fwd/core/fvar.hpp>
#include <stan/math/rev/mat/fun/multiply.hpp>
#include <test/unit/math/rev/mat/fun/util.hpp>
#include <stan/math/rev/core/operator_addition.hpp>
#include <stan/math/rev/core/operator_divide_equal.hpp>
#include <stan/math/rev/core/operator_division.hpp>
#include <stan/math/rev/core/operator_equal.hpp>
#include <stan/math/rev/core/operator_greater_than.hpp>
#include <stan/math/rev/core/operator_greater_than_or_equal.hpp>
#include <stan/math/rev/core/operator_less_than.hpp>
#include <stan/math/rev/core/operator_less_than_or_equal.hpp>
#include <stan/math/rev/core/operator_minus_equal.hpp>
#include <stan/math/rev/core/operator_multiplication.hpp>
#include <stan/math/rev/core/operator_multiply_equal.hpp>
#include <stan/math/rev/core/operator_not_equal.hpp>
#include <stan/math/rev/core/operator_plus_equal.hpp>
#include <stan/math/rev/core/operator_subtraction.hpp>
#include <stan/math/rev/core/operator_unary_decrement.hpp>
#include <stan/math/rev/core/operator_unary_increment.hpp>
#include <stan/math/rev/core/operator_unary_negative.hpp>
#include <stan/math/rev/core/operator_unary_not.hpp>
#include <stan/math/rev/core/operator_unary_plus.hpp>
#include <stan/math/fwd/core/operator_addition.hpp>
#include <stan/math/fwd/core/operator_division.hpp>
#include <stan/math/fwd/core/operator_equal.hpp>
#include <stan/math/fwd/core/operator_greater_than.hpp>
#include <stan/math/fwd/core/operator_greater_than_or_equal.hpp>
#include <stan/math/fwd/core/operator_less_than.hpp>
#include <stan/math/fwd/core/operator_less_than_or_equal.hpp>
#include <stan/math/fwd/core/operator_multiplication.hpp>
#include <stan/math/fwd/core/operator_not_equal.hpp>
#include <stan/math/fwd/core/operator_subtraction.hpp>
#include <stan/math/fwd/core/operator_unary_minus.hpp>
#include <stan/math/fwd/scal/fun/abs.hpp>
#include <stan/math/rev/scal/fun/abs.hpp>

TEST(AgradFwdMatrixDeterminant,matrix_fd) {
  using stan::agrad::matrix_fd;
  using stan::math::matrix_d;
  using stan::agrad::fvar;
  
  matrix_fd a(2,2);
  a << 2.0, 3.0, 5.0, 7.0;
   a(0,0).d_ = 1.0;
   a(0,1).d_ = 1.0;
   a(1,0).d_ = 1.0;
   a(1,1).d_ = 1.0;

  fvar<double> a_det = stan::agrad::determinant(a);
   
  EXPECT_FLOAT_EQ(-1,a_det.val_);
  EXPECT_FLOAT_EQ(1,a_det.d_);

  EXPECT_THROW(determinant(matrix_fd(2,3)), std::invalid_argument);
}
TEST(AgradFwdMatrixDeterminant,matrix_fv_1stDeriv) {
  using stan::agrad::matrix_fv;
  using stan::math::matrix_d;
  using stan::agrad::fvar;
  using stan::agrad::var;

  fvar<var> b(2.0,1.0);
  fvar<var> c(3.0,1.0);
  fvar<var> d(5.0,1.0);
  fvar<var> e(7.0,1.0);

  matrix_fv a(2,2);
  a << b,c,d,e;

  fvar<var> a_det = stan::agrad::determinant(a);

  EXPECT_FLOAT_EQ(-1,a_det.val_.val());
  EXPECT_FLOAT_EQ(1,a_det.d_.val());

  EXPECT_THROW(determinant(matrix_fv(2,3)), std::invalid_argument);

  AVEC z = createAVEC(b.val(),c.val(),d.val(),e.val());
  VEC h;
  a_det.val_.grad(z,h);
  EXPECT_FLOAT_EQ(7.0,h[0]);
  EXPECT_FLOAT_EQ(-5.0,h[1]);
  EXPECT_FLOAT_EQ(-3.0,h[2]);
  EXPECT_FLOAT_EQ(2.0,h[3]);
}
TEST(AgradFwdMatrixDeterminant,matrix_fv_2ndDeriv) {
  using stan::agrad::matrix_fv;
  using stan::math::matrix_d;
  using stan::agrad::fvar;
  using stan::agrad::var;

  fvar<var> b(2.0,1.0);
  fvar<var> c(3.0,1.0);
  fvar<var> d(5.0,1.0);
  fvar<var> e(7.0,1.0);

  matrix_fv a(2,2);
  a << b,c,d,e;

  fvar<var> a_det = stan::agrad::determinant(a);

  AVEC z = createAVEC(b.val(),c.val(),d.val(),e.val());
  VEC h;
  a_det.d_.grad(z,h);
  EXPECT_FLOAT_EQ(1.0,h[0]);
  EXPECT_FLOAT_EQ(-1.0,h[1]);
  EXPECT_FLOAT_EQ(-1.0,h[2]);
  EXPECT_FLOAT_EQ(1.0,h[3]);
}
TEST(AgradFwdMatrixDeterminant,matrix_ffd) {
  using stan::agrad::matrix_ffd;
  using stan::agrad::fvar;

  fvar<fvar<double> > a,b,c,d;
  a.val_.val_ = 2.0;
  a.d_.val_ = 1.0;  
  b.val_.val_ = 3.0;
  b.d_.val_ = 1.0;
  c.val_.val_ = 5.0;
  c.d_.val_ = 1.0;
  d.val_.val_ = 7.0;
  d.d_.val_ = 1.0; 

  matrix_ffd g(2,2);
  g << a,b,c,d;

  fvar<fvar<double> > a_det = stan::agrad::determinant(g);

   EXPECT_FLOAT_EQ(-1,a_det.val_.val());
   EXPECT_FLOAT_EQ(1,a_det.d_.val());

  EXPECT_THROW(determinant(matrix_ffd(2,3)), std::invalid_argument);
}
TEST(AgradFwdMatrixDeterminant,matrix_ffv_1stDeriv) {
  using stan::agrad::matrix_ffv;
  using stan::math::matrix_d;
  using stan::agrad::fvar;
  using stan::agrad::var;

  fvar<fvar<var> > b(2.0,1.0);
  fvar<fvar<var> > c(3.0,1.0);
  fvar<fvar<var> > d(5.0,1.0);
  fvar<fvar<var> > e(7.0,1.0);

  matrix_ffv a(2,2);
  a << b,c,d,e;

  fvar<fvar<var> > a_det = stan::agrad::determinant(a);

  EXPECT_FLOAT_EQ(-1,a_det.val_.val().val());
  EXPECT_FLOAT_EQ(1,a_det.d_.val().val());

  EXPECT_THROW(determinant(matrix_ffv(2,3)), std::invalid_argument);

  AVEC z = createAVEC(b.val().val(),c.val().val(),d.val().val(),e.val().val());
  VEC h;
  a_det.val_.val().grad(z,h);
  EXPECT_FLOAT_EQ(7.0,h[0]);
  EXPECT_FLOAT_EQ(-5.0,h[1]);
  EXPECT_FLOAT_EQ(-3.0,h[2]);
  EXPECT_FLOAT_EQ(2.0,h[3]);
}
TEST(AgradFwdMatrixDeterminant,matrix_ffv_2ndDeriv_1) {
  using stan::agrad::matrix_ffv;
  using stan::math::matrix_d;
  using stan::agrad::fvar;
  using stan::agrad::var;

  fvar<fvar<var> > b(2.0,1.0);
  fvar<fvar<var> > c(3.0,1.0);
  fvar<fvar<var> > d(5.0,1.0);
  fvar<fvar<var> > e(7.0,1.0);

  matrix_ffv a(2,2);
  a << b,c,d,e;

  fvar<fvar<var> > a_det = stan::agrad::determinant(a);

  AVEC z = createAVEC(b.val().val(),c.val().val(),d.val().val(),e.val().val());
  VEC h;
  a_det.val().d_.grad(z,h);
  EXPECT_FLOAT_EQ(0.0,h[0]);
  EXPECT_FLOAT_EQ(0.0,h[1]);
  EXPECT_FLOAT_EQ(0.0,h[2]);
  EXPECT_FLOAT_EQ(0.0,h[3]);
}

TEST(AgradFwdMatrixDeterminant,matrix_ffv_2ndDeriv_2) {
  using stan::agrad::matrix_ffv;
  using stan::math::matrix_d;
  using stan::agrad::fvar;
  using stan::agrad::var;

  fvar<fvar<var> > b(2.0,1.0);
  fvar<fvar<var> > c(3.0,1.0);
  fvar<fvar<var> > d(5.0,1.0);
  fvar<fvar<var> > e(7.0,1.0);

  matrix_ffv a(2,2);
  a << b,c,d,e;

  fvar<fvar<var> > a_det = stan::agrad::determinant(a);

  AVEC z = createAVEC(b.val().val(),c.val().val(),d.val().val(),e.val().val());
  VEC h;
  a_det.d_.val().grad(z,h);
  EXPECT_FLOAT_EQ(1.0,h[0]);
  EXPECT_FLOAT_EQ(-1.0,h[1]);
  EXPECT_FLOAT_EQ(-1.0,h[2]);
  EXPECT_FLOAT_EQ(1.0,h[3]);
}

TEST(AgradFwdMatrixDeterminant,matrix_ffv_3rdDeriv) {
  using stan::agrad::matrix_ffv;
  using stan::math::matrix_d;
  using stan::agrad::fvar;
  using stan::agrad::var;

  fvar<fvar<var> > b(2.0,1.0);
  fvar<fvar<var> > c(3.0,1.0);
  fvar<fvar<var> > d(5.0,1.0);
  fvar<fvar<var> > e(7.0,1.0);
  b.val_.d_ = 1.0;
  c.val_.d_ = 1.0;
  d.val_.d_ = 1.0;
  e.val_.d_ = 1.0;

  matrix_ffv a(2,2);
  a << b,c,d,e;

  fvar<fvar<var> > a_det = stan::agrad::determinant(a);

  AVEC z = createAVEC(b.val().val(),c.val().val(),d.val().val(),e.val().val());
  VEC h;
  a_det.d_.d_.grad(z,h);
  EXPECT_NEAR(0.0,h[0],1e-8);
  EXPECT_NEAR(0.0,h[1],1e-8);
  EXPECT_NEAR(0.0,h[2],1e-8);
  EXPECT_NEAR(0.0,h[3],1e-8);
}
