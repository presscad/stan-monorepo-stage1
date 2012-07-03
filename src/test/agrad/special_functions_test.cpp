#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <boost/math/special_functions.hpp>
#include <gtest/gtest.h>
#include "stan/agrad/agrad.hpp"
#include "stan/agrad/special_functions.hpp"

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


// cut and paste helpers and typedefs from agrad_test.cpp
typedef stan::agrad::var AVAR;
typedef std::vector<AVAR> AVEC;
typedef std::vector<double> VEC;

AVEC createAVEC(AVAR x) {
  AVEC v;
  v.push_back(x);
  return v;
}
AVEC createAVEC(AVAR x1, AVAR x2) {
  AVEC v;
  v.push_back(x1);
  v.push_back(x2);
  return v;
}
AVEC createAVEC(AVAR x1, AVAR x2, AVAR x3) {
  AVEC v;
  v.push_back(x1);
  v.push_back(x2);
  v.push_back(x3);
  return v;
}
// end cut-and-paste

TEST(agrad_agrad_special_functions,lgamma) {
  AVAR a = 3.0;
  AVAR f = lgamma(a);
  EXPECT_FLOAT_EQ(lgamma(3.0),f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(boost::math::digamma(3.0),grad_f[0]);
}

TEST(agrad_agrad_special_functions,fma_vvv) {
  AVAR a = 3.0;
  AVAR b = 5.0;
  AVAR c = 7.0;
  AVAR f = fma(a,b,c);
  EXPECT_FLOAT_EQ(3.0 * 5.0 + 7.0, f.val());
  
  AVEC x = createAVEC(a,b,c);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(5.0,grad_f[0]);
  EXPECT_FLOAT_EQ(3.0,grad_f[1]);
  EXPECT_FLOAT_EQ(1.0,grad_f[2]);
}  

TEST(agrad_agrad_special_functions,fma_vvd) {
  AVAR a = 3.0;
  AVAR b = 5.0;
  double c = 7.0;
  AVAR f = fma(a,b,c);
  EXPECT_FLOAT_EQ(3.0 * 5.0 + 7.0, f.val());
  
  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(5.0,grad_f[0]);
  EXPECT_FLOAT_EQ(3.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fma_vdv) {
  AVAR a = 3.0;
  double b = 5.0;
  AVAR c = 7.0;
  AVAR f = fma(a,b,c);
  EXPECT_FLOAT_EQ(3.0 * 5.0 + 7.0, f.val());
  
  AVEC x = createAVEC(a,c);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(5.0,grad_f[0]);
  EXPECT_FLOAT_EQ(1.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fma_vdd) {
  AVAR a = 3.0;
  double b = 5.0;
  double c = 7.0;
  AVAR f = fma(a,b,c);
  EXPECT_FLOAT_EQ(3.0 * 5.0 + 7.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(5.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fma_dvv) {
  double a = 3.0;
  AVAR b = 5.0;
  AVAR c = 7.0;
  AVAR f = fma(a,b,c);
  EXPECT_FLOAT_EQ(3.0 * 5.0 + 7.0, f.val());
  
  AVEC x = createAVEC(b,c);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(3.0,grad_f[0]);
  EXPECT_FLOAT_EQ(1.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fma_dvd) {
  double a = 3.0;
  AVAR b = 5.0;
  double c = 7.0;
  AVAR f = fma(a,b,c);
  EXPECT_FLOAT_EQ(3.0 * 5.0 + 7.0, f.val());
  
  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(3.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fma_ddv) {
  double a = 3.0;
  double b = 5.0;
  AVAR c = 7.0;
  AVAR f = fma(a,b,c);
  EXPECT_FLOAT_EQ(3.0 * 5.0 + 7.0, f.val());
  
  AVEC x = createAVEC(c);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  


TEST(agrad_agrad_special_functions,inv_logit) {
  AVAR a = 2.0;
  AVAR f = inv_logit(a);
  EXPECT_FLOAT_EQ(1.0 / (1.0 + exp(-2.0)),f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(exp(-2.0)/pow(1 + exp(-2.0),2.0),
                  grad_f[0]);
}

TEST(agrad_agrad_special_functions,log1p) {
  AVAR a = 0.1;
  AVAR f = log1p(a);
  EXPECT_FLOAT_EQ(log(1 + 0.1), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0 / (1.0 + 0.1), grad_f[0]);
}

TEST(agrad_agrad_special_functions,log1m) {
  AVAR a = 0.1;
  AVAR f = log1m(a);
  EXPECT_FLOAT_EQ(log(1 - 0.1), f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-1.0/(1.0 - 0.1), grad_f[0]);
}

TEST(agrad_agrad_special_functions,log_loss_zero) {
  AVAR y_hat = 0.2;
  int y = 0;
  AVAR f = log_loss(y,y_hat);
  EXPECT_FLOAT_EQ(-log(1.0 - 0.2), f.val());

  AVEC x = createAVEC(y_hat);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ((1.0 / (1.0 - 0.2)), grad_f[0]);
}

TEST(agrad_agrad_special_functions,log_loss_one) {
  AVAR y_hat = 0.2;
  int y = 1;
  AVAR f = log_loss(y,y_hat);
  EXPECT_FLOAT_EQ(-log(0.2), f.val());

  AVEC x = createAVEC(y_hat);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-1.0 / 0.2, grad_f[0]);
}

TEST(agrad_agrad_special_functions,acosh) {
  AVAR a = 1.3;
  AVAR f = acosh(a);
  EXPECT_FLOAT_EQ(acosh(1.3), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0/sqrt(1.3 * 1.3  - 1.0), grad_f[0]);
}

TEST(agrad_agrad_special_functions,asinh) {
  AVAR a = 0.2;
  AVAR f = asinh(a);
  EXPECT_FLOAT_EQ(asinh(0.2), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0/sqrt(0.2 * 0.2  + 1.0), grad_f[0]);
}

TEST(agrad_agrad_special_functions,atanh) {
  AVAR a = 0.3;
  AVAR f = atanh(a);
  EXPECT_FLOAT_EQ(atanh(0.3), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0/(1.0 - 0.3 * 0.3), grad_f[0]);
}

TEST(agrad_agrad_special_functions,erf) {
  AVAR a = 1.3;
  AVAR f = erf(a);
  EXPECT_FLOAT_EQ(boost::math::erf(1.3), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(2.0 / std::sqrt(boost::math::constants::pi<double>()) * std::exp(- 1.3 * 1.3), grad_f[0]);
}

TEST(agrad_agrad_special_functions,erfc) {
  AVAR a = 1.3;
  AVAR f = erfc(a);
  EXPECT_FLOAT_EQ(boost::math::erfc(1.3), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-2.0 / std::sqrt(boost::math::constants::pi<double>()) * std::exp(- 1.3 * 1.3), grad_f[0]);
}
  

TEST(agrad_agrad_special_functions,exp2_defaultpolicy) {
  AVAR a = 1.3;
  AVAR f = exp2(a);
  EXPECT_FLOAT_EQ(std::pow(2.0,1.3), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(std::pow(2.0,1.3) * std::log(2.0),grad_f[0]);
  
  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),
		  stan::math::exp2(a).val());
  
  a = std::numeric_limits<AVAR>::quiet_NaN();
  EXPECT_THROW(stan::math::exp2(a), std::domain_error);
}

TEST(agrad_agrad_special_functions,exp2_errnopolicy) {
  AVAR a = 1.3;
  AVAR f = exp2(a, errno_policy());
  EXPECT_FLOAT_EQ(std::pow(2.0,1.3), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(std::pow(2.0,1.3) * std::log(2.0),grad_f[0]);
  
  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),
		  stan::math::exp2(a, errno_policy()).val());

  a = std::numeric_limits<AVAR>::quiet_NaN();
  EXPECT_NO_THROW(f = stan::math::exp2(a, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
}

TEST(agrad_agrad_special_functions,expm1) {
  AVAR a = 1.3;
  AVAR f = expm1(a);
  EXPECT_FLOAT_EQ(boost::math::expm1(1.3), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(std::exp(1.3) - 1.0, grad_f[0]);
}  


TEST(agrad_agrad_special_functions,fmax_vv) {
  AVAR a = 1.3;
  AVAR b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
  EXPECT_FLOAT_EQ(1.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fmax_vv_2) {
  AVAR a = 2.3;
  AVAR b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.3,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
  EXPECT_FLOAT_EQ(0.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fmax_vv_3) {
  AVAR a = 2.0;
  AVAR b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  // arbitrary, but documented this way
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
  EXPECT_FLOAT_EQ(1.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fmax_vd) {
  AVAR a = 1.3;
  double b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmax_vd_2) {
  AVAR a = 2.3;
  double b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.3,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmax_vd_3) {
  AVAR a = 2.0;
  double b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmax_dv) {
  double a = 1.3;
  AVAR b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmax_dv_2) {
  double a = 2.3;
  AVAR b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.3,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmax_dv_3) {
  double a = 2.0;
  AVAR b = 2.0;
  AVAR f = fmax(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  // arbitrary, but doc this way
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmin_vv) {
  AVAR a = 1.3;
  AVAR b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(1.3,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
  EXPECT_FLOAT_EQ(0.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fmin_vv_2) {
  AVAR a = 2.3;
  AVAR b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
  EXPECT_FLOAT_EQ(1.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fmin_vv_3) {
  AVAR a = 2.0;
  AVAR b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  // arbitrary, but documented this way
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
  EXPECT_FLOAT_EQ(1.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,fmin_vd) {
  AVAR a = 1.3;
  double b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(1.3,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmin_vd_2) {
  AVAR a = 2.3;
  double b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmin_vd_3) {
  AVAR a = 2.0;
  double b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmin_dv) {
  double a = 1.3;
  AVAR b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(1.3,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmin_dv_2) {
  double a = 2.3;
  AVAR b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,fmin_dv_3) {
  double a = 2.0;
  AVAR b = 2.0;
  AVAR f = fmin(a,b);
  EXPECT_FLOAT_EQ(2.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  // arbitrary, but doc this way
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,hypot_vv) {
  AVAR a = 3.0;
  AVAR b = 4.0;
  AVAR f = hypot(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  // arbitrary, but doc this way
  EXPECT_FLOAT_EQ(3.0/5.0,grad_f[0]);
  EXPECT_FLOAT_EQ(4.0/5.0,grad_f[1]);
}  

TEST(agrad_agrad_special_functions,hypot_vd) {
  AVAR a = 3.0;
  double b = 4.0;
  AVAR f = hypot(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  // arbitrary, but doc this way
  EXPECT_FLOAT_EQ(3.0/5.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,hypot_dv) {
  double a = 3.0;
  AVAR b = 4.0;
  AVAR f = hypot(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  // arbitrary, but doc this way
  EXPECT_FLOAT_EQ(4.0/5.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,log2_defaultpolicy) {
  AVAR a = 3.0;
  AVAR f = log2(a);
  EXPECT_FLOAT_EQ(std::log(3.0)/std::log(2.0), f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0 / 3.0 / std::log(2.0), grad_f[0]);

  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),
		  stan::math::log2(a).val());

  a = std::numeric_limits<AVAR>::quiet_NaN();
  EXPECT_THROW(stan::math::log2(a), std::domain_error);
 
  a = -1;
  EXPECT_THROW(stan::math::log2(a), std::domain_error);
}

TEST(agrad_agrad_special_functions,log2_errnopolicy) {
  AVAR a = 3.0;
  AVAR f = log2(a);
  EXPECT_FLOAT_EQ(std::log(3.0)/std::log(2.0), f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0 / 3.0 / std::log(2.0), grad_f[0]);

  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),
		  stan::math::log2(a, errno_policy()).val());

  a = std::numeric_limits<AVAR>::quiet_NaN();
  EXPECT_NO_THROW(f = stan::math::log2(a, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));

  a = -1;
  EXPECT_NO_THROW(f = stan::math::log2(a, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));

}

TEST(agrad_agrad_special_functions,cbrt) {
  AVAR a = 27.0;
  AVAR f = cbrt(a);
  EXPECT_FLOAT_EQ(3.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0 / 3.0 / std::pow(27.0,2.0/3.0), grad_f[0]);
}

TEST(agrad_agrad_special_functions,trunc) {
  AVAR a = 1.2;
  AVAR f = trunc(a);
  EXPECT_FLOAT_EQ(1.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(agrad_agrad_special_functions,trunc_2) {
  AVAR a = -1.2;
  AVAR f = trunc(a);
  EXPECT_FLOAT_EQ(-1.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(agrad_agrad_special_functions,round) {
  AVAR a = 1.2;
  AVAR f = round(a);
  EXPECT_FLOAT_EQ(1.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(agrad_agrad_special_functions,round_2) {
  AVAR a = -1.2;
  AVAR f = round(a);
  EXPECT_FLOAT_EQ(-1.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(agrad_agrad_special_functions,round_3) {
  AVAR a = 1.7;
  AVAR f = round(a);
  EXPECT_FLOAT_EQ(2.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}


TEST(agrad_agrad_special_functions,round_4) {
  AVAR a = -1.7;
  AVAR f = round(a);
  EXPECT_FLOAT_EQ(-2.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(agrad_agrad_special_functions,fdim_vv_defaultpolicy) {
  AVAR a = 3.0;
  AVAR b = 4.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
  EXPECT_FLOAT_EQ(0.0,grad_f[1]);

  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,a).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(a,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(b,a).val());
  
  a = std::numeric_limits<AVAR>::quiet_NaN();
  EXPECT_THROW(stan::math::fdim(a,a), std::domain_error);
  EXPECT_THROW(stan::math::fdim(b,a), std::domain_error);
  EXPECT_THROW(stan::math::fdim(a,b), std::domain_error);
}  
TEST(agrad_agrad_special_functions,fdim_vv_errnopolicy) {
  AVAR a = 3.0;
  AVAR b = 4.0;
  AVAR f = fdim(a,b, errno_policy());
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
  EXPECT_FLOAT_EQ(0.0,grad_f[1]);

  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,a, errno_policy()).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(a,b,errno_policy()).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(b,a, errno_policy()).val());

  a = std::numeric_limits<AVAR>::quiet_NaN();
  EXPECT_NO_THROW(f = stan::math::fdim(a,a, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(b,a, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(a,b, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));

}  

TEST(agrad_agrad_special_functions,fdim_vv_2_errnopolicy) {
  AVAR a = 7.0;
  AVAR b = 2.0;
  AVAR f = fdim(a,b,errno_policy());
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
  EXPECT_FLOAT_EQ(-1.0,grad_f[1]);
  
  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,a, errno_policy()).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(a,b,errno_policy()).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(b,a, errno_policy()).val());

  a = std::numeric_limits<AVAR>::quiet_NaN();
  EXPECT_NO_THROW(f = stan::math::fdim(a,a, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(b,a, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(a,b, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
}  

TEST(agrad_agrad_special_functions,fdim_vv_2_defaultpolicy) {
  AVAR a = 7.0;
  AVAR b = 2.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
  EXPECT_FLOAT_EQ(-1.0,grad_f[1]);

  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,a).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(a,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(b,a).val());

  a = std::numeric_limits<AVAR>::quiet_NaN();
  EXPECT_THROW(stan::math::fdim(a,a), std::domain_error);
  EXPECT_THROW(stan::math::fdim(b,a), std::domain_error);
  EXPECT_THROW(stan::math::fdim(a,b), std::domain_error);
}  

TEST(agrad_agrad_special_functions,fdim_vd_defaultpolicy) {
  AVAR a = 3.0;
  double b = 4.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinityavar,infinitydouble).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinityavar,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinitydouble).val());
  
  AVAR nanavar = std::numeric_limits<AVAR>::quiet_NaN();
  double nandouble = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(stan::math::fdim(nanavar,nandouble), std::domain_error);
  EXPECT_THROW(stan::math::fdim(nanavar,b), std::domain_error);
  EXPECT_THROW(stan::math::fdim(a,nandouble), std::domain_error);
}  
TEST(agrad_agrad_special_functions,fdim_vd_errnopolicy) {
  AVAR a = 3.0;
  double b = 4.0;
  AVAR f = fdim(a,b, errno_policy());
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinityavar,infinitydouble, errno_policy()).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinityavar,b,errno_policy()).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinitydouble, errno_policy()).val());
  
  AVAR nanavar = std::numeric_limits<AVAR>::quiet_NaN();
  double nandouble = std::numeric_limits<double>::quiet_NaN();
  EXPECT_NO_THROW(f = stan::math::fdim(nanavar,nandouble, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(a,nandouble, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(nanavar,b, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
}  

TEST(agrad_agrad_special_functions,fdim_vd_2_defaultpolicy) {
  AVAR a = 7.0;
  double b = 2.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinityavar,infinitydouble).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinityavar,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinitydouble).val());

  AVAR nanavar = std::numeric_limits<AVAR>::quiet_NaN();
  double nandouble = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(stan::math::fdim(nanavar,nandouble), std::domain_error);
  EXPECT_THROW(stan::math::fdim(nanavar,b), std::domain_error);
  EXPECT_THROW(stan::math::fdim(a,nandouble), std::domain_error);
}  
TEST(agrad_agrad_special_functions,fdim_vd_2_errnopolicy) {
  AVAR a = 7.0;
  double b = 2.0;
  AVAR f = fdim(a,b, errno_policy());
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinityavar,infinitydouble, errno_policy()).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinityavar,b,errno_policy()).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinitydouble,errno_policy()).val());
  
  AVAR nanavar = std::numeric_limits<AVAR>::quiet_NaN();
  double nandouble = std::numeric_limits<double>::quiet_NaN();
  EXPECT_NO_THROW(f = stan::math::fdim(nanavar,nandouble, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(a,nandouble, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(nanavar,nandouble, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
}  

TEST(agrad_agrad_special_functions,fdim_dv_defaultpolicy) {
  double a = 3.0;
  AVAR b = 4.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
 
  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinitydouble,infinityavar).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinitydouble,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinityavar).val());
 
  AVAR nanavar = std::numeric_limits<AVAR>::quiet_NaN();
  double nandouble = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(stan::math::fdim(nandouble, nanavar), std::domain_error);
  EXPECT_THROW(stan::math::fdim(a,nanavar), std::domain_error);
  EXPECT_THROW(stan::math::fdim(nandouble,b), std::domain_error);
}

TEST(agrad_agrad_special_functions,fdim_dv_errnopolicy) {
  double a = 3.0;
  AVAR b = 4.0;
  AVAR f = fdim(a,b,errno_policy());
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
 
  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinitydouble,infinityavar, errno_policy()).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinitydouble,b,errno_policy()).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinityavar, errno_policy()).val());

  AVAR nanavar = std::numeric_limits<AVAR>::quiet_NaN();
  double nandouble = std::numeric_limits<double>::quiet_NaN();
  EXPECT_NO_THROW(f = stan::math::fdim(nandouble,nanavar, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(a,nanavar, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(nandouble,b, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
}    

TEST(agrad_agrad_special_functions,fdim_dv_2_defaultpolicy) {
  double a = 7.0;
  AVAR b = 2.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-1.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinitydouble,infinityavar).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinitydouble,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinityavar).val());
 
  AVAR nanavar  = std::numeric_limits<AVAR>::quiet_NaN();
  double nandouble = std::numeric_limits<double>::quiet_NaN();
  EXPECT_THROW(stan::math::fdim(nandouble,nanavar), std::domain_error);
  EXPECT_THROW(stan::math::fdim(nandouble,b), std::domain_error);
  EXPECT_THROW(stan::math::fdim(a,nanavar), std::domain_error);
}  
TEST(agrad_agrad_special_functions,fdim_dv_2_errnopolicy) {
  double a = 7.0;
  AVAR b = 2.0;
  AVAR f = fdim(a,b,errno_policy());
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-1.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinitydouble,infinityavar, errno_policy()).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinitydouble,b,errno_policy()).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinityavar, errno_policy()).val());
  
  AVAR nanavar = std::numeric_limits<AVAR>::quiet_NaN();
  double nandouble = std::numeric_limits<double>::quiet_NaN();
  EXPECT_NO_THROW(f = stan::math::fdim(nandouble,nanavar, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(nandouble,b, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
  EXPECT_NO_THROW(f = stan::math::fdim(a,nanavar, errno_policy()));
  EXPECT_TRUE(std::isnan(f.val()));
}   

TEST(agrad_agrad_special_functions,tgamma) {
  AVAR a = 3.5;
  AVAR f = tgamma(a);
  EXPECT_FLOAT_EQ(boost::math::tgamma(3.5),f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(boost::math::digamma(3.5) * boost::math::tgamma(3.5),grad_f[0]);
}  

TEST(agrad_agrad_special_functions,step) {
  AVAR a = 3.5;
  AVAR f = step(a);
  EXPECT_FLOAT_EQ(1.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,step_2) {
  AVAR a = 0.0;
  AVAR f = step(a);
  EXPECT_FLOAT_EQ(1.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  

TEST(agrad_agrad_special_functions,step_3) {
  AVAR a = -18765.3;
  AVAR f = step(a);
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  
 
TEST(agrad_agrad_special_functions,inv_cloglog) {
  AVAR a = 2.7;
  AVAR f = inv_cloglog(a);
  EXPECT_FLOAT_EQ(std::exp(-std::exp(2.7)),f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-std::exp(2.7 - std::exp(2.7)),grad_f[0]);
}

TEST(agrad_agrad_special_functions,log_sum_exp_vv) {
  AVAR a = 5.0;
  AVAR b = 2.0;
  AVAR f = log_sum_exp(a, b);
  EXPECT_FLOAT_EQ (std::log(std::exp(5) + std::exp(2)), f.val());
  
  AVEC x = createAVEC(a, b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(std::exp(5.0) / (std::exp(5.0) + std::exp(2.0)), grad_f[0]);
  EXPECT_FLOAT_EQ(std::exp(2.0) / (std::exp(5.0) + std::exp(2.0)), grad_f[1]);

  // underflow example
  a = 1000;
  b = 10;
  f = log_sum_exp(a, b);
  EXPECT_FLOAT_EQ (std::log(std::exp(0.0) + std::exp(-990.0)) + 1000.0, f.val());
  
  x = createAVEC(a, b);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ (std::exp (1000.0 - (std::log(std::exp(0.0) + std::exp(-999.0)) + 1000)), grad_f[0]);
  EXPECT_FLOAT_EQ (std::exp (10.0 - (std::log(std::exp(0.0) + std::exp(-999.0)) + 1000)), grad_f[1]);
}
TEST(agrad_agrad_special_functions,log_sum_exp_vd) {
  AVAR a = 5.0;
  double b = 2.0;
  AVAR f = log_sum_exp(a, b);
  EXPECT_FLOAT_EQ (std::log(std::exp(5) + std::exp(2)), f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(std::exp(5.0) / (std::exp(5.0) + std::exp(2.0)), grad_f[0]);

  // underflow example
  a = 1000;
  b = 10;
  f = log_sum_exp(a, b);
  EXPECT_FLOAT_EQ (std::log(std::exp(0.0) + std::exp(-990.0)) + 1000.0, f.val());
  
  x = createAVEC(a);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ (std::exp (1000.0 - (std::log(std::exp(0.0) + std::exp(-999.0)) + 1000)), grad_f[0]);
}
TEST(agrad_agrad_special_functions,log_sum_exp_dv) {
  double a = 5.0;
  AVAR b = 2.0;
  AVAR f = log_sum_exp(a, b);
  EXPECT_FLOAT_EQ (std::log(std::exp(5) + std::exp(2)), f.val());
  
  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(std::exp(2.0) / (std::exp(5.0) + std::exp(2.0)), grad_f[0]);

  // underflow example
  a = 10;
  b = 1000;
  f = log_sum_exp(a, b);
  EXPECT_FLOAT_EQ (std::log(std::exp(0.0) + std::exp(-990.0)) + 1000.0, f.val());
  
  x = createAVEC(b);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ (std::exp (1000.0 - (std::log(std::exp(0.0) + std::exp(-999.0)) + 1000)), grad_f[0]);
}
TEST(agrad_agrad_special_functions,log_sum_exp_vector) {
  // simple test
  AVEC x;
  x.push_back (5.0);
  x.push_back (2.0);
  
  AVAR f = log_sum_exp(x);
  EXPECT_FLOAT_EQ (std::log(std::exp(5) + std::exp(2)), f.val());
  
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(std::exp(5.0) / (std::exp(5.0) + std::exp(2.0)), grad_f[0]);
  EXPECT_FLOAT_EQ(std::exp(2.0) / (std::exp(5.0) + std::exp(2.0)), grad_f[1]);

  // longer test
  x.clear();
  x.push_back (1.0);
  x.push_back (2.0);
  x.push_back (3.0);
  x.push_back (4.0);
  x.push_back (5.0);
  f = log_sum_exp(x);
  double expected_log_sum_exp = std::log(std::exp(1) + std::exp(2) + std::exp(3) + std::exp(4) + std::exp(5));
  EXPECT_FLOAT_EQ (expected_log_sum_exp,
                   f.val());
  
  grad_f.clear();
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(std::exp(1.0) / exp(expected_log_sum_exp), grad_f[0]);
  EXPECT_FLOAT_EQ(std::exp(2.0) / exp(expected_log_sum_exp), grad_f[1]);
  EXPECT_FLOAT_EQ(std::exp(3.0) / exp(expected_log_sum_exp), grad_f[2]);
  EXPECT_FLOAT_EQ(std::exp(4.0) / exp(expected_log_sum_exp), grad_f[3]);
  EXPECT_FLOAT_EQ(std::exp(5.0) / exp(expected_log_sum_exp), grad_f[4]);

  // underflow example
  x.clear();
  x.push_back(1000.0);
  x.push_back(10.0);
  f = log_sum_exp(x);
  EXPECT_FLOAT_EQ (std::log(std::exp(0.0) + std::exp(-990.0)) + 1000.0, f.val());
  
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ (std::exp (1000.0 - (std::log(std::exp(0.0) + std::exp(-999.0)) + 1000)), grad_f[0]);
  EXPECT_FLOAT_EQ (std::exp (10.0 - (std::log(std::exp(0.0) + std::exp(-999.0)) + 1000)), grad_f[1]);

  // longer underflow example
  x.clear();
  x.push_back(800.0);
  x.push_back(900.0);
  x.push_back(10.0);
  x.push_back(0.0);
  x.push_back(-100.0);
  f = log_sum_exp(x);
  expected_log_sum_exp = std::log(std::exp(0.0) + std::exp(-100) + std::exp(-890.0) + std::exp(-900.0) + std::exp(-1000.0)) + 900.0;
  EXPECT_FLOAT_EQ (expected_log_sum_exp, 
                   f.val());
  
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ (std::exp ( 800.0 - expected_log_sum_exp), grad_f[0]);
  EXPECT_FLOAT_EQ (std::exp ( 900.0 - expected_log_sum_exp), grad_f[1]);
  EXPECT_FLOAT_EQ (std::exp (  10.0 - expected_log_sum_exp), grad_f[2]);
  EXPECT_FLOAT_EQ (std::exp (   0.0 - expected_log_sum_exp), grad_f[3]);
  EXPECT_FLOAT_EQ (std::exp (-100.0 - expected_log_sum_exp), grad_f[4]);
}

TEST(agrad_agrad_special_functions,square) {
  AVAR a = 7.0;
  AVEC x = createAVEC(a);
  AVAR f = square(a);
  EXPECT_FLOAT_EQ(49.0, f.val());

  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_EQ(1U,grad_f.size());
  EXPECT_FLOAT_EQ(14.0, grad_f[0]);
}


TEST(AgradAgrad,multiplyLogChainVV) {
  AVAR a = 19.7;
  AVAR b = 1299.1;
  AVAR f = 2.0 * multiply_log(a,b);

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);

  EXPECT_FLOAT_EQ(2.0 * log(b.val()), grad_f[0]);
  EXPECT_FLOAT_EQ(2.0 * a.val() / b.val(), grad_f[1]);
}
TEST(AgradAgrad,multiplyLogChainDV) {
  double a = 19.7;
  AVAR b = 1299.1;
  AVAR f = 2.0 * multiply_log(a,b);

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);

  EXPECT_FLOAT_EQ(2.0 * a / b.val(), grad_f[0]);
}
TEST(AgradAgrad,multiplyLogChainVD) {
  AVAR a = 19.7;
  double b = 1299.1;
  AVAR f = 2.0 * multiply_log(a,b);

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);

  EXPECT_FLOAT_EQ(2.0 * log(b), grad_f[0]);
}
TEST(AgradAgrad,multiply_log_var_var) {
  AVAR a = 2.2;
  AVAR b = 3.3;
  AVAR f = multiply_log(a,b);
  EXPECT_FLOAT_EQ(2.2*log(3.3),f.val()) << "Reasonable values";

  AVEC x = createAVEC(a,b);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(log(b.val()),g[0]);
  EXPECT_FLOAT_EQ(a.val()/b.val(),g[1]);

  a = 0.0;
  b = 0.0;
  f = multiply_log(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val()) << "a and b both 0";

  x = createAVEC(a,b);
  g.resize(0);
  f.grad(x,g);
  EXPECT_FLOAT_EQ(log(b.val()),g[0]);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),g[1]);
}

TEST(AgradAgrad,multiply_log_var_double){
  AVAR a = 2.2;
  double b = 3.3;
  AVAR f = multiply_log(a,b);
  EXPECT_FLOAT_EQ(2.2*log(3.3),f.val()) << "Reasonable values";

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(log(b),g[0]);

  a = 0.0;
  b = 0.0;
  f = multiply_log(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val()) << "a and b both 0";

  x = createAVEC(a);
  g.resize(0);
  f.grad(x,g);
  EXPECT_FLOAT_EQ(log(b),g[0]);
}
TEST(AgradAgrad,multiply_log_double_var){
  double a = 2.2;
  AVAR b = 3.3;
  AVAR f = multiply_log(a,b);
  EXPECT_FLOAT_EQ(2.2*log(3.3),f.val()) << "Reasonable values";

  AVEC x = createAVEC(b);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(a/b.val(),g[0]);

  a = 0.0;
  b = 0.0;
  f = multiply_log(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val()) << "a and b both 0";

  x = createAVEC(b);
  g.resize(0);
  f.grad(x,g);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),g[0]);
}

void test_log_sum_exp_2_vv(double a_val, 
                           double b_val) {
  using std::exp;
  using std::log;
  using stan::math::log_sum_exp;

  AVAR a(a_val);
  AVAR b(b_val);

  AVEC x = createAVEC(a,b);
  AVAR f = log_sum_exp(a,b);
  VEC g;
  f.grad(x,g);
  
  double f_val = f.val();

  stan::agrad::var a2(a_val);
  stan::agrad::var b2(b_val);
  AVEC x2 = createAVEC(a2,b2);
  AVAR f2 = log(exp(a2) + exp(b2));
  VEC g2;
  f2.grad(x2,g2);

  EXPECT_FLOAT_EQ(f2.val(), f_val);
  EXPECT_EQ(2U,g.size());
  EXPECT_EQ(2U,g2.size());
  EXPECT_FLOAT_EQ(g2[0],g[0]);
  EXPECT_FLOAT_EQ(g2[1],g[1]);
}
void test_log_sum_exp_2_vd(double a_val,
                           double b) {
  using std::exp;
  using std::log;
  using stan::math::log_sum_exp;

  AVAR a(a_val);
  AVEC x = createAVEC(a);
  AVAR f = log_sum_exp(a,b);
  VEC g;
  f.grad(x,g);
  
  double f_val = f.val();

  stan::agrad::var a2(a_val);
  AVEC x2 = createAVEC(a2);
  AVAR f2 = log(exp(a2) + exp(b));
  VEC g2;
  f2.grad(x2,g2);

  EXPECT_FLOAT_EQ(f2.val(), f_val);
  EXPECT_EQ(1U,g.size());
  EXPECT_EQ(1U,g2.size());
  EXPECT_FLOAT_EQ(g2[0],g[0]);
  
}
void test_log_sum_exp_2_dv(double a,
                           double b_val) {
  using std::exp;
  using std::log;
  using stan::math::log_sum_exp;

  AVAR b(b_val);
  AVEC x = createAVEC(b);
  AVAR f = log_sum_exp(a,b);
  VEC g;
  f.grad(x,g);
  
  double f_val = f.val();

  AVAR b2(b_val);
  AVEC x2 = createAVEC(b2);
  AVAR f2 = log(exp(a) + exp(b2));
  VEC g2;
  f2.grad(x2,g2);

  EXPECT_FLOAT_EQ(f2.val(), f_val);
  EXPECT_EQ(1U,g.size());
  EXPECT_EQ(1U,g2.size());
  EXPECT_FLOAT_EQ(g2[0],g[0]);
  
}

void test_log_sum_exp_2(double a, double b) {
  test_log_sum_exp_2_vv(a,b);
  test_log_sum_exp_2_vd(a,b);
  test_log_sum_exp_2_dv(a,b);
}

TEST(AgradSpecialFunctions,log_sum_exp_2) {
  test_log_sum_exp_2(0.0,0.0);
  test_log_sum_exp_2(1.0,2.0);
  test_log_sum_exp_2(2.0,1.0);
  test_log_sum_exp_2(-2.0,15.0);
  test_log_sum_exp_2(2.0,-15.0);
}

void test_log1p_exp(double val) {
  using stan::math::log1p_exp;
  using stan::agrad::log1p_exp;
  AVAR a(val);   
  AVEC x = createAVEC(a);
  AVAR f = log1p_exp(a);
  EXPECT_FLOAT_EQ(log1p_exp(val), f.val());
  VEC g;
  f.grad(x,g);
  double f_val = f.val();
  
  AVAR a2(val);
  AVEC x2 = createAVEC(a2);
  AVAR f2 = log(1.0 + exp(a2));
  VEC g2;
  f2.grad(x2,g2);

  EXPECT_EQ(1U,g.size());
  EXPECT_EQ(1U,g2.size());
  EXPECT_FLOAT_EQ(g2[0],g[0]);
  EXPECT_FLOAT_EQ(f2.val(),f_val);
}

TEST(AgradSpecialFunctions, log1p_exp) {
  test_log1p_exp(-15.0);
  test_log1p_exp(-5.0);
  test_log1p_exp(-1.0);
  test_log1p_exp(0.0);
  test_log1p_exp(2.0);
  test_log1p_exp(32.0);
  test_log1p_exp(64.0);
}


TEST(AgradSpecialFunctions, log_sum_exp_vec_1) {
  using stan::math::log_sum_exp;
  using stan::agrad::log_sum_exp;
  AVAR a(5.0);
  AVEC as = createAVEC(a);
  AVEC x = createAVEC(a);
  AVAR f = log_sum_exp(as);
  EXPECT_FLOAT_EQ(5.0, f.val());
  VEC g;
  f.grad(x,g);
  EXPECT_EQ(1U,g.size());
  EXPECT_FLOAT_EQ(1.0,g[0]);
}


TEST(AgradSpecialFunctions, log_sum_exp_vec_2) {
  using stan::math::log_sum_exp;
  using stan::agrad::log_sum_exp;
  AVAR a(5.0);
  AVAR b(-7.0);
  AVEC as = createAVEC(a,b);
  AVEC x = createAVEC(a,b);
  AVAR f = log_sum_exp(as);
  EXPECT_FLOAT_EQ(log(exp(5.0) + exp(-7.0)), f.val());
  VEC g;
  f.grad(x,g);

  double f_val = f.val();

  AVAR a2(5.0);
  AVAR b2(-7.0);
  AVEC as2 = createAVEC(a2,b2);
  AVEC x2 = createAVEC(a2,b2);
  AVAR f2 = log(exp(a2) + exp(b2));
  VEC g2;
  f2.grad(x2,g2);

  EXPECT_FLOAT_EQ(f2.val(), f_val);
  EXPECT_EQ(2U,g.size());
  EXPECT_EQ(2U,g2.size());
  EXPECT_FLOAT_EQ(g[0],g2[0]);
  EXPECT_FLOAT_EQ(g[1],g2[1]);
}

TEST(AgradSpecialFunctions, log_sum_exp_vec_3) {
  using stan::math::log_sum_exp;
  using stan::agrad::log_sum_exp;
  AVAR a(5.0);
  AVAR b(-7.0);
  AVAR c(2.3);
  AVEC as = createAVEC(a,b,c);
  AVEC x = createAVEC(a,b,c);
  AVAR f = log_sum_exp(as);
  EXPECT_FLOAT_EQ(log(exp(5.0) + exp(-7.0) + exp(2.3)), f.val());
  VEC g;
  f.grad(x,g);

  double f_val = f.val();

  AVAR a2(5.0);
  AVAR b2(-7.0);
  AVAR c2(2.3);
  AVEC as2 = createAVEC(a2,b2,c2);
  AVEC x2 = createAVEC(a2,b2,c2);
  AVAR f2 = log(exp(a2) + exp(b2) + exp(c2));
  VEC g2;
  f2.grad(x2,g2);

  EXPECT_FLOAT_EQ(f2.val(), f_val);
  EXPECT_EQ(3U,g.size());
  EXPECT_EQ(3U,g2.size());
  EXPECT_FLOAT_EQ(g[0],g2[0]);
  EXPECT_FLOAT_EQ(g[1],g2[1]);
  EXPECT_FLOAT_EQ(g[2],g2[2]);
}

TEST(AgradSpecialFunctions,int_step) {
  using stan::math::int_step;

  AVAR a(5.0);
  AVAR b(0.0);
  AVAR c(-1.0);
  
  EXPECT_EQ(1U,int_step(a));
  EXPECT_EQ(0U,int_step(b));
  EXPECT_EQ(0U,int_step(c));
}

TEST(AgradSpecialFunctions,if_else) {
  using stan::agrad::var;
  using stan::math::if_else;
  using stan::agrad::if_else;
  
  EXPECT_FLOAT_EQ(1.0,if_else(true,var(1.0),var(2.0)).val());
  EXPECT_FLOAT_EQ(2.0,if_else(false,var(1.0),var(2.0)).val());

  EXPECT_FLOAT_EQ(1.0,if_else(true,1.0,var(2.0)).val());
  EXPECT_FLOAT_EQ(2.0,if_else(false,1.0,var(2.0)).val());

  EXPECT_FLOAT_EQ(1.0,if_else(true,var(1.0),2.0).val());
  EXPECT_FLOAT_EQ(2.0,if_else(false,var(1.0),2.0).val());
}

TEST(AgradSpecialFunctions,ibeta_vvv) {
  using stan::agrad::var;
  using stan::math::ibeta;
  using stan::agrad::ibeta;
  
  using boost::math::ibeta_derivative;

  AVAR a = 0.6;
  AVAR b = 0.3;
  AVAR c = 0.5;
  AVAR f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.3121373, f.val());
  
  AVEC x = createAVEC(a,b,c);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-0.436993,grad_f[0]);
  EXPECT_FLOAT_EQ(0.7779751,grad_f[1]);
  EXPECT_FLOAT_EQ(ibeta_derivative(a.val(), b.val(), c.val()),grad_f[2]);

  a = 3;
  b = 2;
  c = 0.2;
  f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.0272, f.val());
  x = createAVEC(a,b,c);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-0.03737671,grad_f[0]);
  EXPECT_FLOAT_EQ(0.02507405,grad_f[1]);
  EXPECT_FLOAT_EQ(ibeta_derivative(a.val(), b.val(), c.val()),grad_f[2]);
}
TEST(AgradSpecialFunctions,ibeta_vvd) {
  using stan::agrad::var;
  using stan::math::ibeta;
  using stan::agrad::ibeta;
  
  using boost::math::ibeta_derivative;

  AVAR a = 0.6;
  AVAR b = 0.3;
  double c = 0.5;
  AVAR f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.3121373, f.val());
  
  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-0.436993,grad_f[0]);
  EXPECT_FLOAT_EQ(0.7779751,grad_f[1]);
  
  a = 3;
  b = 2;
  c = 0.2;
  f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.0272, f.val());
  x = createAVEC(a,b);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-0.03737671,grad_f[0]);
  EXPECT_FLOAT_EQ(0.02507405,grad_f[1]);
}
TEST(AgradSpecialFunctions,ibeta_vdv) {
  using stan::agrad::var;
  using stan::math::ibeta;
  using stan::agrad::ibeta;
  
  using boost::math::ibeta_derivative;

  AVAR a = 0.6;
  double b = 0.3;
  AVAR c = 0.5;
  AVAR f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.3121373, f.val());
  
  AVEC x = createAVEC(a,c);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-0.436993,grad_f[0]);
  EXPECT_FLOAT_EQ(ibeta_derivative(a.val(), b, c.val()),grad_f[1]);

  a = 3;
  b = 2;
  c = 0.2;
  f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.0272, f.val());
  x = createAVEC(a,c);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-0.03737671,grad_f[0]);
  EXPECT_FLOAT_EQ(ibeta_derivative(a.val(), b, c.val()),grad_f[1]);
}
TEST(AgradSpecialFunctions,ibeta_vdd) {
  using stan::agrad::var;
  using stan::math::ibeta;
  using stan::agrad::ibeta;
  
  using boost::math::ibeta_derivative;

  AVAR a = 0.6;
  double b = 0.3;
  double c = 0.5;
  AVAR f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.3121373, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-0.436993,grad_f[0]);

  a = 3;
  b = 2;
  c = 0.2;
  f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.0272, f.val());
  x = createAVEC(a);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-0.03737671,grad_f[0]);
}
TEST(AgradSpecialFunctions,ibeta_dvv) {
  using stan::agrad::var;
  using stan::math::ibeta;
  using stan::agrad::ibeta;
  
  using boost::math::ibeta_derivative;

  double a = 0.6;
  AVAR b = 0.3;
  AVAR c = 0.5;
  AVAR f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.3121373, f.val());
  
  AVEC x = createAVEC(b,c);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.7779751,grad_f[0]);
  EXPECT_FLOAT_EQ(ibeta_derivative(a, b.val(), c.val()),grad_f[1]);

  a = 3;
  b = 2;
  c = 0.2;
  f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.0272, f.val());
  x = createAVEC(b,c);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.02507405,grad_f[0]);
  EXPECT_FLOAT_EQ(ibeta_derivative(a, b.val(), c.val()),grad_f[1]);
}
TEST(AgradSpecialFunctions,ibeta_dvd) {
  using stan::agrad::var;
  using stan::math::ibeta;
  using stan::agrad::ibeta;
  
  using boost::math::ibeta_derivative;

  double a = 0.6;
  AVAR b = 0.3;
  double c = 0.5;
  AVAR f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.3121373, f.val());
  
  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.7779751,grad_f[0]);

  a = 3;
  b = 2;
  c = 0.2;
  f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.0272, f.val());
  x = createAVEC(b);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.02507405,grad_f[0]);
}
TEST(AgradSpecialFunctions,ibeta_ddv) {
  using stan::agrad::var;
  using stan::math::ibeta;
  using stan::agrad::ibeta;
  
  using boost::math::ibeta_derivative;

  double a = 0.6;
  double b = 0.3;
  AVAR c = 0.5;
  AVAR f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.3121373, f.val());
  
  AVEC x = createAVEC(c);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(ibeta_derivative(a, b, c.val()),grad_f[0]);

  a = 3;
  b = 2;
  c = 0.2;
  f = ibeta(a,b,c);
  EXPECT_FLOAT_EQ(0.0272, f.val());
  x = createAVEC(c);
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(ibeta_derivative(a, b, c.val()),grad_f[0]);
}

TEST(AgradSpecialFunctions,value_of) {
  using stan::agrad::var;
  using stan::math::value_of;

  var a = 5.0;
  EXPECT_FLOAT_EQ(5.0, value_of(a));
  EXPECT_FLOAT_EQ(5.0, value_of(5.0)); // make sure all work together
  EXPECT_FLOAT_EQ(5.0, value_of(5));
}
