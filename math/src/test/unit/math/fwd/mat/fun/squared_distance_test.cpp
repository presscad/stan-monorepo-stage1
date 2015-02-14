#include <stan/math/prim/mat/fun/squared_distance.hpp>
#include <stan/math/fwd/mat/fun/typedefs.hpp>
#include <gtest/gtest.h>
#include <boost/math/special_functions/fpclassify.hpp>
#include <stan/math/fwd/scal/fun/operator_addition.hpp>
#include <stan/math/fwd/scal/fun/operator_division.hpp>
#include <stan/math/fwd/scal/fun/operator_equal.hpp>
#include <stan/math/fwd/scal/fun/operator_greater_than.hpp>
#include <stan/math/fwd/scal/fun/operator_greater_than_or_equal.hpp>
#include <stan/math/fwd/scal/fun/operator_less_than.hpp>
#include <stan/math/fwd/scal/fun/operator_less_than_or_equal.hpp>
#include <stan/math/fwd/scal/fun/operator_multiplication.hpp>
#include <stan/math/fwd/scal/fun/operator_not_equal.hpp>
#include <stan/math/fwd/scal/fun/operator_subtraction.hpp>
#include <stan/math/fwd/scal/fun/operator_unary_minus.hpp>
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
using stan::agrad::fvar;

TEST(AgradFwdMatrixSquaredDistance, vector_fd_vector_fd) {
  stan::agrad::vector_fd v1, v2;
  
  v1.resize(3);
  v2.resize(3);
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  v1(0).d_ = 1.0;
  v1(1).d_ = 2.0;
  v1(2).d_ = 3.0;
  v2(0).d_ = 4.0;
  v2(1).d_ = 5.0;
  v2(2).d_ = 6.0;
  
  stan::agrad::fvar<double> a = stan::math::squared_distance(v1, v2);

  EXPECT_FLOAT_EQ(50, a.val_);
  EXPECT_FLOAT_EQ(12, a.d_);

  v1.resize(0);
  v2.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(v1, v2).val_);

  v1.resize(1);
  v2.resize(2);
  v1 << 1;
  v2 << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(v1, v2), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, rowvector_fd_vector_fd) {
  stan::agrad::row_vector_fd rv;
  stan::agrad::vector_fd v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<double> a = stan::math::squared_distance(rv, v);

  EXPECT_FLOAT_EQ(50, a.val_);
  EXPECT_FLOAT_EQ(12, a.d_);

  rv.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(rv, v).val_);

  rv.resize(1);
  v.resize(2);
  rv << 1;
  v << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(rv, v), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fd_rowvector_fd) {
  stan::agrad::row_vector_fd rv;
  stan::agrad::vector_fd v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<double> a = stan::math::squared_distance(v, rv);

  EXPECT_FLOAT_EQ(50, a.val_);
  EXPECT_FLOAT_EQ(12, a.d_);

  v.resize(0);
  rv.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(v, rv).val_);

  v.resize(1);
  rv.resize(2);
  v << 1;
  rv << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(v, rv), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, special_values_fd) {
  stan::agrad::vector_fd v1, v2;
  v1.resize(1);
  v2.resize(1);
  
  v1 << 0;
  v2 << std::numeric_limits<double>::quiet_NaN();
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v2, v1)));

  v1 << 0;
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v2, v1)));

  v1 << std::numeric_limits<double>::infinity();
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v2, v1)));

  v1 << -std::numeric_limits<double>::infinity();
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v2, v1)));
}

