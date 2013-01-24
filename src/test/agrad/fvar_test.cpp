#include <gtest/gtest.h>

#include <iostream>

#include <boost/math/special_functions/fpclassify.hpp>

#include <stan/agrad/fvar.hpp>

TEST(AgradFvar,fvar) {
  using stan::agrad::fvar;
  typedef stan::agrad::fvar<double> fvd;

  fvar<double> a;
  EXPECT_FLOAT_EQ(0.0, a.val_);
  EXPECT_FLOAT_EQ(0.0, a.d_);

  fvar<double> b(1.9);
  EXPECT_FLOAT_EQ(1.9, b.val_);
  EXPECT_FLOAT_EQ(0.0, b.d_);

  fvar<double> c(1.93, -27.832);
  EXPECT_FLOAT_EQ(1.93, c.val_);
  EXPECT_FLOAT_EQ(-27.832, c.d_);

  fvar<double> d = -c;
  EXPECT_FLOAT_EQ(-1.93, d.val_);
  EXPECT_FLOAT_EQ(27.832, d.d_);

  fvar<double> e(5.0);
  d += e;
  EXPECT_FLOAT_EQ(3.07, d.val_);

  EXPECT_FLOAT_EQ(3.07, (d++).val_);
  EXPECT_FLOAT_EQ(4.07, d.val_);

  EXPECT_FLOAT_EQ(5.07, (++d).val_);
  EXPECT_FLOAT_EQ(5.07, d.val_);
}

TEST(AgradFvar, sqrt) {
  using stan::agrad::fvar;
  using std::sqrt;

  fvar<double> x(0.5);
  x.d_ = 1.0; //derivatives w.r.t. x
  fvar<double> a = sqrt(x);

  EXPECT_FLOAT_EQ(sqrt(0.5), a.val_);
  EXPECT_FLOAT_EQ(1 / (2 * sqrt(0.5)), a.d_);

  fvar<double> b = 3 * sqrt(x) + x;
  EXPECT_FLOAT_EQ(3 * sqrt(0.5) + 0.5, b.val_);
  EXPECT_FLOAT_EQ(3 / (2 * sqrt(0.5)) + 1, b.d_);

  fvar<double> c = -sqrt(x) + 5;
  EXPECT_FLOAT_EQ(-sqrt(0.5) + 5, c.val_);
  EXPECT_FLOAT_EQ(-1 / (2 * sqrt(0.5)), c.d_);

  fvar<double> d = -3 * sqrt(x) + 5 * x;
  EXPECT_FLOAT_EQ(-3 * sqrt(0.5) + 5 * 0.5, d.val_);
  EXPECT_FLOAT_EQ(-3 / (2 * sqrt(0.5)) + 5, d.d_);
}

TEST(AgradFvar, exp) {
  using stan::agrad::fvar;
  using std::exp;

  fvar<double> x(0.5);
  x.d_ = 1.0;   // derivatives w.r.t. x
  
  fvar<double> a = exp(x);
  EXPECT_FLOAT_EQ(exp(0.5), a.val_);
  EXPECT_FLOAT_EQ(exp(0.5), a.d_);

  fvar<double> b = 2 * exp(x) + 4;
  EXPECT_FLOAT_EQ(2 * exp(0.5) + 4, b.val_);
  EXPECT_FLOAT_EQ(2 * exp(0.5), b.d_);

  fvar<double> c = -exp(x) + 5;
  EXPECT_FLOAT_EQ(-exp(0.5) + 5, c.val_);
  EXPECT_FLOAT_EQ(-exp(0.5), c.d_);

  fvar<double> d = -3 * exp(x) + 5 * x;
  EXPECT_FLOAT_EQ(-3 * exp(0.5) + 5 * 0.5, d.val_);
  EXPECT_FLOAT_EQ(-3 * exp(0.5) + 5, d.d_);
}

TEST(AgradFvar, sin) {
  using stan::agrad::fvar;
  using std::sin;
  using std::cos;

  fvar<double> x(0.5);
  x.d_ = 1.0;   // derivatives w.r.t. x
  
  fvar<double> a = sin(x);
  EXPECT_FLOAT_EQ(sin(0.5), a.val_);
  EXPECT_FLOAT_EQ(cos(0.5), a.d_);

  fvar<double> b = 2 * sin(x) + 4;
  EXPECT_FLOAT_EQ(2 * sin(0.5) + 4, b.val_);
  EXPECT_FLOAT_EQ(2 * cos(0.5), b.d_);

  fvar<double> c = -sin(x) + 5;
  EXPECT_FLOAT_EQ(-sin(0.5) + 5, c.val_);
  EXPECT_FLOAT_EQ(-cos(0.5), c.d_);

  fvar<double> d = -3 * sin(x) + 5 * x;
  EXPECT_FLOAT_EQ(-3 * sin(0.5) + 5 * 0.5, d.val_);
  EXPECT_FLOAT_EQ(-3 * cos(0.5) + 5, d.d_);
}

TEST(AgradFvar, cos) {
  using stan::agrad::fvar;
  using std::sin;
  using std::cos;

  fvar<double> x(0.5);
  x.d_ = 1.0;   // derivatives w.r.t. x
  
  fvar<double> a = cos(x);
  EXPECT_FLOAT_EQ(cos(0.5), a.val_);
  EXPECT_FLOAT_EQ(-sin(0.5), a.d_);

  fvar<double> b = 2 * cos(x) + 4;
  EXPECT_FLOAT_EQ(2 * cos(0.5) + 4, b.val_);
  EXPECT_FLOAT_EQ(2 * -sin(0.5), b.d_);

  fvar<double> c = -cos(x) + 5;
  EXPECT_FLOAT_EQ(-cos(0.5) + 5, c.val_);
  EXPECT_FLOAT_EQ(sin(0.5), c.d_);

  fvar<double> d = -3 * cos(x) + 5 * x;
  EXPECT_FLOAT_EQ(-3 * cos(0.5) + 5 * 0.5, d.val_);
  EXPECT_FLOAT_EQ(-3 * -sin(0.5) + 5, d.d_);
}

TEST(AgradFvar, tan) {
  using stan::agrad::fvar;
  using std::tan;
  using std::cos;

  fvar<double> x(0.5);
  x.d_ = 1.0;   // derivatives w.r.t. x
  
  fvar<double> a = tan(x);
  EXPECT_FLOAT_EQ(tan(0.5), a.val_);
  EXPECT_FLOAT_EQ(1 / (cos(0.5) * cos(0.5)), a.d_);

  fvar<double> b = 2 * tan(x) + 4;
  EXPECT_FLOAT_EQ(2 * tan(0.5) + 4, b.val_);
  EXPECT_FLOAT_EQ(2 / (cos(0.5) * cos(0.5)), b.d_);

  fvar<double> c = -tan(x) + 5;
  EXPECT_FLOAT_EQ(-tan(0.5) + 5, c.val_);
  EXPECT_FLOAT_EQ(-1 / (cos(0.5) * cos(0.5)), c.d_);

  fvar<double> d = -3 * tan(x) + 5 * x;
  EXPECT_FLOAT_EQ(-3 * tan(0.5) + 5 * 0.5, d.val_);
  EXPECT_FLOAT_EQ(-3 / (cos(0.5) * cos(0.5)) + 5, d.d_);
}

