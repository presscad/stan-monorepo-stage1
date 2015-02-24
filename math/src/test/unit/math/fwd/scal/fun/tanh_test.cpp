#include <gtest/gtest.h>
#include <stan/math/rev/core.hpp>
#include <test/unit/math/rev/mat/fun/util.hpp>
#include <test/unit/math/fwd/scal/fun/nan_util.hpp>
#include <stan/math/fwd/core.hpp>
#include <stan/math/fwd/scal/fun/tanh.hpp>
#include <stan/math/rev/scal/fun/tanh.hpp>

class AgradFwdTanh : public testing::Test {
  void SetUp() {
    stan::agrad::recover_memory();
  }
};


TEST_F(AgradFwdTanh, Fvar) {
  using stan::agrad::fvar;
  using std::tanh;

  fvar<double> x(0.5,1.0);
  fvar<double> a = tanh(x);
  EXPECT_FLOAT_EQ(tanh(0.5), a.val_);
  EXPECT_FLOAT_EQ(1 - tanh(0.5) * tanh(0.5), a.d_);

  fvar<double> y(-1.2,1.0);
  fvar<double> b = tanh(y);
  EXPECT_FLOAT_EQ(tanh(-1.2), b.val_);
  EXPECT_FLOAT_EQ(1 - tanh(-1.2) * tanh(-1.2), b.d_);

  fvar<double> c = tanh(-x);
  EXPECT_FLOAT_EQ(tanh(-0.5), c.val_);
  EXPECT_FLOAT_EQ(-1 * (1 - tanh(-0.5) * tanh(-0.5)), c.d_);
}

TEST_F(AgradFwdTanh, FvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::tanh;

  fvar<var> x(1.5,1.3);
  fvar<var> a = tanh(x);

  EXPECT_FLOAT_EQ(tanh(1.5), a.val_.val());
  EXPECT_FLOAT_EQ(1.3 * (1.0 - tanh(1.5) * tanh(1.5)), a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ((1.0 - tanh(1.5) * tanh(1.5)), g[0]);
}
TEST_F(AgradFwdTanh, FvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::tanh;
  using std::cosh;

  fvar<var> x(1.5,1.3);
  fvar<var> a = tanh(x);

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(1.3 * -2.0 * tanh(1.5) / (cosh(1.5) * cosh(1.5)), g[0]);
}

TEST_F(AgradFwdTanh, FvarFvarDouble) {
  using stan::agrad::fvar;
  using std::tanh;

  fvar<fvar<double> > x;
  x.val_.val_ = 1.5;
  x.val_.d_ = 2.0;

  fvar<fvar<double> > a = tanh(x);

  EXPECT_FLOAT_EQ(tanh(1.5), a.val_.val_);
  EXPECT_FLOAT_EQ(2.0 * (1.0 - tanh(1.5) * tanh(1.5)), a.val_.d_);
  EXPECT_FLOAT_EQ(0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > y;
  y.val_.val_ = 1.5;
  y.d_.val_ = 2.0;

  a = tanh(y);
  EXPECT_FLOAT_EQ(tanh(1.5), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(2.0 * (1.0 - tanh(1.5) * tanh(1.5)), a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);
}

TEST_F(AgradFwdTanh, FvarFvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::tanh;

  fvar<fvar<var> > x;
  x.val_.val_ = 1.5;
  x.val_.d_ = 2.0;

  fvar<fvar<var> > a = tanh(x);

  EXPECT_FLOAT_EQ(tanh(1.5), a.val_.val_.val());
  EXPECT_FLOAT_EQ(2.0 * (1.0 - tanh(1.5) * tanh(1.5)), a.val_.d_.val());
  EXPECT_FLOAT_EQ(0, a.d_.val_.val());
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.val_.val_.grad(p,g);
  stan::agrad::recover_memory();
  EXPECT_FLOAT_EQ((1.0 - tanh(1.5) * tanh(1.5)), g[0]);

  fvar<fvar<var> > y;
  y.val_.val_ = 1.5;
  y.d_.val_ = 2.0;

  fvar<fvar<var> > b = tanh(y);
  EXPECT_FLOAT_EQ(tanh(1.5), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0, a.val_.d_.val());
  EXPECT_FLOAT_EQ(2.0 * (1.0 - tanh(1.5) * tanh(1.5)), a.d_.val_.val());
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC q = createAVEC(y.val_.val_);
  VEC r;
  b.val_.val_.grad(q,r);
  EXPECT_FLOAT_EQ((1.0 - tanh(1.5) * tanh(1.5)), r[0]);
}
TEST_F(AgradFwdTanh, FvarFvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::tanh;
  using std::cosh;

  fvar<fvar<var> > x;
  x.val_.val_ = 1.5;
  x.val_.d_ = 2.0;

  fvar<fvar<var> > a = tanh(x);

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.val_.d_.grad(p,g);
  stan::agrad::recover_memory();
  EXPECT_FLOAT_EQ(2.0 * -2.0 * tanh(1.5) / (cosh(1.5) * cosh(1.5)), g[0]);

  fvar<fvar<var> > y;
  y.val_.val_ = 1.5;
  y.d_.val_ = 2.0;

  fvar<fvar<var> > b = tanh(y);

  AVEC q = createAVEC(y.val_.val_);
  VEC r;
  b.d_.val_.grad(q,r);
  EXPECT_FLOAT_EQ(2.0 * -2.0 * tanh(1.5) / (cosh(1.5) * cosh(1.5)), r[0]);
}
TEST_F(AgradFwdTanh, FvarFvarVar_3rdDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::tanh;
  using std::cosh;

  fvar<fvar<var> > x;
  x.val_.val_ = 1.5;
  x.val_.d_ = 1.0;
  x.d_.val_ = 1.0;

  fvar<fvar<var> > a = tanh(x);

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.d_.d_.grad(p,g);
  EXPECT_FLOAT_EQ(0.526897219588102805376158394192, g[0]);
}

struct tanh_fun {
  template <typename T0>
  inline T0
  operator()(const T0& arg1) const {
    return tanh(arg1);
  }
};

TEST_F(AgradFwdTanh,tanh_NaN) {
  tanh_fun tanh_;
  test_nan(tanh_,false);
}
