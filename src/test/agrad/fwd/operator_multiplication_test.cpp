#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, operatorMultiplication) {
  using stan::agrad::fvar;

  fvar<double> x1(0.5);
  fvar<double> x2(0.4);
  x1.d_ = 1.0;
  x2.d_ = 2.0;
  fvar<double> a = x1 * x2;

  EXPECT_FLOAT_EQ(0.5 * 0.4, a.val_);
  EXPECT_FLOAT_EQ(1.0 * 0.4 + 2.0 * 0.5, a.d_);

  fvar<double> b = -x1 * x2;
  EXPECT_FLOAT_EQ(-0.5 * 0.4, b.val_);
  EXPECT_FLOAT_EQ(-1 * 0.4 - 2.0 * 0.5, b.d_);

  fvar<double> c = -3 * x1 * x2;
  EXPECT_FLOAT_EQ(-3 * 0.5 * 0.4, c.val_);
  EXPECT_FLOAT_EQ(3 * (-1 * 0.4 - 2.0 * 0.5), c.d_);

  fvar<double> x3(0.5);
  x3.d_ = 1.0;

  fvar<double> e = 2 * x3;
  EXPECT_FLOAT_EQ(2 * 0.5, e.val_);
  EXPECT_FLOAT_EQ(2 * 1.0, e.d_);

  fvar<double> f = x3 * -2;
  EXPECT_FLOAT_EQ(0.5 * -2, f.val_);
  EXPECT_FLOAT_EQ(1.0 * -2, f.d_);
}

TEST(AgradFvarVar, operatorMultiplication) {
  using stan::agrad::fvar;
  using stan::agrad::var;

  fvar<var> x;
  x.val_ = 0.5;
  x.d_ = 1.3;

  fvar<var> z;
  z.val_ = 0.5;
  z.d_ = 1.3;
  fvar<var> a = x * z;

  EXPECT_FLOAT_EQ(0.25, a.val_.val());
  EXPECT_FLOAT_EQ(1.3, a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(0.5, g[0]);
  std::isnan(g[1]);

  y = createAVEC(x.d_);
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(0, g[0]);
  std::isnan(g[1]);
}

TEST(AgradFvarFvar, operatorMultiplication) {
  using stan::agrad::fvar;

  fvar<fvar<double> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;
  x.d_.val_ = 0.0;
  x.d_.d_ = 0.0;

  fvar<fvar<double> > y;
  y.val_.val_ = 0.5;
  y.val_.d_ = 0.0;
  y.d_.val_ = 1.0;
  y.d_.d_ = 0.0;

  fvar<fvar<double> > z = x * y;
  EXPECT_FLOAT_EQ(0.25, z.val_.val_);
  EXPECT_FLOAT_EQ(0.5, z.val_.d_);
  EXPECT_FLOAT_EQ(0.5, z.d_.val_);
  EXPECT_FLOAT_EQ(1, z.d_.d_);
}