TEST(AgradFwdMatrixSquaredDistance, vector_ffd_vector_ffd) {
  stan::agrad::vector_ffd v1, v2;
  
  v1.resize(3);
  v2.resize(3);
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  v1(0).d_ = 1.0;
  v1(1).d_ = 2.0;
  v1(2).d_ = 3.0;
  v2(0).d_ = 4.0;
  v2(1).d_ = 5.0;
  v2(2).d_ = 6.0;
  
  stan::agrad::fvar<fvar<double> > a = stan::math::squared_distance(v1, v2);

  EXPECT_FLOAT_EQ(50, a.val_.val_);
  EXPECT_FLOAT_EQ(12, a.d_.val_);

  v1.resize(0);
  v2.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(v1, v2).val_.val_);

  v1.resize(1);
  v2.resize(2);
  v1 << 1;
  v2 << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(v1, v2), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, rowvector_ffd_vector_ffd) {
  stan::agrad::row_vector_ffd rv;
  stan::agrad::vector_ffd v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<fvar<double> > a = stan::math::squared_distance(rv, v);

  EXPECT_FLOAT_EQ(50, a.val_.val_);
  EXPECT_FLOAT_EQ(12, a.d_.val_);

  rv.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(rv, v).val_.val_);

  rv.resize(1);
  v.resize(2);
  rv << 1;
  v << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(rv, v), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, vector_ffd_rowvector_ffd) {
  stan::agrad::row_vector_ffd rv;
  stan::agrad::vector_ffd v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<fvar<double> > a = stan::math::squared_distance(v, rv);

  EXPECT_FLOAT_EQ(50, a.val_.val_);
  EXPECT_FLOAT_EQ(12, a.d_.val_);

  v.resize(0);
  rv.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(v, rv).val_.val_);

  v.resize(1);
  rv.resize(2);
  v << 1;
  rv << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(v, rv), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, special_values_ffd) {
  stan::agrad::vector_ffd v1, v2;
  v1.resize(1);
  v2.resize(1);
  
  v1 << 0;
  v2 << std::numeric_limits<double>::quiet_NaN();
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v2, v1)));

  v1 << 0;
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v2, v1)));

  v1 << std::numeric_limits<double>::infinity();
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v2, v1)));

  v1 << -std::numeric_limits<double>::infinity();
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v2, v1)));
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_vector_fv1) {
  stan::agrad::vector_fv v1, v2;
  
  v1.resize(3);
  v2.resize(3);
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  v1(0).d_ = 1.0;
  v1(1).d_ = 2.0;
  v1(2).d_ = 3.0;
  v2(0).d_ = 4.0;
  v2(1).d_ = 5.0;
  v2(2).d_ = 6.0;
  
  stan::agrad::fvar<var> a = stan::math::squared_distance(v1, v2);

  EXPECT_FLOAT_EQ(50, a.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(v1(0).val_);
  vars.push_back(v1(1).val_);
  vars.push_back(v1(2).val_);
  vars.push_back(v2(0).val_);
  vars.push_back(v2(1).val_);
  vars.push_back(v2(2).val_);

  a.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(10, grads[1]);
  EXPECT_FLOAT_EQ(-8, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(-10, grads[4]);
  EXPECT_FLOAT_EQ(8, grads[5]);

  v1.resize(0);
  v2.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(v1, v2).val_.val());

  v1.resize(1);
  v2.resize(2);
  v1 << 1;
  v2 << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(v1, v2), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_vector_fv2) {
  stan::agrad::vector_fv v1, v2;
  
  v1.resize(3);
  v2.resize(3);
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  v1(0).d_ = 1.0;
  v1(1).d_ = 2.0;
  v1(2).d_ = 3.0;
  v2(0).d_ = 4.0;
  v2(1).d_ = 5.0;
  v2(2).d_ = 6.0;
  
  stan::agrad::fvar<var> a = stan::math::squared_distance(v1, v2);

  EXPECT_FLOAT_EQ(50, a.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(v1(0).val_);
  vars.push_back(v1(1).val_);
  vars.push_back(v1(2).val_);
  vars.push_back(v2(0).val_);
  vars.push_back(v2(1).val_);
  vars.push_back(v2(2).val_);

  a.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}

TEST(AgradFwdMatrixSquaredDistance, rowvector_fv_vector_fv1) {
  stan::agrad::row_vector_fv rv;
  stan::agrad::vector_fv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<var> a = stan::math::squared_distance(rv, v);

  EXPECT_FLOAT_EQ(50, a.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_);
  vars.push_back(rv(1).val_);
  vars.push_back(rv(2).val_);
  vars.push_back(v(0).val_);
  vars.push_back(v(1).val_);
  vars.push_back(v(2).val_);

  a.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(10, grads[1]);
  EXPECT_FLOAT_EQ(-8, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(-10, grads[4]);
  EXPECT_FLOAT_EQ(8, grads[5]);

  rv.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(rv, v).val_.val());

  rv.resize(1);
  v.resize(2);
  rv << 1;
  v << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(rv, v), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, rowvector_fv_vector_fv2) {
  stan::agrad::row_vector_fv rv;
  stan::agrad::vector_fv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<var> a = stan::math::squared_distance(rv, v);

  EXPECT_FLOAT_EQ(50, a.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_);
  vars.push_back(rv(1).val_);
  vars.push_back(rv(2).val_);
  vars.push_back(v(0).val_);
  vars.push_back(v(1).val_);
  vars.push_back(v(2).val_);

  a.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_rowvector_fv1) {
  stan::agrad::row_vector_fv rv;
  stan::agrad::vector_fv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<var> a = stan::math::squared_distance(v, rv);

  EXPECT_FLOAT_EQ(50, a.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_);
  vars.push_back(rv(1).val_);
  vars.push_back(rv(2).val_);
  vars.push_back(v(0).val_);
  vars.push_back(v(1).val_);
  vars.push_back(v(2).val_);

  a.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(10, grads[1]);
  EXPECT_FLOAT_EQ(-8, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(-10, grads[4]);
  EXPECT_FLOAT_EQ(8, grads[5]);

  v.resize(0);
  rv.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(v, rv).val_.val());

  v.resize(1);
  rv.resize(2);
  v << 1;
  rv << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(v, rv), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_rowvector_fv2) {
  stan::agrad::row_vector_fv rv;
  stan::agrad::vector_fv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<var> a = stan::math::squared_distance(v, rv);

  EXPECT_FLOAT_EQ(50, a.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_);
  vars.push_back(rv(1).val_);
  vars.push_back(rv(2).val_);
  vars.push_back(v(0).val_);
  vars.push_back(v(1).val_);
  vars.push_back(v(2).val_);

  a.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}
TEST(AgradFwdMatrixSquaredDistance, special_values_fv) {
  stan::agrad::vector_fv v1, v2;
  v1.resize(1);
  v2.resize(1);
  
  v1 << 0;
  v2 << std::numeric_limits<double>::quiet_NaN();
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v2, v1)));

  v1 << 0;
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v2, v1)));

  v1 << std::numeric_limits<double>::infinity();
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v2, v1)));

  v1 << -std::numeric_limits<double>::infinity();
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v2, v1)));
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_vector_ffv1) {
  stan::agrad::vector_ffv v1, v2;
  
  v1.resize(3);
  v2.resize(3);
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  v1(0).d_ = 1.0;
  v1(1).d_ = 2.0;
  v1(2).d_ = 3.0;
  v2(0).d_ = 4.0;
  v2(1).d_ = 5.0;
  v2(2).d_ = 6.0;
  
  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(v1, v2);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(v1(0).val_.val_);
  vars.push_back(v1(1).val_.val_);
  vars.push_back(v1(2).val_.val_);
  vars.push_back(v2(0).val_.val_);
  vars.push_back(v2(1).val_.val_);
  vars.push_back(v2(2).val_.val_);

  a.val_.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(10, grads[1]);
  EXPECT_FLOAT_EQ(-8, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(-10, grads[4]);
  EXPECT_FLOAT_EQ(8, grads[5]);

  v1.resize(0);
  v2.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(v1, v2).val_.val_.val());

  v1.resize(1);
  v2.resize(2);
  v1 << 1;
  v2 << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(v1, v2), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_vector_ffv2) {
  stan::agrad::vector_ffv v1, v2;
  
  v1.resize(3);
  v2.resize(3);
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  v1(0).d_ = 1.0;
  v1(1).d_ = 2.0;
  v1(2).d_ = 3.0;
  v2(0).d_ = 4.0;
  v2(1).d_ = 5.0;
  v2(2).d_ = 6.0;
  v1(0).val_.d_ = 1.0;
  v1(1).val_.d_ = 2.0;
  v1(2).val_.d_ = 3.0;
  v2(0).val_.d_ = 4.0;
  v2(1).val_.d_ = 5.0;
  v2(2).val_.d_ = 6.0;
  
  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(v1, v2);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(v1(0).val_.val_);
  vars.push_back(v1(1).val_.val_);
  vars.push_back(v1(2).val_.val_);
  vars.push_back(v2(0).val_.val_);
  vars.push_back(v2(1).val_.val_);
  vars.push_back(v2(2).val_.val_);

  a.val_.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_vector_ffv3) {
  stan::agrad::vector_ffv v1, v2;
  
  v1.resize(3);
  v2.resize(3);
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  v1(0).d_ = 1.0;
  v1(1).d_ = 2.0;
  v1(2).d_ = 3.0;
  v2(0).d_ = 4.0;
  v2(1).d_ = 5.0;
  v2(2).d_ = 6.0;
  v1(0).val_.d_ = 1.0;
  v1(1).val_.d_ = 2.0;
  v1(2).val_.d_ = 3.0;
  v2(0).val_.d_ = 4.0;
  v2(1).val_.d_ = 5.0;
  v2(2).val_.d_ = 6.0;
  
  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(v1, v2);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(v1(0).val_.val_);
  vars.push_back(v1(1).val_.val_);
  vars.push_back(v1(2).val_.val_);
  vars.push_back(v2(0).val_.val_);
  vars.push_back(v2(1).val_.val_);
  vars.push_back(v2(2).val_.val_);

  a.d_.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_vector_ffv4) {
  stan::agrad::vector_ffv v1, v2;
  
  v1.resize(3);
  v2.resize(3);
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  v1(0).d_ = 1.0;
  v1(1).d_ = 2.0;
  v1(2).d_ = 3.0;
  v2(0).d_ = 4.0;
  v2(1).d_ = 5.0;
  v2(2).d_ = 6.0;
  v1(0).val_.d_ = 1.0;
  v1(1).val_.d_ = 2.0;
  v1(2).val_.d_ = 3.0;
  v2(0).val_.d_ = 4.0;
  v2(1).val_.d_ = 5.0;
  v2(2).val_.d_ = 6.0;
  
  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(v1, v2);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(v1(0).val_.val_);
  vars.push_back(v1(1).val_.val_);
  vars.push_back(v1(2).val_.val_);
  vars.push_back(v2(0).val_.val_);
  vars.push_back(v2(1).val_.val_);
  vars.push_back(v2(2).val_.val_);

  a.d_.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(0, grads[0]);
  EXPECT_FLOAT_EQ(-0, grads[1]);
  EXPECT_FLOAT_EQ(0, grads[2]);
  EXPECT_FLOAT_EQ(-0, grads[3]);
  EXPECT_FLOAT_EQ(0, grads[4]);
  EXPECT_FLOAT_EQ(-0, grads[5]);
}

