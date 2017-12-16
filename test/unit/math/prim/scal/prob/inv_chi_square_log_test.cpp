#include <stan/math/prim/scal.hpp>
#include <gtest/gtest.h>

TEST(ProbInvChiSquare, log_matches_lpdf) {
  double y = 0.8;
  double nu = 2.3;

  EXPECT_FLOAT_EQ((stan::math::inv_chi_square_lpdf(y, nu)),
                  (stan::math::inv_chi_square_log(y, nu)));
  EXPECT_FLOAT_EQ((stan::math::inv_chi_square_lpdf<true>(y, nu)),
                  (stan::math::inv_chi_square_log<true>(y, nu)));
  EXPECT_FLOAT_EQ((stan::math::inv_chi_square_lpdf<false>(y, nu)),
                  (stan::math::inv_chi_square_log<false>(y, nu)));
  EXPECT_FLOAT_EQ(
      (stan::math::inv_chi_square_lpdf<true, double, double>(y, nu)),
      (stan::math::inv_chi_square_log<true, double, double>(y, nu)));
  EXPECT_FLOAT_EQ(
      (stan::math::inv_chi_square_lpdf<false, double, double>(y, nu)),
      (stan::math::inv_chi_square_log<false, double, double>(y, nu)));
  EXPECT_FLOAT_EQ((stan::math::inv_chi_square_lpdf<double, double>(y, nu)),
                  (stan::math::inv_chi_square_log<double, double>(y, nu)));
}
