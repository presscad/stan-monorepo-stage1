#include <gtest/gtest.h>
#include <test/unit/math/rev/mat/fun/util.hpp>
#include <stan/math/prim/scal/fun/bessel_second_kind.hpp>
#include <test/unit/math/fwd/scal/fun/nan_util.hpp>
#include <stan/math/fwd/mat/fun/Eigen_NumTraits.hpp>
#include <stan/math/fwd/scal/fun/bessel_second_kind.hpp>
#include <stan/math/fwd/scal/fun/cos.hpp>
#include <stan/math/fwd/scal/fun/ceil.hpp>
#include <stan/math/fwd/scal/fun/floor.hpp>
#include <stan/math/fwd/scal/fun/log.hpp>
#include <stan/math/fwd/scal/fun/pow.hpp>
#include <stan/math/fwd/scal/fun/sin.hpp>
#include <stan/math/fwd/scal/fun/sqrt.hpp>
#include <stan/math/fwd/scal/fun/operator_addition.hpp>
#include <stan/math/fwd/scal/fun/operator_division.hpp>
#include <stan/math/fwd/scal/fun/operator_equal.hpp>
#include <stan/math/fwd/scal/fun/operator_greater_than.hpp>
#include <stan/math/fwd/scal/fun/operator_greater_than_or_equal.hpp>
#include <stan/math/fwd/scal/fun/operator_less_than.hpp>
#include <stan/math/fwd/scal/fun/operator_less_than_or_equal.hpp>
#include <stan/math/fwd/scal/fun/operator_multiplication.hpp>
#include <stan/math/fwd/scal/fun/operator_not_equal.hpp>
#include <stan/math/fwd/scal/fun/operator_subtraction.hpp>
#include <stan/math/fwd/scal/fun/operator_unary_minus.hpp>
#include <stan/math/rev/scal/fun/operator_addition.hpp>
#include <stan/math/rev/scal/fun/operator_divide_equal.hpp>
#include <stan/math/rev/scal/fun/operator_division.hpp>
#include <stan/math/rev/scal/fun/operator_equal.hpp>
#include <stan/math/rev/scal/fun/operator_greater_than.hpp>
#include <stan/math/rev/scal/fun/operator_greater_than_or_equal.hpp>
#include <stan/math/rev/scal/fun/operator_less_than.hpp>
#include <stan/math/rev/scal/fun/operator_less_than_or_equal.hpp>
#include <stan/math/rev/scal/fun/operator_minus_equal.hpp>
#include <stan/math/rev/scal/fun/operator_multiplication.hpp>
#include <stan/math/rev/scal/fun/operator_multiply_equal.hpp>
#include <stan/math/rev/scal/fun/operator_not_equal.hpp>
#include <stan/math/rev/scal/fun/operator_plus_equal.hpp>
#include <stan/math/rev/scal/fun/operator_subtraction.hpp>
#include <stan/math/rev/scal/fun/operator_unary_decrement.hpp>
#include <stan/math/rev/scal/fun/operator_unary_increment.hpp>
#include <stan/math/rev/scal/fun/operator_unary_negative.hpp>
#include <stan/math/rev/scal/fun/operator_unary_not.hpp>
#include <stan/math/rev/scal/fun/operator_unary_plus.hpp>
#include <stan/math/rev/scal/fun/value_of_rec.hpp>
#include <stan/math/rev/scal/fun/bessel_second_kind.hpp>
#include <stan/math/rev/scal/fun/cos.hpp>
#include <stan/math/rev/scal/fun/ceil.hpp>
#include <stan/math/rev/scal/fun/floor.hpp>
#include <stan/math/rev/scal/fun/log.hpp>
#include <stan/math/rev/scal/fun/pow.hpp>
#include <stan/math/rev/scal/fun/sin.hpp>
#include <stan/math/rev/scal/fun/sqrt.hpp>
#include <stan/math/rev/scal/meta/numeric_limits.hpp>
#include <stan/math/rev/mat/fun/Eigen_NumTraits.hpp>

TEST(AgradFwdBesselSecondKind,Fvar) {
  using stan::agrad::fvar;
  using stan::agrad::bessel_second_kind;

  fvar<double> a(4.0,1.0);
  int b = 0;
  fvar<double> x = bessel_second_kind(b,a);
  EXPECT_FLOAT_EQ(-0.01694073932506499190, x.val_);
  EXPECT_FLOAT_EQ(-0.39792571055710000525, x.d_);

  fvar<double> c(3.0,2.0);

  x = bessel_second_kind(1, c);
  EXPECT_FLOAT_EQ(0.32467442479179997, x.val_);
  EXPECT_FLOAT_EQ(0.53725040349771411, x.d_);

  EXPECT_THROW(bessel_second_kind(0, -a), std::domain_error);
}

