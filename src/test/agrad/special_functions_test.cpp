#include <stan/agrad/agrad.hpp>
#include <gtest/gtest.h>
#include <stan/math.hpp>

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

TEST(AgradRev,trunc) {
  AVAR a = 1.2;
  AVAR f = trunc(a);
  EXPECT_FLOAT_EQ(1.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(AgradRev,trunc_2) {
  AVAR a = -1.2;
  AVAR f = trunc(a);
  EXPECT_FLOAT_EQ(-1.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(AgradRev,round) {
  AVAR a = 1.2;
  AVAR f = round(a);
  EXPECT_FLOAT_EQ(1.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(AgradRev,round_2) {
  AVAR a = -1.2;
  AVAR f = round(a);
  EXPECT_FLOAT_EQ(-1.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}

TEST(AgradRev,round_3) {
  AVAR a = 1.7;
  AVAR f = round(a);
  EXPECT_FLOAT_EQ(2.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}


TEST(AgradRev,round_4) {
  AVAR a = -1.7;
  AVAR f = round(a);
  EXPECT_FLOAT_EQ(-2.0, f.val());
  
  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0, grad_f[0]);
}


TEST(AgradRev,tgamma) {
  AVAR a = 3.5;
  AVAR f = tgamma(a);
  EXPECT_FLOAT_EQ(boost::math::tgamma(3.5),f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(boost::math::digamma(3.5) * boost::math::tgamma(3.5),grad_f[0]);
}  

TEST(AgradRev,step) {
  AVAR a = 3.5;
  AVAR f = step(a);
  EXPECT_FLOAT_EQ(1.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  

TEST(AgradRev,step_2) {
  AVAR a = 0.0;
  AVAR f = step(a);
  EXPECT_FLOAT_EQ(1.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  

TEST(AgradRev,step_3) {
  AVAR a = -18765.3;
  AVAR f = step(a);
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
}  
 


TEST(AgradRev,square) {
  AVAR a = 7.0;
  AVEC x = createAVEC(a);
  AVAR f = square(a);
  EXPECT_FLOAT_EQ(49.0, f.val());

  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_EQ(1U,grad_f.size());
  EXPECT_FLOAT_EQ(14.0, grad_f[0]);
}


TEST(AgradRev,multiplyLogChainVV) {
  AVAR a = 19.7;
  AVAR b = 1299.1;
  AVAR f = 2.0 * multiply_log(a,b);

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);

  EXPECT_FLOAT_EQ(2.0 * log(b.val()), grad_f[0]);
  EXPECT_FLOAT_EQ(2.0 * a.val() / b.val(), grad_f[1]);
}
TEST(AgradRev,multiplyLogChainDV) {
  double a = 19.7;
  AVAR b = 1299.1;
  AVAR f = 2.0 * multiply_log(a,b);

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);

  EXPECT_FLOAT_EQ(2.0 * a / b.val(), grad_f[0]);
}
TEST(AgradRev,multiplyLogChainVD) {
  AVAR a = 19.7;
  double b = 1299.1;
  AVAR f = 2.0 * multiply_log(a,b);

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);

  EXPECT_FLOAT_EQ(2.0 * log(b), grad_f[0]);
}
TEST(AgradRev,multiply_log_var_var) {
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

TEST(AgradRev,multiply_log_var_double){
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
TEST(AgradRev,multiply_log_double_var){
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

TEST(AgradRev,log_sum_exp_2) {
  test_log_sum_exp_2(0.0,0.0);
  test_log_sum_exp_2(1.0,2.0);
  test_log_sum_exp_2(2.0,1.0);
  test_log_sum_exp_2(-2.0,15.0);
  test_log_sum_exp_2(2.0,-15.0);
}



TEST(AgradRev, log_sum_exp_vec_1) {
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


TEST(AgradRev, log_sum_exp_vec_2) {
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

TEST(AgradRev, log_sum_exp_vec_3) {
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

TEST(AgradRev,int_step) {
  using stan::math::int_step;

  AVAR a(5.0);
  AVAR b(0.0);
  AVAR c(-1.0);
  
  EXPECT_EQ(1U,int_step(a));
  EXPECT_EQ(0U,int_step(b));
  EXPECT_EQ(0U,int_step(c));
}



TEST(AgradRev,value_of) {
  using stan::agrad::var;
  using stan::math::value_of;

  var a = 5.0;
  EXPECT_FLOAT_EQ(5.0, value_of(a));
  EXPECT_FLOAT_EQ(5.0, value_of(5.0)); // make sure all work together
  EXPECT_FLOAT_EQ(5.0, value_of(5));
}



void test_log_inv_logit(const double x) {
  using stan::agrad::var;
  using stan::math::log_inv_logit;
  using std::log;
  using stan::math::inv_logit;

  
  // test gradient
  AVEC x1 = createAVEC(x);
  AVAR f1 = log_inv_logit(x1[0]);
  std::vector<double> grad_f1;
  f1.grad(x1,grad_f1);

  AVEC x2 = createAVEC(x);
  AVAR f2 = log(inv_logit(x2[0]));
  std::vector<double> grad_f2;
  f2.grad(x2,grad_f2);

  EXPECT_EQ(1U, grad_f1.size());
  EXPECT_EQ(1U, grad_f2.size());
  EXPECT_FLOAT_EQ(grad_f2[0], grad_f1[0]);

  // test value
  EXPECT_FLOAT_EQ(log(inv_logit(x)),
                  log_inv_logit(var(x)).val());

}
TEST(AgradRev, log_inv_logit) {
  test_log_inv_logit(-7.2);
  test_log_inv_logit(0.0);
  test_log_inv_logit(1.9);
}
void test_log1m_inv_logit(const double x) {
  using stan::agrad::var;
  using stan::math::log1m_inv_logit;
  using std::log;
  using stan::math::inv_logit;

  
  // test gradient
  AVEC x1 = createAVEC(x);
  AVAR f1 = log1m_inv_logit(x1[0]);
  std::vector<double> grad_f1;
  f1.grad(x1,grad_f1);

  AVEC x2 = createAVEC(x);
  AVAR f2 = log(1.0 - inv_logit(x2[0]));
  std::vector<double> grad_f2;
  f2.grad(x2,grad_f2);

  EXPECT_EQ(1U, grad_f1.size());
  EXPECT_EQ(1U, grad_f2.size());
  EXPECT_FLOAT_EQ(grad_f2[0], grad_f1[0]);

  // test value
  EXPECT_FLOAT_EQ(log(1.0 - inv_logit(x)),
                  log1m_inv_logit(var(x)).val());
}
TEST(AgradRev, log1m_inv_logit) {
  test_log1m_inv_logit(-7.2);
  test_log1m_inv_logit(0.0);
  test_log1m_inv_logit(1.9);
}


