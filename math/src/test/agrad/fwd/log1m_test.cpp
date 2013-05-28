#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <stan/math/functions/log1m.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, log1m){
  using stan::agrad::fvar;
  using stan::math::log1m;
  using std::isnan;

  fvar<double> x(0.5);
  fvar<double> y(1.0);
  fvar<double> z(2.0);
  x.d_ = 1.0;
  y.d_ = 2.0;
  z.d_ = 3.0;

  fvar<double> a = log1m(x);
  EXPECT_FLOAT_EQ(log1m(0.5), a.val_);
  EXPECT_FLOAT_EQ(-1 / (1 - 0.5), a.d_);

  fvar<double> b = log1m(y);
  isnan(b.val_);
  isnan(b.d_);

  fvar<double> c = log1m(z);
  isnan(c.val_);
  isnan(c.d_);
}

TEST(AgradFvarVar, log1m) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::log1m;

  fvar<var> x;
  x.val_ = 0.5;
  x.d_ = 1.3;
  fvar<var> a = log1m(x);

  EXPECT_FLOAT_EQ(log1m(0.5), a.val_.val());
  EXPECT_FLOAT_EQ(-1.3 / (0.5), a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(-1 / (0.5), g[0]);

  y = createAVEC(x.d_);
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(0, g[0]);
}

TEST(AgradFvarFvar, log1m) {
  using stan::agrad::fvar;
  using stan::math::log1m;

  fvar<fvar<double> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;
  x.d_.val_ = 0.0;
  x.d_.d_ = 0.0;

  fvar<fvar<double> > a = log1m(x);

  EXPECT_FLOAT_EQ(log1m(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(-1 / (0.5), a.val_.d_);
  EXPECT_FLOAT_EQ(0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > y;
  y.val_.val_ = 0.5;
  y.val_.d_ = 0.0;
  y.d_.val_ = 1.0;
  y.d_.d_ = 0.0;

  a = log1m(y);
  EXPECT_FLOAT_EQ(log1m(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(-1 / (0.5), a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);
}

