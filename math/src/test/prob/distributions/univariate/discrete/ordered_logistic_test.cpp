#include <gtest/gtest.h>
#include <stan/math/special_functions.hpp>
#include <stan/prob/distributions/univariate/discrete/ordered_logistic.hpp>

using Eigen::Matrix;
using Eigen::Dynamic;

typedef Eigen::Matrix<double,Eigen::Dynamic,1> vector_d;

vector_d
get_simplex(double lambda, 
           const vector_d& c) {
  using stan::math::inv_logit;
  int K = c.size() + 2;
  vector_d theta(K);
  // see p. 119, Gelman and Hill
  theta(0) = 1.0 - inv_logit(lambda);
  theta(1) = inv_logit(lambda) - inv_logit(lambda - c(0));
  for (int k = 2; k < (K - 1); ++k)
    theta(k) = inv_logit(lambda - c(k - 2)) - inv_logit(lambda - c(k - 1));
  theta(K-1) = inv_logit(lambda - c(K-3)); // - 0.0
  return theta;
}



TEST(ProbDistributions,ordered_logistic_vals) {
  using Eigen::Matrix;
  using Eigen::Dynamic;

  using stan::prob::ordered_logistic_log;
  using stan::math::inv_logit;

  int K = 5;
  Matrix<double,Dynamic,1> c(K-2);
  c << 0.9, 1.2, 2.6;
  double lambda = 1.1;
  
  vector_d theta = get_simplex(lambda,c);

  double sum = 0.0;
  for (int k = 0; k < theta.size(); ++k)
    sum += theta(k);
  EXPECT_FLOAT_EQ(1.0,sum);


  for (int k = 0; k < K; ++k) 
    EXPECT_FLOAT_EQ(log(theta(k)),ordered_logistic_log(k+1,lambda,c));

  EXPECT_THROW(ordered_logistic_log(0,lambda,c),std::domain_error);
  EXPECT_THROW(ordered_logistic_log(6,lambda,c),std::domain_error);
}

TEST(ProbDistributions,ordered_logistic_vals_2) {
  using Eigen::Matrix;
  using Eigen::Dynamic;

  using stan::prob::ordered_logistic_log;
  using stan::math::inv_logit;

  int K = 3;
  Matrix<double,Dynamic,1> c(K-2);
  c << 0.4;
  double lambda = -0.9;
  
  vector_d theta = get_simplex(lambda,c);

  double sum = 0.0;
  for (int k = 0; k < theta.size(); ++k)
    sum += theta(k);
  EXPECT_FLOAT_EQ(1.0,sum);

  for (int k = 0; k < K; ++k)
    EXPECT_FLOAT_EQ(log(theta(k)),ordered_logistic_log(k+1,lambda,c));

  EXPECT_THROW(ordered_logistic_log(0,lambda,c),std::domain_error);
  EXPECT_THROW(ordered_logistic_log(4,lambda,c),std::domain_error);
}

TEST(ProbDistributions,ordered_logistic_default_policy) {
  using stan::prob::ordered_logistic_log;
  int K = 4;
  Eigen::Matrix<double,Eigen::Dynamic,1> c(2);
  c << 0.1, 1.2;
  double lambda = 0.5;
  EXPECT_THROW(ordered_logistic_log(-1,lambda,c),std::domain_error);
  EXPECT_THROW(ordered_logistic_log(0,lambda,c),std::domain_error);
  EXPECT_THROW(ordered_logistic_log(5,lambda,c),std::domain_error);
  for (int k = 1; k <= K; ++k)
    EXPECT_NO_THROW(ordered_logistic_log(k,lambda,c));

  Eigen::Matrix<double,Eigen::Dynamic,1> c_zero; // init size zero
  EXPECT_EQ(0,c_zero.size());
  EXPECT_THROW(ordered_logistic_log(1,lambda,c_zero),std::domain_error);

  Eigen::Matrix<double,Eigen::Dynamic,1> c_neg(1); // init size zero
  c_neg << -13.7;
  EXPECT_THROW(ordered_logistic_log(1,lambda,c_neg),std::domain_error);

  Eigen::Matrix<double,Eigen::Dynamic,1> c_unord(3); // init size zero
  c_unord << 1.0, 0.4, 2.0;
  EXPECT_THROW(ordered_logistic_log(1,lambda,c_unord),std::domain_error);

  Eigen::Matrix<double,Eigen::Dynamic,1> c_unord_2(3); // init size zero
  c_unord_2 << 1.0, 2.0, 0.4;
  EXPECT_THROW(ordered_logistic_log(1,lambda,c_unord_2),std::domain_error);

  double nan = std::numeric_limits<double>::quiet_NaN();
  double inf = std::numeric_limits<double>::infinity();

  EXPECT_THROW(ordered_logistic_log(1,nan,c),std::domain_error);
  EXPECT_THROW(ordered_logistic_log(1,inf,c),std::domain_error);

  Eigen::Matrix<double,Eigen::Dynamic,1> cbad(2); // init size zero
  cbad << 0.2, inf;
  EXPECT_THROW(ordered_logistic_log(1,1.0,cbad),std::domain_error);
  cbad[1] = nan;
  EXPECT_THROW(ordered_logistic_log(1,1.0,cbad),std::domain_error);

  Eigen::Matrix<double,Eigen::Dynamic,1> cbad1(1); // init size zero
  cbad1 <<  inf;
  EXPECT_THROW(ordered_logistic_log(1,1.0,cbad1),std::domain_error);
  cbad1[0] = nan;
  EXPECT_THROW(ordered_logistic_log(1,1.0,cbad1),std::domain_error);

  Eigen::Matrix<double,Eigen::Dynamic,1> cbad3(3); // init size zero
  cbad3 <<  0.5, inf, 1.0;
  EXPECT_THROW(ordered_logistic_log(1,1.0,cbad3),std::domain_error);
  cbad3[1] = nan;
  EXPECT_THROW(ordered_logistic_log(1,1.0,cbad3),std::domain_error);
  
}

