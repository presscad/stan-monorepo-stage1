#include <stan/math/error_handling/check_equal.hpp>
#include <gtest/gtest.h>

using stan::math::check_equal;

TEST(MathErrorHandling,CheckEqual) {
  const char* function = "check_equal(%1%)";
  double x = 0.0;
  double eq = 0.0;
  double result;
 
  EXPECT_TRUE(check_equal(function, x, eq, "x", &result)) 
    << "check_equal should be true with x = eq";
  
  x = -1.0;
  EXPECT_THROW(check_equal(function, x, eq, "x", &result),
               std::domain_error)
    << "check_equal should throw an exception with x < eq";

  x = eq;
  EXPECT_NO_THROW(check_equal(function, x, eq, "x", &result))
    << "check_equal should not throw an exception with x == eq";

  x = std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_equal(function, x, eq, "x", &result), 
               std::domain_error)
    << "check_equal should be false with x == Inf and eq = 0.0";

  x = 10.0;
  eq = std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_equal(function, x, eq, "x", &result),
               std::domain_error)
    << "check_equal should throw an exception with x == 10.0 and eq == Inf";

  x = std::numeric_limits<double>::infinity();
  eq = std::numeric_limits<double>::infinity();
  EXPECT_NO_THROW(check_equal(function, x, eq, "x", &result))
    << "check_equal should not throw an exception with x == Inf and eq == Inf";
}

TEST(MathErrorHandling,CheckEqualMatrix) {
  const char* function = "check_equal(%1%)";
  double result;
  Eigen::Matrix<double,Eigen::Dynamic,1> x_vec;
  Eigen::Matrix<double,Eigen::Dynamic,1> eq_vec;
  x_vec.resize(3);
  eq_vec.resize(3);

  // x_vec, low_vec
  result = 0;
  x_vec   << -1, 0, 1;
  eq_vec << -1, 0, 1;
  EXPECT_TRUE(check_equal(function, x_vec, eq_vec, "x", &result)) 
    << "check_equal: matrix<3,1>, matrix<3,1>";

  x_vec   <<   -1,    0,   1;
  eq_vec << -1.1, -0.1, 0.9;
  EXPECT_THROW(check_equal(function, x_vec, eq_vec, "x", &result),
               std::domain_error) 
    << "check_equal: matrix<3,1>, matrix<3,1>";
  
  x_vec   << -1, 0,  1;
  eq_vec << -2, -1, std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_equal(function, x_vec, eq_vec, "x", &result), 
               std::domain_error) 
    << "check_equal: matrix<3,1>, matrix<3,1>, should fail with infinity";
}
