#include <stan/math/prim/scal/prob/normal.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <test/unit/math/rev/mat/fun/util.hpp>
#include <stan/math/fwd/scal/fun/value_of.hpp>
#include <stan/math/rev/scal/fun/value_of.hpp>
#include <stan/math/fwd/scal/fun/value_of_rec.hpp>
#include <stan/math/rev/scal/fun/value_of_rec.hpp>
#include <stan/math/rev/core/operator_addition.hpp>
#include <stan/math/rev/core/operator_divide_equal.hpp>
#include <stan/math/rev/core/operator_division.hpp>
#include <stan/math/rev/core/operator_equal.hpp>
#include <stan/math/rev/core/operator_greater_than.hpp>
#include <stan/math/rev/core/operator_greater_than_or_equal.hpp>
#include <stan/math/rev/core/operator_less_than.hpp>
#include <stan/math/rev/core/operator_less_than_or_equal.hpp>
#include <stan/math/rev/core/operator_minus_equal.hpp>
#include <stan/math/rev/core/operator_multiplication.hpp>
#include <stan/math/rev/core/operator_multiply_equal.hpp>
#include <stan/math/rev/core/operator_not_equal.hpp>
#include <stan/math/rev/core/operator_plus_equal.hpp>
#include <stan/math/rev/core/operator_subtraction.hpp>
#include <stan/math/rev/core/operator_unary_decrement.hpp>
#include <stan/math/rev/core/operator_unary_increment.hpp>
#include <stan/math/rev/core/operator_unary_negative.hpp>
#include <stan/math/rev/core/operator_unary_not.hpp>
#include <stan/math/rev/core/operator_unary_plus.hpp>
#include <stan/math/fwd/core/operator_addition.hpp>
#include <stan/math/fwd/core/operator_division.hpp>
#include <stan/math/fwd/core/operator_equal.hpp>
#include <stan/math/fwd/core/operator_greater_than.hpp>
#include <stan/math/fwd/core/operator_greater_than_or_equal.hpp>
#include <stan/math/fwd/core/operator_less_than.hpp>
#include <stan/math/fwd/core/operator_less_than_or_equal.hpp>
#include <stan/math/fwd/core/operator_multiplication.hpp>
#include <stan/math/fwd/core/operator_not_equal.hpp>
#include <stan/math/fwd/core/operator_subtraction.hpp>
#include <stan/math/fwd/core/operator_unary_minus.hpp>
#include <stan/math/fwd/scal/fun/log.hpp>
#include <stan/math/rev/scal/fun/log.hpp>

std::vector<double> test_fun(double y, double mu, double sigma) {
  using stan::agrad::var;
  using stan::prob::normal_log;
  var y_var = y;
  var mu_var = mu;
  var sigma_var = sigma;
  
  std::vector<var> x;
  x.push_back(y_var);
  x.push_back(mu_var);
  x.push_back(sigma_var);

  var logp = normal_log<false>(y_var,mu_var,sigma_var);
  std::vector<double> grad;
  logp.grad(x,grad);
  return grad;
}

TEST(ProbAgradDistributionsNormal, fwd) {
  using stan::agrad::fvar;
  using stan::prob::normal_log;

  EXPECT_FLOAT_EQ(-0.918938533204673, 
                  normal_log<false>(0,0,1));
  EXPECT_FLOAT_EQ(-0.918938533204673, 
                  normal_log<false>(0,0,fvar<double>(1.0)).val());
  EXPECT_FLOAT_EQ(-0.918938533204673, 
                  normal_log<false>(0,fvar<double>(0),1).val());
  EXPECT_FLOAT_EQ(-0.918938533204673, 
                  normal_log<false>(0,fvar<double>(0),fvar<double>(1)).val());
  EXPECT_FLOAT_EQ(-0.918938533204673, 
                  normal_log<false>(fvar<double>(0),0,1).val());
  EXPECT_FLOAT_EQ(-0.918938533204673, 
                  normal_log<false>(fvar<double>(0),0,fvar<double>(1)).val());
  EXPECT_FLOAT_EQ(-0.918938533204673, 
                  normal_log<false>(fvar<double>(0),fvar<double>(0),1).val());
  EXPECT_FLOAT_EQ(-0.918938533204673, 
                  normal_log<false>(fvar<double>(0),fvar<double>(0),fvar<double>(1)).val());
}

TEST(ProbAgradDistributionsNormal, derivatives) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::prob::normal_log;
   
  std::vector<double> grad = test_fun(0,0,1);

  fvar<double> lp = normal_log<false>(0,0,fvar<double>(1.0,1));
  EXPECT_FLOAT_EQ(grad[2], lp.tangent());

  fvar<fvar<double> > y (1.0);
  fvar<double> x (1.0,2.0);
  EXPECT_NO_THROW(normal_log(y,1,1));
  EXPECT_FLOAT_EQ(normal_log(x,1,1).val_,-0.918938533204672741780);
  EXPECT_FLOAT_EQ(normal_log(x,2,1).d_,2);
  

}
TEST(ProbAgradDistributionsNormal, FvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::prob::normal_log;
   
  fvar<var> y_ (2,1);
  double mu (0);
  double sigma (1);

  fvar<var> logp = normal_log(y_,mu,sigma);

  AVEC y = createAVEC(y_.val_);
  VEC g;
  logp.val_.grad(y,g);
  EXPECT_FLOAT_EQ(-2, g[0]);

}
TEST(ProbAgradDistributionsNormal, FvarVar_2ndDeriv1) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::prob::normal_log;
   
  double y_ (1);
  fvar<var> mu (0,1);
  double sigma (1);
  fvar<var> logp = normal_log(y_,mu,sigma);

  AVEC y = createAVEC(mu.val_);
  VEC g;
  logp.d_.grad(y,g);
  EXPECT_FLOAT_EQ(-1, g[0]);
}
TEST(ProbAgradDistributionsNormal, FvarVar_2ndDeriv2) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::prob::normal_log;
   
  double y_ (1);
  double mu (0);
  fvar<var> sigma (1,1);
  fvar<var> logp = normal_log(y_,mu,sigma);

  AVEC y = createAVEC(sigma.val_);
  VEC g;
  logp.d_.grad(y,g);
  EXPECT_FLOAT_EQ(-2, g[0]);
}
