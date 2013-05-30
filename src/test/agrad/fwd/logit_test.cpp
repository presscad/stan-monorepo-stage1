#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <stan/math/functions/logit.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, logit) {
  using stan::agrad::fvar;
  using stan::math::logit;
  using std::isnan;

  fvar<double> x(0.5,1.0);

  fvar<double> a = logit(x);
  EXPECT_FLOAT_EQ(logit(0.5), a.val_);
  EXPECT_FLOAT_EQ(1 / (0.5 - 0.5 * 0.5), a.d_);

  fvar<double> y(-1.2,1.0);

  fvar<double> b = logit(y);
  isnan(b.val_);
  isnan(b.d_);

  fvar<double> z(1.5,1.0);

  fvar<double> c = logit(z);
  isnan(c.val_);
  isnan(c.d_);
}

TEST(AgradFvarVar, logit) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::logit;

  fvar<var> x(0.5,1.3);
  fvar<var> a = logit(x);

  EXPECT_FLOAT_EQ(logit(0.5), a.val_.val());
  EXPECT_FLOAT_EQ(1.3 / (0.5 - 0.25), a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(1 / (0.5 - 0.25), g[0]);

  y = createAVEC(x.d_);
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(0, g[0]);
}

TEST(AgradFvarFvar, log) {
  using stan::agrad::fvar;
  using stan::math::logit;

  fvar<fvar<double> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  fvar<fvar<double> > a = logit(x);

  EXPECT_FLOAT_EQ(logit(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(1 / (0.5 - 0.25), a.val_.d_);
  EXPECT_FLOAT_EQ(0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > y;
  y.val_.val_ = 0.5;
  y.d_.val_ = 1.0;

  a = logit(y);
  EXPECT_FLOAT_EQ(logit(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(1 / (0.5 - 0.25), a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);
}
