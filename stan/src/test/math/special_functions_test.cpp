#include <cmath>
#include <stdexcept>
#include <gtest/gtest.h>
#include "stan/math/special_functions.hpp"

TEST(MathsSpecialFunctions, log1m) {
  EXPECT_FLOAT_EQ(log1p(-0.1),stan::math::log1m(0.1));
}

TEST(MathsSpecialFunctions, log_loss) {
  EXPECT_FLOAT_EQ(0.0, stan::math::binary_log_loss(0,0.0));
  EXPECT_FLOAT_EQ(0.0, stan::math::binary_log_loss(1,1.0));
  EXPECT_FLOAT_EQ(-log(0.5), stan::math::binary_log_loss(0,0.5));
  EXPECT_FLOAT_EQ(-log(0.5), stan::math::binary_log_loss(1,0.5));
  EXPECT_FLOAT_EQ(-log(0.75), stan::math::binary_log_loss(0,0.25));
  EXPECT_FLOAT_EQ(-log(0.75), stan::math::binary_log_loss(1,0.75));
}


TEST(MathsSpecialFunctions, inv_cloglog) {
  EXPECT_EQ(std::exp(-std::exp(3.7)), stan::math::inv_cloglog(3.7));
  EXPECT_EQ(std::exp(-std::exp(0.0)), stan::math::inv_cloglog(0.0));
  EXPECT_EQ(std::exp(-std::exp(-2.93)), stan::math::inv_cloglog(-2.93));
}

TEST(MathsSpecialFunctions, Phi_approx) {
  EXPECT_EQ(0.5, stan::math::Phi_approx(0.0));
  EXPECT_NEAR(stan::math::Phi(0.9), stan::math::Phi_approx(0.9), 0.00014);
  EXPECT_NEAR(stan::math::Phi(-5.0), stan::math::Phi_approx(-5.0), 0.00014);
}

TEST(MathsSpecialFunctions, softmax) {
  std::vector<double> x;
  x.push_back(1.0);
  x.push_back(-1.0);
  x.push_back(2.0);
  std::vector<double> simplex(3);
  stan::math::softmax<std::vector<double>,double>(x,simplex);
  EXPECT_FLOAT_EQ(1.0, simplex[0] + simplex[1] + simplex[2]);
  double sum = exp(1.0) + exp(-1.0) + exp(2.0);
  EXPECT_FLOAT_EQ(exp(1.0)/sum, simplex[0]);
  EXPECT_FLOAT_EQ(exp(-1.0)/sum, simplex[1]);
  EXPECT_FLOAT_EQ(exp(2.0)/sum, simplex[2]);
}
TEST(MathsSpecialFunctions, softmax_exception) {
  std::vector<double> x;
  x.push_back(1.0);
  x.push_back(-1.0);
  x.push_back(2.0);
  std::vector<double> simplex(2);
  
  // dl: EXPECT_THROW is not able to handle this templating
  //EXPECT_THROW(stan::math::softmax<std::vector<double>,double>(x,simplex), std::invalid_argument);
  try{
    stan::math::softmax<std::vector<double>,double>(x,simplex);
    FAIL();
  } catch (std::invalid_argument e) {
    SUCCEED();
  }
}
TEST(MathsSpecialFunctions, inverse_softmax_exception) {
  std::vector<double> simplex(2);
  std::vector<double> y(3);
  EXPECT_THROW(stan::math::inverse_softmax< std::vector<double> >(simplex, y), std::invalid_argument);
}
TEST(MathsSpecialFunctions, log1p) {
  double x;

  x = 0;
  EXPECT_FLOAT_EQ (0.0, stan::math::log1p(x));
  x = 0.0000001;
  EXPECT_FLOAT_EQ (0.0000001, stan::math::log1p(x));
  x = 0.001;
  EXPECT_FLOAT_EQ (0.0009995003, stan::math::log1p(x));
  x = 0.1;
  EXPECT_FLOAT_EQ (0.09531018, stan::math::log1p(x));
  x = 1;
  EXPECT_FLOAT_EQ (0.6931472, stan::math::log1p(x));
  x = 10;
  EXPECT_FLOAT_EQ (2.397895, stan::math::log1p(x));

  x = -0.0000001;
  EXPECT_FLOAT_EQ (-0.0000001, stan::math::log1p(x));
  x = -0.001;
  EXPECT_FLOAT_EQ (-0.0010005, stan::math::log1p(x));
  x = -0.1;
  EXPECT_FLOAT_EQ (-0.1053605, stan::math::log1p(x));
  x = -0.999;
  EXPECT_FLOAT_EQ (-6.907755, stan::math::log1p(x));
  x = -1;
  EXPECT_FLOAT_EQ (-std::numeric_limits<double>::infinity(), stan::math::log1p(x));
}
TEST(MathsSpecialFunctions, log1p_exception) {
  double x;

  x = -2;
  EXPECT_THROW (stan::math::log1p(x), std::domain_error);
}
TEST(MathsSpecialFunctions, lmgamma) {
  unsigned int k = 1;
  double x = 2.5;
  double result = k * (k - 1) * log(boost::math::constants::pi<double>()) / 4.0;
  result += lgamma(x); // j = 1
  EXPECT_FLOAT_EQ(result, stan::math::lmgamma(k,x));

  k = 2;
  x = 3.0;
  result = k * (k - 1) * log(boost::math::constants::pi<double>()) / 4.0;
  result += lgamma(x); // j = 1
  result += lgamma(x + (1.0 - 2.0)/2.0); // j = 2
  EXPECT_FLOAT_EQ(result, stan::math::lmgamma(k,x));
}

