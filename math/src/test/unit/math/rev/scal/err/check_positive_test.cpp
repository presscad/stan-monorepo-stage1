#include <stan/math/prim/scal/err/check_positive.hpp>
#include <gtest/gtest.h>
#include <stan/math/rev/scal/fun/value_of_rec.hpp>
#include <stan/math/rev/scal/fun/operator_addition.hpp>
#include <stan/math/rev/scal/fun/operator_divide_equal.hpp>
#include <stan/math/rev/scal/fun/operator_division.hpp>
#include <stan/math/rev/scal/fun/operator_equal.hpp>
#include <stan/math/rev/scal/fun/operator_greater_than.hpp>
#include <stan/math/rev/scal/fun/operator_greater_than_or_equal.hpp>
#include <stan/math/rev/scal/fun/operator_less_than.hpp>
#include <stan/math/rev/scal/fun/operator_less_than_or_equal.hpp>
#include <stan/math/rev/scal/fun/operator_minus_equal.hpp>
#include <stan/math/rev/scal/fun/operator_multiplication.hpp>
#include <stan/math/rev/scal/fun/operator_multiply_equal.hpp>
#include <stan/math/rev/scal/fun/operator_not_equal.hpp>
#include <stan/math/rev/scal/fun/operator_plus_equal.hpp>
#include <stan/math/rev/scal/fun/operator_subtraction.hpp>
#include <stan/math/rev/scal/fun/operator_unary_decrement.hpp>
#include <stan/math/rev/scal/fun/operator_unary_increment.hpp>
#include <stan/math/rev/scal/fun/operator_unary_negative.hpp>
#include <stan/math/rev/scal/fun/operator_unary_not.hpp>
#include <stan/math/rev/scal/fun/operator_unary_plus.hpp>

using stan::agrad::var;

TEST(AgradRevErrorHandlingScalar,CheckPositive) {
  using stan::math::check_positive;
  const char* function = "check_positive";

  EXPECT_TRUE(check_positive(function, "x", nan));

  std::vector<var> x;
  x.push_back(var(1.0));
  x.push_back(var(2.0));
  x.push_back(var(3.0));

  for (size_t i = 0; i < x.size(); i++) {
    EXPECT_TRUE(check_positive(function, "x", x));
  }

  Eigen::Matrix<var,Eigen::Dynamic,1> x_mat(3);
  x_mat   << 1, 2, 3;
  for (int i = 0; i < x_mat.size(); i++) {
    EXPECT_TRUE(check_positive(function, "x", x_mat));
  }

  x_mat(0) = 0;

  EXPECT_THROW(check_positive(function, "x", x_mat),
               std::domain_error);
  stan::agrad::recover_memory();
}

TEST(AgradRevErrorHandlingScalar, CheckPositiveVarCheckUnivariate) {
  using stan::agrad::var;
  using stan::math::check_positive;

  const char* function = "check_positive";
  var a(5.0);

  size_t stack_size = stan::agrad::ChainableStack::var_stack_.size();

  EXPECT_EQ(1U,stack_size);
  EXPECT_TRUE(check_positive(function,"a",a));

  size_t stack_size_after_call = stan::agrad::ChainableStack::var_stack_.size();
  EXPECT_EQ(1U,stack_size_after_call);

  stan::agrad::recover_memory();
}

TEST(AgradRevErrorHandlingScalar, CheckPositiveVarCheckVectorized) {
  using stan::agrad::var;
  using std::vector;
  using stan::math::check_positive;

  int N = 5;
  const char* function = "check_positive";
  vector<var> a;

  for (int i = 0; i < N; ++i)
   a.push_back(var(i));

  size_t stack_size = stan::agrad::ChainableStack::var_stack_.size();

  EXPECT_EQ(5U,stack_size);
  EXPECT_THROW(check_positive(function,"a",a),std::domain_error);
  EXPECT_TRUE(check_positive(function,"a",a[2]));

  size_t stack_size_after_call = stan::agrad::ChainableStack::var_stack_.size();
  EXPECT_EQ(5U,stack_size_after_call);
  stan::agrad::recover_memory();
}
