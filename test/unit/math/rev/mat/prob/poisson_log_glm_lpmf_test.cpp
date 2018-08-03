#include <stan/math/rev/mat.hpp>
#include <gtest/gtest.h>
#include <stan/math/prim/scal/fun/value_of.hpp>

using Eigen::Dynamic;
using Eigen::Matrix;
using stan::math::var;

//  We check that the values of the new regression match those of one built
//  from existing primitives.
TEST(ProbDistributionsPoissonLogGLM, glm_matches_poisson_log_doubles) {
  Matrix<int, Dynamic, 1> n(3, 1);
  n << 15, 3, 5;
  Matrix<double, Dynamic, Dynamic> x(3, 2);
  x << -12, 46, -42, 24, 25, 27;
  Matrix<double, Dynamic, 1> beta(2, 1);
  beta << 0.3, 2;
  double alpha = 0.3;
  Matrix<double, Dynamic, 1> alphavec = alpha * Matrix<double, 3, 1>::Ones();
  Matrix<double, Dynamic, 1> theta(3, 1);
  theta = x * beta + alphavec;
  EXPECT_FLOAT_EQ((stan::math::poisson_log_lpmf(n, theta)),
                  (stan::math::poisson_log_glm_lpmf(n, x, beta, alpha)));
  EXPECT_FLOAT_EQ((stan::math::poisson_log_lpmf<true>(n, theta)),
                  (stan::math::poisson_log_glm_lpmf<true>(n, x, beta, alpha)));
}
//  We check that the values of the new regression match those of one built
//  from existing primitives.
TEST(ProbDistributionsPoissonLogGLM, glm_matches_poisson_log_doubles_rand) {
  for (size_t ii = 0; ii < 20000; ii++) {
    Matrix<int, Dynamic, 1> n(3, 1);
    for (size_t i = 0; i < 3; i++) {
      n[i] = Matrix<uint, 1, 1>::Random(1, 1)[0] % 200;
    }
    Matrix<double, Dynamic, Dynamic> x
        = Matrix<double, Dynamic, Dynamic>::Random(3, 2);
    Matrix<double, Dynamic, 1> beta
        = Matrix<double, Dynamic, Dynamic>::Random(2, 1);
    Matrix<double, 1, 1> alphamat = Matrix<double, 1, 1>::Random(1, 1);
    double alpha = alphamat[0];
    Matrix<double, Dynamic, 1> alphavec = alpha * Matrix<double, 3, 1>::Ones();
    Matrix<double, Dynamic, 1> theta(3, 1);
    theta = x * beta + alphavec;
    EXPECT_FLOAT_EQ((stan::math::poisson_log_lpmf(n, theta)),
                    (stan::math::poisson_log_glm_lpmf(n, x, beta, alpha)));
    EXPECT_FLOAT_EQ(
        (stan::math::poisson_log_lpmf<true>(n, theta)),
        (stan::math::poisson_log_glm_lpmf<true>(n, x, beta, alpha)));
  }
}
//  We check that the gradients of the new regression match those of one built
//  from existing primitives.
TEST(ProbDistributionsPoissonLogGLM, glm_matches_poisson_log_vars) {
  Matrix<int, Dynamic, 1> n(3, 1);
  n << 14, 2, 5;
  Matrix<var, Dynamic, Dynamic> x(3, 2);
  x << -12, 46, -42, 24, 25, 27;
  Matrix<var, Dynamic, 1> beta(2, 1);
  beta << 0.3, 2;
  var alpha = 0.3;
  Matrix<var, Dynamic, 1> alphavec = alpha * Matrix<double, 3, 1>::Ones();
  Matrix<var, Dynamic, 1> theta(3, 1);
  theta = x * beta + alphavec;
  var lp = stan::math::poisson_log_lpmf(n, theta);
  lp.grad();

  double lp_val = lp.val();
  double alpha_adj = alpha.adj();
  Matrix<double, Dynamic, Dynamic> x_adj(3, 2);
  Matrix<double, Dynamic, 1> beta_adj(2, 1);
  for (size_t i = 0; i < 2; i++) {
    beta_adj[i] = beta[i].adj();
    for (size_t j = 0; j < 3; j++) {
      x_adj(j, i) = x(j, i).adj();
    }
  }

  stan::math::recover_memory();

  Matrix<int, Dynamic, 1> n2(3, 1);
  n2 << 14, 2, 5;
  Matrix<var, Dynamic, Dynamic> x2(3, 2);
  x2 << -12, 46, -42, 24, 25, 27;
  Matrix<var, Dynamic, 1> beta2(2, 1);
  beta2 << 0.3, 2;
  var alpha2 = 0.3;
  var lp2 = stan::math::poisson_log_glm_lpmf(n2, x2, beta2, alpha2);
  lp2.grad();
  EXPECT_FLOAT_EQ(lp_val, lp2.val());
  EXPECT_FLOAT_EQ(alpha_adj, alpha2.adj());
  for (size_t i = 0; i < 2; i++) {
    EXPECT_FLOAT_EQ(beta_adj[i], beta2[i].adj());
    for (size_t j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(x_adj(j, i), x2(j, i).adj());
    }
  }
}
//  We check that the gradients of the new regression match those of one built
//  from existing primitives.
TEST(ProbDistributionsPoissonLogGLM, glm_matches_poisson_log_vars_rand) {
  for (size_t ii = 0; ii < 200; ii++) {
    Matrix<int, Dynamic, 1> n(3, 1);
    for (size_t i = 0; i < 3; i++) {
      n[i] = Matrix<uint, 1, 1>::Random(1, 1)[0] % 200;
    }
    Matrix<double, Dynamic, Dynamic> xreal
        = Matrix<double, Dynamic, Dynamic>::Random(3, 2);
    Matrix<double, Dynamic, 1> betareal
        = Matrix<double, Dynamic, Dynamic>::Random(2, 1);
    Matrix<double, 1, 1> alphareal = Matrix<double, 1, 1>::Random(1, 1);
    Matrix<var, Dynamic, 1> beta = betareal;
    Matrix<var, Dynamic, 1> theta(3, 1);
    Matrix<var, Dynamic, Dynamic> x = xreal;
    var alpha = alphareal[0];
    Matrix<var, Dynamic, 1> alphavec = Matrix<double, 3, 1>::Ones() * alpha;
    theta = (x * beta) + alphavec;
    var lp = stan::math::poisson_log_lpmf(n, theta);
    lp.grad();

    double lp_val = lp.val();
    double alpha_adj = alpha.adj();
    Matrix<double, Dynamic, Dynamic> x_adj(3, 2);
    Matrix<double, Dynamic, 1> beta_adj(2, 1);
    for (size_t i = 0; i < 2; i++) {
      beta_adj[i] = beta[i].adj();
      for (size_t j = 0; j < 3; j++) {
        x_adj(j, i) = x(j, i).adj();
      }
    }

    stan::math::recover_memory();

    Matrix<var, Dynamic, 1> beta2 = betareal;
    Matrix<var, Dynamic, Dynamic> x2 = xreal;
    var alpha2 = alphareal[0];
    var lp2 = stan::math::poisson_log_glm_lpmf(n, x2, beta2, alpha2);
    lp2.grad();
    EXPECT_FLOAT_EQ(lp_val, lp2.val());
    EXPECT_FLOAT_EQ(alpha_adj, alpha2.adj());
    for (size_t i = 0; i < 2; i++) {
      EXPECT_FLOAT_EQ(beta_adj[i], beta2[i].adj());
      for (size_t j = 0; j < 3; j++) {
        EXPECT_FLOAT_EQ(x_adj(j, i), x2(j, i).adj());
      }
    }
  }
}
//  Here, we compare the speed of the new regression to that of one built from
//  existing primitives.
/*
#include <chrono>
typedef std::chrono::high_resolution_clock::time_point TimeVar;
#define duration(a) \
  std::chrono::duration_cast<std::chrono::microseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()
TEST(ProbDistributionsPoissonLogGLM, glm_matches_poisson_log_speed) {
  const int R = 3000;
  const int C = 1000;
  Matrix<int,Dynamic,1> n(R, 1);
  for (size_t i = 0; i < R; i++) {
    n[i] = Matrix<uint, 1, 1>::Random(1, 1)[0]%200;
  }
  int T1 = 0;
  int T2 = 0;
  for (size_t testnumber = 0; testnumber < 30; testnumber++){
    Matrix<double, Dynamic, Dynamic> xreal = Matrix<double, Dynamic,
Dynamic>::Random(R, C); Matrix<double, Dynamic, 1> betareal = Matrix<double,
Dynamic, Dynamic>::Random(C, 1); Matrix<double, 1, 1> alphareal = Matrix<double,
1, 1>::Random(1, 1); Matrix<double, Dynamic, 1> alpharealvec = Matrix<double, R,
1>::Ones() * alphareal;
    Matrix<var, Dynamic, 1> beta = betareal;
    Matrix<var, Dynamic, 1> theta(R, 1);
    TimeVar t1 = timeNow();
    theta = (xreal * beta) + alpharealvec;
    var lp = stan::math::poisson_log_lpmf(n, theta);
    lp.grad();
    TimeVar t2 = timeNow();
    stan::math::recover_memory();
    Matrix<var, Dynamic, 1> beta2 = betareal;
    TimeVar t3 = timeNow();
    var lp2 = stan::math::poisson_log_glm_lpmf(n, xreal, beta2, alphareal[0]);
    lp2.grad();
    TimeVar t4 = timeNow();
    stan::math::recover_memory();
    T1 += duration(t2 - t1);
    T2 += duration(t4 - t3);
  }
  std::cout << "Existing Primitives:" << std::endl << T1 << std::endl  << "New
Primitives:" << std::endl << T2 << std::endl;
}*/
