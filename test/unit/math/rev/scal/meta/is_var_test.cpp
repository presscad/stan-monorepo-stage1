#include <stan/math/rev/scal.hpp>
#include <gtest/gtest.h>

TEST(MetaTraits, is_var) {
  using stan::is_var;
  EXPECT_FALSE(is_var<stan::math::var>::value);
}