TEST(MathsSpecialFunctions, if_else) {
  using stan::math::if_else;
  unsigned int c = 5;
  double x = 1.0;
  double y = -1.0;
  EXPECT_FLOAT_EQ(x, if_else(c,x,y));
  c = 0;
  EXPECT_FLOAT_EQ(y, if_else(c,x,y));

  bool d = true;
  int u = 1;
  int v = -1;
  EXPECT_EQ(1.0, stan::math::if_else(d,u,v));
  d = false;
  EXPECT_FLOAT_EQ(-1.0, stan::math::if_else(d,u,v));

  EXPECT_FLOAT_EQ(1.2,if_else(true,1.2,12));
  EXPECT_FLOAT_EQ(12.0,if_else(false,1.2,12));

  EXPECT_FLOAT_EQ(1.0,if_else(true,1,12.3));
  EXPECT_FLOAT_EQ(12.3,if_else(false,1,12.3));
}

TEST(MathsSpecialFunctions, square) {
  double y = 2.0;
  EXPECT_FLOAT_EQ(y * y, stan::math::square(y));

  y = 0.0;
  EXPECT_FLOAT_EQ(y * y, stan::math::square(y));

  y = -32.7;
  EXPECT_FLOAT_EQ(y * y, stan::math::square(y));
}

TEST(MathsSpecialFunctions, multiply_log) {
  double a = 2.0;
  double b = 3.0;
  EXPECT_FLOAT_EQ(a * log(b), stan::math::multiply_log(a,b));

  a = 0.0;
  b = 0.0;
  EXPECT_FLOAT_EQ(0.0, stan::math::multiply_log(a,b)) << 
    "when a and b are both 0, the result should be 0";

  a = 1.0;
  b = -1.0;
  EXPECT_TRUE(std::isnan(stan::math::multiply_log(a,b))) << 
    "log(b) with b < 0 should result in NaN";
}

TEST(MathsSpecialFunctions, pi_fun) {
  EXPECT_FLOAT_EQ(4.0 * std::atan(1.0), stan::math::pi());
}
TEST(MathsSpecialFunctions, e_fun) {
  EXPECT_FLOAT_EQ(std::exp(1.0), stan::math::e());
}
TEST(MathsSpecialFunctions, sqrt2_fun) {
  EXPECT_FLOAT_EQ(std::sqrt(2.0), stan::math::sqrt2());
}
TEST(MathsSpecialFunctions, log10_fun) {
  EXPECT_FLOAT_EQ(std::log(10.0), stan::math::log10());
}