TEST(AgradFwdMatrixSquaredDistance, rowvector_fv_vector_ffv1) {
  stan::agrad::row_vector_ffv rv;
  stan::agrad::vector_ffv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(rv, v);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_.val_);
  vars.push_back(rv(1).val_.val_);
  vars.push_back(rv(2).val_.val_);
  vars.push_back(v(0).val_.val_);
  vars.push_back(v(1).val_.val_);
  vars.push_back(v(2).val_.val_);

  a.val_.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(10, grads[1]);
  EXPECT_FLOAT_EQ(-8, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(-10, grads[4]);
  EXPECT_FLOAT_EQ(8, grads[5]);

  rv.resize(0);
  v.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(rv, v).val_.val_.val());

  rv.resize(1);
  v.resize(2);
  rv << 1;
  v << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(rv, v), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, rowvector_fv_vector_ffv2) {
  stan::agrad::row_vector_ffv rv;
  stan::agrad::vector_ffv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;
  rv(0).val_.d_ = 1.0;
  rv(1).val_.d_ = 2.0;
  rv(2).val_.d_ = 3.0;
  v(0).val_.d_ = 4.0;
  v(1).val_.d_ = 5.0;
  v(2).val_.d_ = 6.0;

  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(rv, v);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_.val_);
  vars.push_back(rv(1).val_.val_);
  vars.push_back(rv(2).val_.val_);
  vars.push_back(v(0).val_.val_);
  vars.push_back(v(1).val_.val_);
  vars.push_back(v(2).val_.val_);

  a.val_.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}
