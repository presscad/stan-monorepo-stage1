#include <stan/math/prim/mat/err/check_pos_semidefinite.hpp>
#include <gtest/gtest.h>
#include <stan/math/rev/arr/meta/var.hpp>
#include <stan/math/rev/scal/fun/log.hpp>
#include <stan/math/rev/scal/fun/operator_greater_than.hpp>
#include <stan/math/rev/scal/fun/operator_greater_than_or_equal.hpp>
#include <stan/math/rev/scal/fun/value_of.hpp>
#include <stan/math/rev/scal/fun/value_of_rec.hpp>
#include <stan/math/rev/mat/fun/Eigen_NumTraits.hpp>

TEST(AgradRevErrorHandlingMatrix, checkPosDefiniteMatrix_nan) {
  using stan::agrad::var;
  using Eigen::Dynamic;
  using Eigen::Matrix;

  Matrix<var, Dynamic, Dynamic> y;
  double nan = std::numeric_limits<double>::quiet_NaN();
  using stan::math::check_pos_semidefinite;

  y.resize(1,1);
  y << nan;
  EXPECT_THROW(check_pos_semidefinite("checkPosDefiniteMatrix", "y", y), 
               std::domain_error);
  
  y.resize(3,3);
  y << 2, -1, 0,
    -1, 2, -1,
    0, -1, 2;
  EXPECT_TRUE(check_pos_semidefinite("checkPosDefiniteMatrix", "y", y));
                                 
  for (int i = 0; i < y.rows(); i++)
    for (int j = 0; j < y.cols(); j++) {
      y << 2, -1, 0, -1, 2, -1, 0, -1, 2;
      y(i,j) = nan;
      if (i >= j)
        EXPECT_THROW(check_pos_semidefinite("checkPosDefiniteMatrix", "y", y), 
                     std::domain_error);
    }

  y << 0, 0, 0, 0, 0, 0, 0, 0, 0;
  EXPECT_TRUE(check_pos_semidefinite("checkPosDefiniteMatrix", "y", y));
  stan::agrad::recover_memory();
}

TEST(AgradRevErrorHandlingMatrix, CheckPosDefiniteMatrixVarCheck) {
  using stan::agrad::var;
  using Eigen::Dynamic;
  using Eigen::Matrix;

  Matrix<var, Dynamic, Dynamic> y;
  double nan = std::numeric_limits<double>::quiet_NaN();
  using stan::math::check_pos_semidefinite;

  y.resize(1,1);
  y << nan;
  // EXPECT_THROW(check_pos_semidefinite("checkPosDefiniteMatrix", "y", y), 
  //              std::domain_error);
  
  y.resize(3,3);
  y << 2, -1, 0,
    -1, 2, -1,
    0, -1, 2;

  size_t stack_before_call = stan::agrad::ChainableStack::var_stack_.size();
  EXPECT_EQ(10U,stack_before_call);

  EXPECT_TRUE(check_pos_semidefinite("checkPosDefiniteMatrix", "y", y));
  size_t stack_after_call = stan::agrad::ChainableStack::var_stack_.size();

  EXPECT_EQ(10U,stack_after_call);
}

