#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, cbrt) {
  using stan::agrad::fvar;
  using boost::math::cbrt;
  using std::isnan;

  fvar<double> x(0.5,1.0);
  fvar<double> a = cbrt(x);

  EXPECT_FLOAT_EQ(cbrt(0.5), a.val_);
  EXPECT_FLOAT_EQ(1 / (3 * pow(0.5, 2.0 / 3.0)), a.d_);

  fvar<double> b = 3 * cbrt(x) + x;
  EXPECT_FLOAT_EQ(3 * cbrt(0.5) + 0.5, b.val_);
  EXPECT_FLOAT_EQ(3 / (3 * pow(0.5, 2.0 / 3.0)) + 1, b.d_);

  fvar<double> c = -cbrt(x) + 5;
  EXPECT_FLOAT_EQ(-cbrt(0.5) + 5, c.val_);
  EXPECT_FLOAT_EQ(-1 / (3 * pow(0.5, 2.0 / 3.0)), c.d_);

  fvar<double> d = -3 * cbrt(x) + 5 * x;
  EXPECT_FLOAT_EQ(-3 * cbrt(0.5) + 5 * 0.5, d.val_);
  EXPECT_FLOAT_EQ(-3 / (3 * pow(0.5, 2.0 / 3.0)) + 5, d.d_);

  fvar<double> e = -3 * cbrt(-x) + 5 * x;
  EXPECT_FLOAT_EQ(-3 * cbrt(-0.5) + 5 * 0.5, e.val_);
  EXPECT_FLOAT_EQ(3 / (3 * cbrt(-0.5) * cbrt(-0.5)) + 5, e.d_);

  fvar<double> y(0.0,1.0);
  fvar<double> f = cbrt(y);
  EXPECT_FLOAT_EQ(cbrt(0.0), f.val_);
  isnan(f.d_);
}

TEST(AgradFvarVar, cbrt) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using boost::math::cbrt;

  fvar<var> x(1.5,1.3);
  fvar<var> a = cbrt(x);

  EXPECT_FLOAT_EQ(cbrt(1.5), a.val_.val());
  EXPECT_FLOAT_EQ(1.3 / (3 * cbrt(1.5) * cbrt(1.5)), a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(1.0 / (3.0 * cbrt(1.5) * cbrt(1.5)), g[0]);
}

TEST(AgradFvarFvar, cbrt) {
  using stan::agrad::fvar;
  using boost::math::cbrt;

  fvar<fvar<double> > x;
  x.val_.val_ = 1.5;
  x.val_.d_ = 2.0;

  fvar<fvar<double> > a = cbrt(x);

  EXPECT_FLOAT_EQ(cbrt(1.5), a.val_.val_);
  EXPECT_FLOAT_EQ(2.0 / (3.0 * cbrt(1.5) * cbrt(1.5)), a.val_.d_);
  EXPECT_FLOAT_EQ(0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > y;
  y.val_.val_ = 1.5;
  y.d_.val_ = 2.0;

  a = cbrt(y);
  EXPECT_FLOAT_EQ(cbrt(1.5), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(2.0 / (3.0 * cbrt(1.5) * cbrt(1.5)), a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);
}
