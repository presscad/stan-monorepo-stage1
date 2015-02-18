#include <gtest/gtest.h>
#include <test/unit/math/prim/mat/prob/expect_eq_diffs.hpp>
#include <stan/math/prim/scal/meta/traits.hpp>
#include <stan/math/prim/mat/prob/multinomial_log.hpp>
#include <stan/math/rev/mat/fun/to_var.hpp>
#include <stan/math/rev/core/operator_addition.hpp>
#include <stan/math/rev/core/operator_division.hpp>
#include <stan/math/rev/core/operator_divide_equal.hpp>
#include <stan/math/rev/core/operator_greater_than.hpp>
#include <stan/math/rev/core/operator_greater_than_or_equal.hpp>
#include <stan/math/rev/core/operator_less_than.hpp>
#include <stan/math/rev/core/operator_less_than_or_equal.hpp>
#include <stan/math/rev/core/operator_multiplication.hpp>
#include <stan/math/rev/core/operator_multiply_equal.hpp>
#include <stan/math/rev/core/operator_plus_equal.hpp>
#include <stan/math/rev/core/operator_minus_equal.hpp>
#include <stan/math/rev/core/operator_equal.hpp>
#include <stan/math/rev/core/operator_not_equal.hpp>
#include <stan/math/rev/core/operator_subtraction.hpp>
#include <stan/math/rev/core/operator_unary_negative.hpp>

template <typename T_prob>
void expect_propto(std::vector<int>& ns1, T_prob theta1, 
                   std::vector<int>& ns2, T_prob theta2, 
                   std::string message) {
  expect_eq_diffs(stan::prob::multinomial_log<false>(ns1, theta1),
                  stan::prob::multinomial_log<false>(ns2, theta2),
                  stan::prob::multinomial_log<true>(ns1, theta1),
                  stan::prob::multinomial_log<true>(ns2, theta2),
                  message);
}

using stan::agrad::var;
using Eigen::Dynamic;
using Eigen::Matrix;


TEST(AgradDistributionsMultinomial,Propto) {
  std::vector<int> ns;
  ns.push_back(1);
  ns.push_back(2);
  ns.push_back(3);
  Matrix<var,Dynamic,1> theta1(3,1);
  theta1 << 0.3, 0.5, 0.2;
  Matrix<var,Dynamic,1> theta2(3,1);
  theta2 << 0.1, 0.2, 0.7;
  
  expect_propto(ns, theta1,
                ns, theta2,
                "var: theta");
}