TEST(MathsSpecialFunctions, infty) {
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::positive_infinity());
}
TEST(MathsSpecialFunctions, neg_infty) {
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  stan::math::negative_infinity());
}
TEST(MathsSpecialFunctions, nan) {
  EXPECT_TRUE(std::isnan(stan::math::not_a_number()));
}
TEST(MathsSpecialFunctions, epsilon) {
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::epsilon(),
                  stan::math::epsilon());
}
TEST(MathsSpecialFunctions, negative_epsilon) {
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::epsilon(),
                  stan::math::negative_epsilon());
}

void test_log_sum_exp(double a, double b) {
  using std::log;
  using std::exp;
  using stan::math::log_sum_exp;
  EXPECT_FLOAT_EQ(log(exp(a) + exp(b)),
                  log_sum_exp(a,b));
}

void test_log_sum_exp(const std::vector<double>& as) {
  using std::log;
  using std::exp;
  using stan::math::log_sum_exp;
  double sum_exp = 0.0;
  for (size_t n = 0; n < as.size(); ++n)
    sum_exp += exp(as[n]);
  EXPECT_FLOAT_EQ(log(sum_exp),
                  log_sum_exp(as));
}



TEST(MathsSpecialFunctions, log_sum_exp) {
  using stan::math::log_sum_exp;
  std::vector<double> as;
  test_log_sum_exp(as);
  as.push_back(0.0);
  test_log_sum_exp(as);
  as.push_back(1.0);
  test_log_sum_exp(as);
  as.push_back(-1.0);
  test_log_sum_exp(as);
  as.push_back(-10000.0);
  test_log_sum_exp(as);
  
  as.push_back(10000.0);
  EXPECT_FLOAT_EQ(10000.0, log_sum_exp(as));
}
TEST(MathsSpecialFunctions, log_sum_exp_2) {
  using stan::math::log_sum_exp;
  test_log_sum_exp(1.0,2.0);
  test_log_sum_exp(1.0,1.0);
  test_log_sum_exp(3.0,2.0);
  test_log_sum_exp(-20.0,12);
  test_log_sum_exp(-20.0,12);

  // exp(10000.0) overflows
  EXPECT_FLOAT_EQ(10000.0,log_sum_exp(10000.0,0.0));
  EXPECT_FLOAT_EQ(0.0,log_sum_exp(-10000.0,0.0));
}
TEST(MathsSpecialFunctions, log1p_exp) {
  using stan::math::log_sum_exp;
  using stan::math::log1p_exp;

  // exp(10000.0) overflows
  EXPECT_FLOAT_EQ(10000.0,log1p_exp(10000.0));
  EXPECT_FLOAT_EQ(0.0,log1p_exp(-10000.0));
}

TEST(MathsSpecialFunctions, ibeta) {
  using stan::math::ibeta;
  
  EXPECT_FLOAT_EQ(0.0, ibeta(0.5, 0.5, 0.0))  << "reasonable values for a, b, x";
  EXPECT_FLOAT_EQ(0.333333333, ibeta(0.5, 0.5, 0.25))  << "reasonable values for a, b, x";
  EXPECT_FLOAT_EQ(0.5, ibeta(0.5, 0.5, 0.5))  << "reasonable values for a, b, x";
  EXPECT_FLOAT_EQ(0.666666667, ibeta(0.5, 0.5, 0.75))  << "reasonable values for a, b, x";
  EXPECT_FLOAT_EQ(1.0, ibeta(0.5, 0.5, 1.0))  << "reasonable values for a, b, x";

  EXPECT_FLOAT_EQ(0.0, ibeta(0.1, 1.5, 0.0))  << "reasonable values for a, b, x";
  EXPECT_FLOAT_EQ(0.9117332, ibeta(0.1, 1.5, 0.25))  << "reasonable values for a, b, x";
  EXPECT_FLOAT_EQ(0.9645342, ibeta(0.1, 1.5, 0.5))  << "reasonable values for a, b, x";
  EXPECT_FLOAT_EQ(0.9897264, ibeta(0.1, 1.5, 0.75))  << "reasonable values for a, b, x";
  EXPECT_FLOAT_EQ(1.0, ibeta(0.1, 1.5, 1.0))  << "reasonable values for a, b, x";
}

