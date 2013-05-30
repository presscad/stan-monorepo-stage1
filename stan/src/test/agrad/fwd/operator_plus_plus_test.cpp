#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, operatorPlusPlus) {
  using stan::agrad::fvar;

  fvar<double> x(0.5,1.0);
  x++;

  EXPECT_FLOAT_EQ(0.5 + 1.0, x.val_);
  EXPECT_FLOAT_EQ(1.0, x.d_);

  fvar<double> y(-0.5,1.0);
  y++;

  EXPECT_FLOAT_EQ(-0.5 + 1.0, y.val_);
  EXPECT_FLOAT_EQ(1.0, y.d_);
}

TEST(AgradFvarVar, operatorPlusPlus) {
  using stan::agrad::fvar;
  using stan::agrad::var;

  fvar<var> x(0.5,1.3);
  x++;
  EXPECT_FLOAT_EQ(0.5 + 1.0, x.val_.val());
  EXPECT_FLOAT_EQ(1.3, x.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  x.val_.grad(y,g);
  EXPECT_FLOAT_EQ(1.0, g[0]);

  y = createAVEC(x.d_);
  x.d_.grad(y,g);
  EXPECT_FLOAT_EQ(1, g[0]);
}

TEST(AgradFvarFvar, operatorPlusPlus) {
  using stan::agrad::fvar;

  fvar<fvar<double> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  x++;
  EXPECT_FLOAT_EQ(0.5 + 1.0, x.val_.val_);
  EXPECT_FLOAT_EQ(1, x.val_.d_);
  EXPECT_FLOAT_EQ(0, x.d_.val_);
  EXPECT_FLOAT_EQ(0, x.d_.d_);
}