TEST(AgradFwdBesselSecondKind,FvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::bessel_second_kind;

  fvar<var> z(3.0,2.0);
  fvar<var> a = bessel_second_kind(1,z);

  EXPECT_FLOAT_EQ(bessel_second_kind(1, 3.0), a.val_.val());
  EXPECT_FLOAT_EQ(0.53725040349771411, a.d_.val());

  AVEC y = createAVEC(z.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(0.53725040349771411 / 2.0, g[0]);
}
TEST(AgradFwdBesselSecondKind,FvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::bessel_second_kind;

  fvar<var> z(3.0,2.0);
  fvar<var> a = bessel_second_kind(1,z);

  AVEC y = createAVEC(z.val_);
  VEC g;
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(-0.75628245, g[0]);
}
TEST(AgradFwdBesselSecondKind,FvarFvarDouble) {
  using stan::agrad::fvar;
  using stan::math::bessel_second_kind;

  fvar<fvar<double> > x;
  x.val_.val_ = 3.0;
  x.val_.d_ = 2.0;

  fvar<fvar<double> > y;
  y.val_.val_ = 3.0;
  y.d_.val_ = 2.0;

  fvar<fvar<double> > a = stan::agrad::bessel_second_kind(1,y);

  EXPECT_FLOAT_EQ(stan::math::bessel_second_kind(1,3.0), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(0.53725040349771411, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > b = stan::agrad::bessel_second_kind(1, x);

  EXPECT_FLOAT_EQ(stan::math::bessel_second_kind(1,3.0), b.val_.val_);
  EXPECT_FLOAT_EQ(0.53725040349771411, b.val_.d_);
  EXPECT_FLOAT_EQ(0, b.d_.val_);
  EXPECT_FLOAT_EQ(0, b.d_.d_);
}
TEST(AgradFwdBesselSecondKind,FvarFvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::bessel_second_kind;

  fvar<fvar<var> > y;
  y.val_.val_ = 3.0;
  y.d_.val_ = 2.0;

  fvar<fvar<var> > a = stan::agrad::bessel_second_kind(1,y);

  EXPECT_FLOAT_EQ(stan::math::bessel_second_kind(1,3.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0, a.val_.d_.val());
  EXPECT_FLOAT_EQ(0.53725040349771411, a.d_.val_.val());
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(y.val_.val_);
  VEC g;
  a.val_.val_.grad(p,g);
  EXPECT_FLOAT_EQ(0.53725040349771411 / 2.0, g[0]);

  fvar<fvar<var> > x;
  x.val_.val_ = 3.0;
  x.val_.d_ = 2.0;

  fvar<fvar<var> > b = stan::agrad::bessel_second_kind(1, x);

  EXPECT_FLOAT_EQ(stan::math::bessel_second_kind(1,3.0), b.val_.val_.val());
  EXPECT_FLOAT_EQ(0.53725040349771411, b.val_.d_.val());
  EXPECT_FLOAT_EQ(0, b.d_.val_.val());
  EXPECT_FLOAT_EQ(0, b.d_.d_.val());

  AVEC q = createAVEC(x.val_.val_);
  VEC r;
  b.val_.val_.grad(q,r);
  EXPECT_FLOAT_EQ(0.53725040349771411 / 2.0, r[0]);
}
TEST(AgradFwdBesselSecondKind,FvarFvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::bessel_second_kind;

  fvar<fvar<var> > y;
  y.val_.val_ = 3.0;
  y.d_.val_ = 2.0;

  fvar<fvar<var> > a = stan::agrad::bessel_second_kind(1,y);

  AVEC p = createAVEC(y.val_.val_);
  VEC g;
  a.d_.val_.grad(p,g);
  EXPECT_FLOAT_EQ(-0.75628245, g[0]);

  fvar<fvar<var> > x;
  x.val_.val_ = 3.0;
  x.val_.d_ = 2.0;

  fvar<fvar<var> > b = stan::agrad::bessel_second_kind(1, x);

  AVEC q = createAVEC(x.val_.val_);
  VEC r;
  b.val_.d_.grad(q,r);
  EXPECT_FLOAT_EQ(-0.75628245, r[0]);
}
TEST(AgradFwdBesselSecondKind,FvarFvarVar_3rdDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::bessel_second_kind;

  fvar<fvar<var> > y;
  y.val_.val_ = 3.0;
  y.d_.val_ = 1.0;
  y.val_.d_ = 1.0;

  fvar<fvar<var> > a = stan::agrad::bessel_second_kind(1,y);

  AVEC p = createAVEC(y.val_.val_);
  VEC g;
  a.d_.d_.grad(p,g);
  EXPECT_FLOAT_EQ(-0.1069335956566158198, g[0]);
}

struct bessel_second_kind_fun {
  template <typename T0>
  inline T0
  operator()(const T0& arg1) const {
    return bessel_second_kind(1,arg1);
  }
};

TEST(AgradFwdBesselSecondKind,bessel_second_kind_NaN) {
  bessel_second_kind_fun bessel_second_kind_;
  test_nan(bessel_second_kind_,false);
}
