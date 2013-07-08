#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(log10,AgradFvar) {
  using stan::agrad::fvar;
  using std::log;
  using std::isnan;
  using std::log10;

  fvar<double> x(0.5,1.0);
  
  fvar<double> a = log10(x);
  EXPECT_FLOAT_EQ(log10(0.5), a.val_);
  EXPECT_FLOAT_EQ(1 / (0.5 * log(10)), a.d_);

  fvar<double> b = 2 * log10(x) + 4;
  EXPECT_FLOAT_EQ(2 * log10(0.5) + 4, b.val_);
  EXPECT_FLOAT_EQ(2 / (0.5 * log(10)), b.d_);

  fvar<double> c = -log10(x) + 5;
  EXPECT_FLOAT_EQ(-log10(0.5) + 5, c.val_);
  EXPECT_FLOAT_EQ(-1 / (0.5 * log(10)), c.d_);

  fvar<double> d = -3 * log10(x) + 5 * x;
  EXPECT_FLOAT_EQ(-3 * log10(0.5) + 5 * 0.5, d.val_);
  EXPECT_FLOAT_EQ(-3 / (0.5 * log(10)) + 5, d.d_);

  fvar<double> y(-0.5,1.0);
  fvar<double> e = log10(y);
  isnan(e.val_);
  isnan(e.d_);

  fvar<double> z(0.0,1.0);
  fvar<double> f = log10(z);
  isnan(f.val_);
  isnan(f.d_);
}

TEST(log10,AgradFvarVar_1stderiv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::log;

  fvar<var> x(0.5,1.3);
  fvar<var> a = log10(x);

  EXPECT_FLOAT_EQ(log10(0.5), a.val_.val());
  EXPECT_FLOAT_EQ(1.3 / (0.5 * log(10)), a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(1 / (0.5 * log(10)), g[0]);
}
TEST(log10,AgradFvarVar_2ndderiv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::log;

  fvar<var> x(0.5,1.3);
  fvar<var> a = log10(x);

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(-1.3 / (0.25 * log(10)), g[0]);
}
TEST(log10,AgradFvarFvarDouble) {
  using stan::agrad::fvar;
  using std::log;

  fvar<fvar<double> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  fvar<fvar<double> > a = log10(x);

  EXPECT_FLOAT_EQ(log10(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(1 / (0.5 * log(10)), a.val_.d_);
  EXPECT_FLOAT_EQ(0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > y;
  y.val_.val_ = 0.5;
  y.d_.val_ = 1.0;

  a = log10(y);
  EXPECT_FLOAT_EQ(log10(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(1 / (0.5 * log(10)), a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);
}
TEST(log10,AgradFvarFvarVar_1stderiv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::log;

  fvar<fvar<var> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  fvar<fvar<var> > a = log10(x);

  EXPECT_FLOAT_EQ(log10(0.5), a.val_.val_.val());
  EXPECT_FLOAT_EQ(1 / (0.5 * log(10)), a.val_.d_.val());
  EXPECT_FLOAT_EQ(0, a.d_.val_.val());
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.val_.val_.grad(p,g);
  EXPECT_FLOAT_EQ(1.0 / (0.5 * log(10)), g[0]);

  fvar<fvar<var> > y;
  y.val_.val_ = 0.5;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > b = log10(y);
  EXPECT_FLOAT_EQ(log10(0.5), b.val_.val_.val());
  EXPECT_FLOAT_EQ(0, b.val_.d_.val());
  EXPECT_FLOAT_EQ(1 / (0.5 * log(10)), b.d_.val_.val());
  EXPECT_FLOAT_EQ(0, b.d_.d_.val());

  AVEC q = createAVEC(y.val_.val_);
  VEC r;
  b.val_.val_.grad(q,r);
  EXPECT_FLOAT_EQ(1.0 / (0.5 * log(10)), r[0]);
}
TEST(log10,AgradFvarFvarVar_2ndderiv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::log;

  fvar<fvar<var> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  fvar<fvar<var> > a = log10(x);

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.val_.d_.grad(p,g);
  EXPECT_FLOAT_EQ(-1.0 / (0.25 * log(10)), g[0]);

  fvar<fvar<var> > y;
  y.val_.val_ = 0.5;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > b = log10(y);

  AVEC q = createAVEC(y.val_.val_);
  VEC r;
  b.d_.val_.grad(q,r);
  EXPECT_FLOAT_EQ(-1.0 / (0.5 * 0.5 * log(10)), r[0]);
}
