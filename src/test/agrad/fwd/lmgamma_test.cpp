#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <boost/math/special_functions/digamma.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFvar, lmgamma) {
  using stan::agrad::fvar;
  using stan::math::lmgamma;

  int x = 3;
  fvar<double> y(3.2,2.1);

  fvar<double> a = lmgamma(x, y);
  EXPECT_FLOAT_EQ(lmgamma(3, 3.2), a.val_);
}