TEST(AgradFwdMatrixSquaredDistance, rowvector_fv_vector_ffv3) {
  stan::agrad::row_vector_ffv rv;
  stan::agrad::vector_ffv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;
  rv(0).val_.d_ = 1.0;
  rv(1).val_.d_ = 2.0;
  rv(2).val_.d_ = 3.0;
  v(0).val_.d_ = 4.0;
  v(1).val_.d_ = 5.0;
  v(2).val_.d_ = 6.0;

  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(rv, v);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_.val_);
  vars.push_back(rv(1).val_.val_);
  vars.push_back(rv(2).val_.val_);
  vars.push_back(v(0).val_.val_);
  vars.push_back(v(1).val_.val_);
  vars.push_back(v(2).val_.val_);

  a.d_.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}
TEST(AgradFwdMatrixSquaredDistance, rowvector_fv_vector_ffv4) {
  stan::agrad::row_vector_ffv rv;
  stan::agrad::vector_ffv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;
  rv(0).val_.d_ = 1.0;
  rv(1).val_.d_ = 2.0;
  rv(2).val_.d_ = 3.0;
  v(0).val_.d_ = 4.0;
  v(1).val_.d_ = 5.0;
  v(2).val_.d_ = 6.0;

  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(rv, v);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_.val_);
  vars.push_back(rv(1).val_.val_);
  vars.push_back(rv(2).val_.val_);
  vars.push_back(v(0).val_.val_);
  vars.push_back(v(1).val_.val_);
  vars.push_back(v(2).val_.val_);

  a.d_.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(0, grads[0]);
  EXPECT_FLOAT_EQ(-0, grads[1]);
  EXPECT_FLOAT_EQ(0, grads[2]);
  EXPECT_FLOAT_EQ(-0, grads[3]);
  EXPECT_FLOAT_EQ(0, grads[4]);
  EXPECT_FLOAT_EQ(-0, grads[5]);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_rowvector_ffv1) {
  stan::agrad::row_vector_ffv rv;
  stan::agrad::vector_ffv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;

  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(v, rv);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_.val_);
  vars.push_back(rv(1).val_.val_);
  vars.push_back(rv(2).val_.val_);
  vars.push_back(v(0).val_.val_);
  vars.push_back(v(1).val_.val_);
  vars.push_back(v(2).val_.val_);

  a.val_.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(10, grads[1]);
  EXPECT_FLOAT_EQ(-8, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(-10, grads[4]);
  EXPECT_FLOAT_EQ(8, grads[5]);

  v.resize(0);
  rv.resize(0);
  EXPECT_FLOAT_EQ(0, stan::math::squared_distance(v, rv).val_.val_.val());

  v.resize(1);
  rv.resize(2);
  v << 1;
  rv << 2, 3;
  EXPECT_THROW(stan::math::squared_distance(v, rv), std::invalid_argument);
}

