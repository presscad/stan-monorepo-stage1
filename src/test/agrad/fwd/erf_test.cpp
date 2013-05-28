#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, erf) {
  using stan::agrad::fvar;
  using std::exp;
  using std::sqrt;
  using boost::math::erf;

  fvar<double> x(0.5);
  x.d_ = 1.0;

  fvar<double> a = erf(x);
  EXPECT_FLOAT_EQ(erf(0.5), a.val_);
  EXPECT_FLOAT_EQ(2 * exp(-0.5 * 0.5) / 
                  sqrt(boost::math::constants::pi<double>()), a.d_);

 fvar<double> b = erf(-x);
  EXPECT_FLOAT_EQ(erf(-0.5), b.val_);
  EXPECT_FLOAT_EQ(-2 * exp(-0.5 * 0.5) 
                  / sqrt(boost::math::constants::pi<double>()), b.d_);
}

TEST(AgradFvarVar, erf) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::exp;
  using std::sqrt;
  using boost::math::erf;

  fvar<var> x;
  x.val_ = 0.5;
  x.d_ = 1.3;
  fvar<var> a = erf(x);

  EXPECT_FLOAT_EQ(erf(0.5), a.val_.val());
  EXPECT_FLOAT_EQ(1.3 * 2 * exp(-0.5 * 0.5) / 
                  sqrt(boost::math::constants::pi<double>()), a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(2 * exp(-0.5 * 0.5) / 
                  sqrt(boost::math::constants::pi<double>()), g[0]);

  y = createAVEC(x.d_);
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(0, g[0]);
}

TEST(AgradFvarFvar, erf) {
  using stan::agrad::fvar;
  using std::exp;
  using std::sqrt;
  using boost::math::erf;

  fvar<fvar<double> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;
  x.d_.val_ = 0.0;
  x.d_.d_ = 0.0;

  fvar<fvar<double> > a = erf(x);

  EXPECT_FLOAT_EQ(erf(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(2 * exp(-0.5 * 0.5) / 
                  sqrt(boost::math::constants::pi<double>()), a.val_.d_);
  EXPECT_FLOAT_EQ(0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > y;
  y.val_.val_ = 0.5;
  y.val_.d_ = 0.0;
  y.d_.val_ = 1.0;
  y.d_.d_ = 0.0;

  a = erf(y);
  EXPECT_FLOAT_EQ(erf(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(2 * exp(-0.5 * 0.5) / 
                  sqrt(boost::math::constants::pi<double>()), a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);
}
