#include <stan/math/prim/mat/fun/cumulative_sum.hpp>
#include <gtest/gtest.h>
#include <test/unit/math/rev/mat/fun/util.hpp>
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

template <typename T>
void test_cumulative_sum() {
  using stan::math::cumulative_sum;

  T c(1);
  c[0] = 1.7;
  T d = cumulative_sum(c);
  EXPECT_EQ(c.size(), d.size());
  EXPECT_FLOAT_EQ(c[0].val(),d[0].val());
  VEC grad = cgrad(d[0], c[0]);
  EXPECT_EQ(1U,grad.size());
  EXPECT_FLOAT_EQ(1.0,grad[0]);

  T e(2);
  e[0] = 5.9;  e[1] = -1.2;
  T f = cumulative_sum(e);
  EXPECT_EQ(e.size(), f.size());
  EXPECT_FLOAT_EQ(e[0].val(),f[0].val());
  EXPECT_FLOAT_EQ((e[0] + e[1]).val(), f[1].val());
  grad = cgrad(f[0],e[0],e[1]);
  EXPECT_EQ(2U,grad.size());
  EXPECT_FLOAT_EQ(1.0,grad[0]);
  EXPECT_FLOAT_EQ(0.0,grad[1]);

  T g(3);
  g[0] = 5.9;  g[1] = -1.2;   g[2] = 192.13456;
  T h = cumulative_sum(g);
  EXPECT_EQ(g.size(), h.size());
  EXPECT_FLOAT_EQ(g[0].val(),h[0].val());
  EXPECT_FLOAT_EQ((g[0] + g[1]).val(), h[1].val());
  EXPECT_FLOAT_EQ((g[0] + g[1] + g[2]).val(), h[2].val());

  grad = cgrad(h[2],g[0],g[1],g[2]);
  EXPECT_EQ(3U,grad.size());
  EXPECT_FLOAT_EQ(1.0,grad[0]);
  EXPECT_FLOAT_EQ(1.0,grad[1]);
  EXPECT_FLOAT_EQ(1.0,grad[2]);
}
TEST(AgradRevMatrix, cumulative_sum) {
  using stan::agrad::var;
  using stan::math::cumulative_sum;

  EXPECT_FLOAT_EQ(0, cumulative_sum(std::vector<var>(0)).size());

  Eigen::Matrix<var,Eigen::Dynamic,1> a;
  EXPECT_FLOAT_EQ(0,cumulative_sum(a).size());

  Eigen::Matrix<var,1,Eigen::Dynamic> b;
  EXPECT_FLOAT_EQ(0,cumulative_sum(b).size());

  test_cumulative_sum<std::vector<var> >();
  test_cumulative_sum<Eigen::Matrix<var,Eigen::Dynamic,1> >();
  test_cumulative_sum<Eigen::Matrix<var,1,Eigen::Dynamic> >();
}

