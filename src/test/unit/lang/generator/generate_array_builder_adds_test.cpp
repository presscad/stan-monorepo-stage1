#include <gtest/gtest.h>
#include <test/unit/lang/utility.hpp>

TEST(genArrayBuilderAdds, addScalars) {
  stan::lang::expression e_d3(stan::lang::double_literal(3));
  std::vector<stan::lang::expression> elts;
  elts.push_back(e_d3);
  elts.push_back(e_d3);
  elts.push_back(e_d3);
  std::stringstream o2;
  stan::lang::generate_array_builder_adds(elts, true, false, o2);
  EXPECT_EQ(3, count_matches(".add(", o2.str()));
}
