#include <stan/math/prim/scal.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <gtest/gtest.h>

TEST(MathFunctions, lgamma) {
  EXPECT_TRUE(boost::math::isinf(lgamma(0.0)));
}  

TEST(MathFunctions, lgammaStanMathUsing) {
  using stan::math::lgamma;
  EXPECT_THROW(lgamma(0.0), std::domain_error);
}  

TEST(MathFunctions, lgamma_nan) {
  double nan = std::numeric_limits<double>::quiet_NaN();
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::math::lgamma(nan));
}