TEST(MathsSpecialFunctions, value_of) {
  using stan::math::value_of;
  double x = 5.0;
  EXPECT_FLOAT_EQ(5.0,value_of(x));
  EXPECT_FLOAT_EQ(5.0,value_of(5));
}

TEST(MathSpecialFunctions, log_inv_logit) {
  using stan::math::log_inv_logit;
  using std::log;
  using stan::math::inv_logit;

  EXPECT_FLOAT_EQ(log(inv_logit(-7.2)), log_inv_logit(-7.2));
  EXPECT_FLOAT_EQ(log(inv_logit(0.0)), log_inv_logit(0.0));
  EXPECT_FLOAT_EQ(log(inv_logit(1.9)), log_inv_logit(1.9));
}
TEST(MathSpecialFunctions, log1m_inv_logit) {
  using stan::math::log1m_inv_logit;
  using std::log;
  using stan::math::inv_logit;

  EXPECT_FLOAT_EQ(log(1 - inv_logit(-7.2)), log1m_inv_logit(-7.2));
  EXPECT_FLOAT_EQ(log(1 - inv_logit(0.0)), log1m_inv_logit(0.0));
  EXPECT_FLOAT_EQ(log(1 - inv_logit(1.9)), log1m_inv_logit(1.9));
}
TEST(MathSpecialFunctions,logicalNegation) {
  using stan::math::logical_negation;
  EXPECT_TRUE(logical_negation(0));
  EXPECT_TRUE(logical_negation(0.0));
  EXPECT_TRUE(logical_negation(0.0f));

  EXPECT_FALSE(logical_negation(1));
  EXPECT_FALSE(logical_negation(2.0));
  EXPECT_FALSE(logical_negation(2.0f));
}