using boost::math::policies::policy;
using boost::math::policies::evaluation_error;
using boost::math::policies::domain_error;
using boost::math::policies::overflow_error;
using boost::math::policies::domain_error;
using boost::math::policies::pole_error;
using boost::math::policies::errno_on_error;

typedef policy<
  domain_error<errno_on_error>, 
  pole_error<errno_on_error>,
  overflow_error<errno_on_error>,
  evaluation_error<errno_on_error> 
  > errno_policy;

void expect_nan(double x) {
  EXPECT_TRUE(std::isnan(x));
}

TEST(ProbDistributions,ordered_logistic_errno_policy) {
  using stan::prob::ordered_logistic_log;
  int K = 4;
  Eigen::Matrix<double,Eigen::Dynamic,1> c(2);
  c << 0.1, 1.2;
  double lambda = 0.5;

  expect_nan(ordered_logistic_log(-1,lambda,c, errno_policy()));

  expect_nan(ordered_logistic_log(0,lambda,c,errno_policy()));
  expect_nan(ordered_logistic_log(5,lambda,c,errno_policy()));
  for (int k = 1; k <= K; ++k)
    EXPECT_NO_THROW(ordered_logistic_log(k,lambda,c));

  Eigen::Matrix<double,Eigen::Dynamic,1> c_zero; // init size zero
  EXPECT_EQ(0,c_zero.size());
  expect_nan(ordered_logistic_log(1,lambda,c_zero,errno_policy()));

  Eigen::Matrix<double,Eigen::Dynamic,1> c_neg(1); // init size zero
  c_neg << -13.7;
  expect_nan(ordered_logistic_log(1,lambda,c_neg,errno_policy()));

  Eigen::Matrix<double,Eigen::Dynamic,1> c_unord(3); // init size zero
  c_unord << 1.0, 0.4, 2.0;
  expect_nan(ordered_logistic_log(1,lambda,c_unord,errno_policy()));

  Eigen::Matrix<double,Eigen::Dynamic,1> c_unord_2(3); // init size zero
  c_unord_2 << 1.0, 2.0, 0.4;
  expect_nan(ordered_logistic_log(1,lambda,c_unord_2,errno_policy()));

  double nan = std::numeric_limits<double>::quiet_NaN();
  double inf = std::numeric_limits<double>::infinity();

  expect_nan(ordered_logistic_log(1,nan,c,errno_policy()));
  expect_nan(ordered_logistic_log(1,inf,c,errno_policy()));

  Eigen::Matrix<double,Eigen::Dynamic,1> cbad(2); // init size zero
  cbad << 0.2, inf;
  expect_nan(ordered_logistic_log(1,1.0,cbad,errno_policy()));
  cbad[1] = nan;
  expect_nan(ordered_logistic_log(1,1.0,cbad,errno_policy()));

  Eigen::Matrix<double,Eigen::Dynamic,1> cbad1(1); // init size zero
  cbad1 <<  inf;
  expect_nan(ordered_logistic_log(1,1.0,cbad1,errno_policy()));
  cbad1[0] = nan;
  expect_nan(ordered_logistic_log(1,1.0,cbad1,errno_policy()));

  Eigen::Matrix<double,Eigen::Dynamic,1> cbad3(3); // init size zero
  cbad3 <<  0.5, inf, 1.0;
  expect_nan(ordered_logistic_log(1,1.0,cbad3,errno_policy()));
  cbad3[1] = nan;
  expect_nan(ordered_logistic_log(1,1.0,cbad3,errno_policy()));

}

