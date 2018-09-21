#include <boost/type_traits.hpp>
#include <gtest/gtest.h>
#include <stan/math/prim/scal.hpp>

TEST(MetaTraits, containsNonconstantStruct) {
  using stan::contains_nonconstant_struct;
  EXPECT_FALSE(contains_nonconstant_struct<int>::value);
  EXPECT_FALSE(contains_nonconstant_struct<double>::value);
  EXPECT_FALSE(contains_nonconstant_struct<float>::value);
  EXPECT_FALSE(contains_nonconstant_struct<int32_t>::value);
}