TEST(MathSpecialFunctions,logicalOr) {
  using stan::math::logical_or;
  EXPECT_TRUE(logical_or(1,0));
  EXPECT_TRUE(logical_or(0,1));
  EXPECT_TRUE(logical_or(1,1));
  EXPECT_TRUE(logical_or(5.7,-1.9));
  EXPECT_TRUE(logical_or(5.7,-1));

  EXPECT_FALSE(logical_or(0,0));
  EXPECT_FALSE(logical_or(0.0, 0.0));
  EXPECT_FALSE(logical_or(0.0, 0));
  EXPECT_FALSE(logical_or(0, 0.0));
}
TEST(MathSpecialFunctions,logicalAnd) {
  using stan::math::logical_and;
  EXPECT_TRUE(logical_and(1,1));
  EXPECT_TRUE(logical_and(5.7,-1.9));

  EXPECT_FALSE(logical_and(0,0));
  EXPECT_FALSE(logical_and(0,1));
  EXPECT_FALSE(logical_and(1,0));
  EXPECT_FALSE(logical_and(0.0, 0.0));
  EXPECT_FALSE(logical_and(0.0, 1.0));
  EXPECT_FALSE(logical_and(1, 0.0));
}
TEST(MathSpecialFunctions,logicalEq) {
  using stan::math::logical_eq;
  EXPECT_TRUE(logical_eq(1,1));
  EXPECT_TRUE(logical_eq(5.7,5.7));
  EXPECT_TRUE(logical_eq(0,0.0));

  EXPECT_FALSE(logical_eq(0,1));
  EXPECT_FALSE(logical_eq(1.0,0));
  EXPECT_FALSE(logical_eq(1, 2));
  EXPECT_FALSE(logical_eq(2.0, -1.0));
}
TEST(MathSpecialFunctions,logicalNeq) {
  using stan::math::logical_neq;
  EXPECT_TRUE(logical_neq(0,1));
  EXPECT_TRUE(logical_neq(1.0,0));
  EXPECT_TRUE(logical_neq(1, 2));
  EXPECT_TRUE(logical_neq(2.0, -1.0));

  EXPECT_FALSE(logical_neq(1,1));
  EXPECT_FALSE(logical_neq(5.7,5.7));
  EXPECT_FALSE(logical_neq(0,0.0));
}
TEST(MathSpecialFunctions,logicalLt) {
  using stan::math::logical_lt;
  EXPECT_TRUE(logical_lt(0,1));
  EXPECT_TRUE(logical_lt(1.0,2.0));
  EXPECT_TRUE(logical_lt(1, 2.0));
  EXPECT_TRUE(logical_lt(-1, 0));

  EXPECT_FALSE(logical_lt(1,1));
  EXPECT_FALSE(logical_lt(5.7,5.7));
  EXPECT_FALSE(logical_lt(5.7,-9.0));
  EXPECT_FALSE(logical_lt(0,0.0));
}
TEST(MathSpecialFunctions,logicalLte) {
  using stan::math::logical_lte;
  EXPECT_TRUE(logical_lte(0,1));
  EXPECT_TRUE(logical_lte(1.0,2.0));
  EXPECT_TRUE(logical_lte(1, 2.0));
  EXPECT_TRUE(logical_lte(-1, 0));
  EXPECT_TRUE(logical_lte(1,1));
  EXPECT_TRUE(logical_lte(5.7,5.7));

  EXPECT_FALSE(logical_lte(5.7,-9.0));
  EXPECT_FALSE(logical_lte(-1,-2));
}
TEST(MathSpecialFunctions,logicalGt) {
  using stan::math::logical_gt;
  EXPECT_TRUE(logical_gt(1,0));
  EXPECT_TRUE(logical_gt(2,1.00));
  EXPECT_TRUE(logical_gt(2.0,1));
  EXPECT_TRUE(logical_gt(0,-1));

  EXPECT_FALSE(logical_gt(1,1));
  EXPECT_FALSE(logical_gt(5.7,5.7));
  EXPECT_FALSE(logical_gt(-5.7,9.0));
  EXPECT_FALSE(logical_gt(0,0.0));
}
TEST(MathSpecialFunctions,logicalGte) {
  using stan::math::logical_gte;
  EXPECT_TRUE(logical_gte(1,0));
  EXPECT_TRUE(logical_gte(2.0,1.0));
  EXPECT_TRUE(logical_gte(2.0, 1));
  EXPECT_TRUE(logical_gte(0, -1));
  EXPECT_TRUE(logical_gte(1,1));
  EXPECT_TRUE(logical_gte(5.7,5.7));

  EXPECT_FALSE(logical_gte(-9.0, 5.7));
  EXPECT_FALSE(logical_gte(-2,-1));
}
TEST(MathSpecialFunctions,asBool) {
  using stan::math::as_bool;
  EXPECT_TRUE(as_bool(1));
  EXPECT_TRUE(as_bool(1.7));
  EXPECT_TRUE(as_bool(-1.7));
  EXPECT_TRUE(as_bool(std::numeric_limits<double>::infinity()));
  EXPECT_TRUE(as_bool(-std::numeric_limits<double>::infinity()));
  // don't like this behavior, but it's what C++ does
  EXPECT_TRUE(as_bool(std::numeric_limits<double>::quiet_NaN()));

  EXPECT_FALSE(as_bool(0));
  EXPECT_FALSE(as_bool(0.0));
  EXPECT_FALSE(as_bool(0.0f));
}
TEST(MathSpecialFunctions,BoostUseTr1Def) {
 bool BOOST_RESULT_OF_USE_TR1_is_defined = false;

#ifdef BOOST_RESULT_OF_USE_TR1
 BOOST_RESULT_OF_USE_TR1_is_defined = true;
#endif

 EXPECT_TRUE(BOOST_RESULT_OF_USE_TR1_is_defined);
}
TEST(MathSpecialFunctions,BoostNoDeclTypeDef) {
 bool BOOST_NO_DECLTYPE_is_defined = false;
#ifdef BOOST_NO_DECLTYPE
 BOOST_NO_DECLTYPE_is_defined = true;
#endif
 EXPECT_TRUE(BOOST_NO_DECLTYPE_is_defined);
}