TEST(AgradFwdMatrixSquaredDistance, vector_fv_rowvector_ffv2) {
  stan::agrad::row_vector_ffv rv;
  stan::agrad::vector_ffv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;
  rv(0).val_.d_ = 1.0;
  rv(1).val_.d_ = 2.0;
  rv(2).val_.d_ = 3.0;
  v(0).val_.d_ = 4.0;
  v(1).val_.d_ = 5.0;
  v(2).val_.d_ = 6.0;


  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(v, rv);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_.val_);
  vars.push_back(rv(1).val_.val_);
  vars.push_back(rv(2).val_.val_);
  vars.push_back(v(0).val_.val_);
  vars.push_back(v(1).val_.val_);
  vars.push_back(v(2).val_.val_);

  a.d_.val_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}
TEST(AgradFwdMatrixSquaredDistance, vector_fv_rowvector_ffv3) {
  stan::agrad::row_vector_ffv rv;
  stan::agrad::vector_ffv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;
  rv(0).val_.d_ = 1.0;
  rv(1).val_.d_ = 2.0;
  rv(2).val_.d_ = 3.0;
  v(0).val_.d_ = 4.0;
  v(1).val_.d_ = 5.0;
  v(2).val_.d_ = 6.0;


  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(v, rv);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_.val_);
  vars.push_back(rv(1).val_.val_);
  vars.push_back(rv(2).val_.val_);
  vars.push_back(v(0).val_.val_);
  vars.push_back(v(1).val_.val_);
  vars.push_back(v(2).val_.val_);

  a.val_.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(-6, grads[0]);
  EXPECT_FLOAT_EQ(-6, grads[1]);
  EXPECT_FLOAT_EQ(-6, grads[2]);
  EXPECT_FLOAT_EQ(6, grads[3]);
  EXPECT_FLOAT_EQ(6, grads[4]);
  EXPECT_FLOAT_EQ(6, grads[5]);
}
TEST(AgradFwdMatrixSquaredDistance, vector_fv_rowvector_ffv4) {
  stan::agrad::row_vector_ffv rv;
  stan::agrad::vector_ffv v;
  
  rv.resize(3);
  v.resize(3);
  rv << 1, 3, -5;
  v << 4, -2, -1;
  rv(0).d_ = 1.0;
  rv(1).d_ = 2.0;
  rv(2).d_ = 3.0;
  v(0).d_ = 4.0;
  v(1).d_ = 5.0;
  v(2).d_ = 6.0;
  rv(0).val_.d_ = 1.0;
  rv(1).val_.d_ = 2.0;
  rv(2).val_.d_ = 3.0;
  v(0).val_.d_ = 4.0;
  v(1).val_.d_ = 5.0;
  v(2).val_.d_ = 6.0;


  stan::agrad::fvar<fvar<var> > a = stan::math::squared_distance(v, rv);

  EXPECT_FLOAT_EQ(50, a.val_.val_.val());
  EXPECT_FLOAT_EQ(12, a.d_.val_.val());

  std::vector<double> grads;
  std::vector<var> vars;
  vars.push_back(rv(0).val_.val_);
  vars.push_back(rv(1).val_.val_);
  vars.push_back(rv(2).val_.val_);
  vars.push_back(v(0).val_.val_);
  vars.push_back(v(1).val_.val_);
  vars.push_back(v(2).val_.val_);

  a.d_.d_.grad(vars, grads);
  EXPECT_FLOAT_EQ(0, grads[0]);
  EXPECT_FLOAT_EQ(-0, grads[1]);
  EXPECT_FLOAT_EQ(0, grads[2]);
  EXPECT_FLOAT_EQ(-0, grads[3]);
  EXPECT_FLOAT_EQ(0, grads[4]);
  EXPECT_FLOAT_EQ(-0, grads[5]);
}
TEST(AgradFwdMatrixSquaredDistance, special_values_ffv) {
  stan::agrad::vector_ffv v1, v2;
  v1.resize(1);
  v2.resize(1);
  
  v1 << 0;
  v2 << std::numeric_limits<double>::quiet_NaN();
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v2, v1)));

  v1 << 0;
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v2, v1)));

  v1 << std::numeric_limits<double>::infinity();
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isnan(stan::math::squared_distance(v2, v1)));

  v1 << -std::numeric_limits<double>::infinity();
  v2 << std::numeric_limits<double>::infinity();
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v1, v2)));
  EXPECT_TRUE(boost::math::isinf(stan::math::squared_distance(v2, v1)));
}
