#ifndef TEST_UNIT_MATH_PRIM_MAT_VECTORIZE_EXPECT_INT_STD_VECTOR_ERROR_HPP
#define TEST_UNIT_MATH_PRIM_MAT_VECTORIZE_EXPECT_INT_STD_VECTOR_ERROR_HPP

#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

template <typename F>
void expect_int_std_vector_error() {
  using std::vector;
  vector<int> illegal_inputs = F::int_illegal_inputs();
  EXPECT_THROW(F::template apply<vector<double> >(illegal_inputs), 
               std::domain_error);

  vector<vector<int> > z;
  z.push_back(illegal_inputs);
  z.push_back(illegal_inputs);
  EXPECT_THROW(F::template apply<vector<vector<double> > >(z),
               std::domain_error);
}

#endif
