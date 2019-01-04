#include <cmath>
#include <gtest/gtest.h>
#include <limits>
#include <stan/math/prim/mat.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <string>
#include <vector>

template <typename T_x, typename T_s, typename T_l>
std::string pull_msg(std::vector<T_x> x, T_s sigma, T_l l) {
  std::string message;
  try {
    stan::math::gp_exponential_cov(x, sigma, l);
  } catch (std::domain_error &e) {
    message = e.what();
  } catch (...) {
    message = "Threw the wrong exception";
  }
  return message;
}

template <typename T_x1, typename T_x2, typename T_s, typename T_l>
std::string pull_msg(std::vector<T_x1> x1, std::vector<T_x2> x2, T_s sigma,
                     T_l l) {
  std::string message;
  try {
    stan::math::gp_exponential_cov(x1, x2, sigma, l);
  } catch (std::domain_error &e) {
    message = e.what();
  } catch (...) {
    message = "Threw the wrong exception";
  }
  return message;
}

TEST(MathPrimMat, vec_double_gp_exponential_cov1) {
  double sigma = 0.2;
  double l = 5.0;

  std::vector<double> x(3);
  x[0] = -2;
  x[1] = -1;
  x[2] = -0.5;

  Eigen::MatrixXd cov;
  cov = stan::math::gp_exponential_cov(x, sigma, l);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      EXPECT_FLOAT_EQ(sigma * sigma *
                          std::exp(-stan::math::squared_distance(x[i], x[j]) /
                                   (2.0 * std::pow(l, 2))),
                      cov(i, j))
          << "index: (" << i << ", " << j << ")";
}

TEST(MathPrimMat, vec_double_double_gp_exponential_cov1) {
  double sigma = 0.2;
  double l = 5.0;

  std::vector<double> x1(3);
  x1[0] = -2;
  x1[1] = -1;
  x1[2] = -0.5;

  std::vector<double> x2(3);
  x2[0] = 3;
  x2[1] = -4;
  x2[2] = -0.7;

  Eigen::MatrixXd cov;
  cov = stan::math::gp_exponential_cov(x1, x2, sigma, l);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      EXPECT_FLOAT_EQ(sigma * sigma *
                          std::exp(-1.0 *
                                   stan::math::squared_distance(x1[i], x2[j]) /
                                   (2 * std::pow(l, 2))),
                      cov(i, j))
          << "index: (" << i << ", " << j << ")";
}

TEST(MathPrimMat, vec_eigen_gp_exponential_cov1) {
  double l = 0.2;
  double sigma = 0.3;

  std::vector<Eigen::Matrix<double, -1, 1>> x1(3);
  for (size_t i = 0; i < x1.size(); ++i) {
    x1[i].resize(3, 1);
    x1[i] << 1 * i, 2 * i, 3 * i;
  }

  Eigen::MatrixXd cov;
  cov = stan::math::gp_exponential_cov(x1, sigma, l);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(
          sigma * sigma *
              std::exp(-1.0 * stan::math::sqrt(
                                  stan::math::squared_distance(x1[i], x1[j]))
                                  /
                       l),
          cov(i, j))
          << "index: (" << i << ", " << j << ")";
    }
  }
}

TEST(MathPrimMat, vec_eigen_vec_eigen_gp_exponential_cov1) {
  double sigma = 0.3;
  double l = 2.3;

  std::vector<Eigen::Matrix<double, -1, 1>> x1(3);
  for (size_t i = 0; i < x1.size(); ++i) {
    x1[i].resize(3, 1);
    x1[i] << 1 * i, 2 * i, 3 * i;
  }

  std::vector<Eigen::Matrix<double, -1, 1>> x2(3);
  for (size_t i = 0; i < x2.size(); ++i) {
    x2[i].resize(3, 1);
    x2[i] << 2 * i, 3 * i, 4 * i;
  }

  Eigen::MatrixXd cov;
  cov = stan::math::gp_exponential_cov(x1, x2, sigma, l);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(
          sigma * sigma *
              std::exp(-1.0 * stan::math::sqrt(
                                  stan::math::squared_distance(x1[i], x2[j]))
                                  /
                       l),
          cov(i, j))
          << "index: (" << i << ", " << j << ")";
    }
  }

  cov = stan::math::gp_exponential_cov(x2, x1, sigma, l);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_FLOAT_EQ(
          sigma * sigma *
              std::exp(-1.0 * stan::math::sqrt(
                                  stan::math::squared_distance(x2[i], x1[j]))
                                  /
                       l),
          cov(i, j))
          << "index: (" << i << ", " << j << ")";
    }
  }
}

TEST(MathPrimMat, vec_eigen_vec_eigen_ard_gp_exponential_cov1) {
  double sigma = 0.3;
  double temp;

  std::vector<double> l(3);
  l[0] = 1;
  l[1] = 2;
  l[2] = 3;

  std::vector<Eigen::Matrix<double, -1, 1>> x1(3);
  for (size_t i = 0; i < x1.size(); ++i) {
    x1[i].resize(3, 1);
    x1[i] << 1 * i, 2 * i, 3 * i;
  }

  std::vector<Eigen::Matrix<double, -1, 1>> x2(3);
  for (size_t i = 0; i < x2.size(); ++i) {
    x2[i].resize(3, 1);
    x2[i] << 2 * i, 3 * i, 4 * i;
  }

  Eigen::MatrixXd cov;
  cov = stan::math::gp_exponential_cov(x1, x2, sigma, l);
  // for (int i = 0; i < 3; i++) {
  //   for (int j = 0; j < 3; j++) {
  //     temp = 0;
  //     for (int k = 0; k < 3; k++) {
  //       temp +=
  //           stan::math::sqrt(stan::math::squared_distance(x1[i], x2[j])) /
  //           l[k];
  //     }

  //     EXPECT_FLOAT_EQ(sigma * sigma * std::exp(-1.0 * temp), cov(i, j))
  //         << "index: (" << i << ", " << j << ")";
  //   }
  // }
  // cov = stan::math::gp_exponential_cov(x2, x1, sigma, l);
  // for (int i = 0; i < 3; i++) {
  //   for (int j = 0; j < 3; j++) {
  //     temp = 0;
  //     for (int k = 0; k < 3; k++) {
  //       temp +=
  //           stan::math::sqrt(stan::math::squared_distance(x2[i], x1[j])) /
  //           l[k];
  //     }

  //     EXPECT_FLOAT_EQ(sigma * sigma * std::exp(-1.0 * temp), cov(i, j))
  //         << "index: (" << i << ", " << j << ")";
  //   }
  // }
}

TEST(MathPrimMat, domain_err_training_sig_l) {
  double sigma = .2;
  double l = 7;
  double sigma_bad = -1.0;
  double l_bad = -1.0;

  std::vector<double> l_vec(2);
  l_vec[0] = 1;
  l_vec[1] = 2;
  l_vec[2] = 3;
  
  std::vector<double> l_vec_bad(2);
  l_vec_bad[0] = 1;
  l_vec_bad[1] = -1;
  l_vec_bad[2] = 2;
  
  std::vector<double> x(3);
  x[0] = -2;
  x[1] = -1;
  x[2] = -0.5;

  std::vector<Eigen::Matrix<double, -1, 1>> x_2(3);
  for (size_t i = 0; i < x_2.size(); ++i) {
    x_2[i].resize(3, 1);
    x_2[i] << 1, 2, 3;
  }

  std::string msg1, msg2, msg3, msg4;
  msg1 = pull_msg(x, sigma, l_bad);
  msg2 = pull_msg(x, sigma_bad, l_bad);
  msg3 = pull_msg(x, sigma_bad, l_bad);
  EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  msg1 = pull_msg(x, sigma, l_bad);
  msg3 = pull_msg(x, sigma_bad, l_bad);
  EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  msg1 = pull_msg(x_2, sigma, l_bad);
  msg2 = pull_msg(x_2, sigma_bad, l);
  msg3 = pull_msg(x_2, sigma_bad, l_bad);
  EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  // msg1 = pull_msg(x_2, sigma, l_bad);
  // msg2 = pull_msg(x_2, sigma_bad, l_vec);
  // msg3 = pull_msg(x_2, sigma_bad, l_bad);
  // EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  // EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  // EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  // msg1 = pull_msg(x_2, sigma, l_vec_bad);
  // msg2 = pull_msg(x_2, sigma_bad, l_vec_bad);
  // msg3 = pull_msg(x_2, sigma_bad, l_vec);
  // EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  // EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  // EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  // msg1 = pull_msg(x_2, x_2, sigma, l_bad);
  // msg2 = pull_msg(x_2, x_2, sigma_bad, l);
  // msg3 = pull_msg(x_2, x_2, sigma_bad, l_bad);
  // EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  // EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  // EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  // msg1 = pull_msg(x_2, x_2, sigma, l_bad);
  // msg2 = pull_msg(x_2, x_2, sigma_bad, l_vec);
  // msg3 = pull_msg(x_2, x_2, sigma_bad, l_bad);
  // EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  // EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  // EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  // msg1 = pull_msg(x_2, x_2, sigma, l_vec_bad);
  // msg2 = pull_msg(x_2, x_2, sigma_bad, l_vec_bad);
  // msg3 = pull_msg(x_2, x_2, sigma_bad, l_vec);
  // EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  // EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  // EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  // msg1 = pull_msg(x_2, x_2, sigma, l_vec_bad);
  // msg2 = pull_msg(x_2, x_2, sigma_bad, l_vec_bad);
  // msg3 = pull_msg(x_2, x_2, sigma_bad, l_vec);
  // EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  // EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  // EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

  // msg1 = pull_msg(x_2, x_2, sigma, l_vec_bad);
  // msg2 = pull_msg(x_2, x_2, sigma_bad, l_vec_bad);
  // msg3 = pull_msg(x_2, x_2, sigma_bad, l_vec);
  // EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
  // EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
  // EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;
}

// // TEST(MathPrimMat, nan_error_training_sig_l_gamma) {
// //   double sigma = 0.2;
// //   double l = 5;

// //   std::vector<double> x(3);
// //   x[0] = -2;
// //   x[1] = -1;
// //   x[2] = -0.5;

// //   std::vector<Eigen::Matrix<double, -1, 1>> x_2(3);
// //   for (size_t i = 0; i < x_2.size(); ++i) {
// //     x_2[i].resize(3, 1);
// //     x_2[i] << 1, 2, 3;
// //   }

// //   std::vector<Eigen::Matrix<double, 1, -1>> x_3(3);
// //   for (size_t i = 0; i < x_3.size(); ++i) {
// //     x_3[i].resize(1, 3);
// //     x_3[i] << 1, 2, 3;
// //   }

// //   std::vector<double> l_vec(2);
// //   l_vec[0] = 1;
// //   l_vec[1] = 2;

// //   std::vector<double> l_vec_bad(2);
// //   l_vec_bad[0] = 1;
// //   l_vec_bad[1] = -1;

// //   std::vector<double> x_bad(x);
// //   x_bad[1] = std::numeric_limits<double>::quiet_NaN();

// //   std::vector<Eigen::Matrix<double, -1, 1>> x_bad_2(x_2);
// //   x_bad_2[1](1) = std::numeric_limits<double>::quiet_NaN();

// //   std::vector<Eigen::Matrix<double, 1, -1>> x_bad_3(x_3);
// //   x_bad_3[1](1) = std::numeric_limits<double>::quiet_NaN();

// //   double sigma_bad = std::numeric_limits<double>::quiet_NaN();
// //   double l_bad = std::numeric_limits<double>::quiet_NaN();

// //   std::string msg1, msg2, msg3, msg4;
// //   msg1 = pull_msg(x, sigma, l_bad);
// //   msg2 = pull_msg(x, sigma_bad, l);
// //   msg3 = pull_msg(x, sigma_bad, l_bad);
// //   EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
// //   EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
// //   EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x, sigma, l_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x, sigma_bad, l),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x, sigma_bad, l_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, l, sigma),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, sigma_bad, l),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, sigma_bad, l_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, sigma, l_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_2, sigma, l_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_2, sigma_bad, l),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_2, sigma_bad, l_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_2, sigma, l_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_2, sigma_bad, l),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_2, sigma, l),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_2, sigma_bad, l_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_3, sigma, l_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_3, sigma_bad, l),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_3, sigma_bad, l_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_3, sigma, l_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_3, sigma_bad, l),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_3, sigma_bad, l_bad),
// //                std::domain_error);

// //   EXPECT_TRUE(std::string::npos != msg1.find(" length-scale")) << msg1;
// //   EXPECT_TRUE(std::string::npos != msg2.find(" marginal variance")) << msg2;
// //   EXPECT_TRUE(std::string::npos != msg3.find(" marginal variance")) << msg3;

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x, sigma, l_vec_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x, sigma_bad, l_vec),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x, sigma_bad, l_vec_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, sigma, l_vec),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, sigma_bad, l_vec),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, sigma_bad, l_vec_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, sigma, l_vec_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad, sigma_bad, l_vec_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_2, sigma, l_vec_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_2, sigma_bad, l_vec),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_2, sigma_bad, l_vec_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_2, sigma, l_vec_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_2, sigma_bad, l_vec),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_2, sigma_bad, l_vec_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_3, sigma, l_vec_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_3, sigma_bad, l_vec),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_3, sigma_bad, l_vec_bad),
// //                std::domain_error);

// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_3, sigma, l_vec_bad),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_3, sigma_bad, l_vec),
// //                std::domain_error);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_bad_3, sigma_bad, l_vec_bad),
// //                std::domain_error);
// // }

// // TEST(MathPrimMat, dim_mismatch_vec_eigen_rvec_gp_exponential_cov2) {
// //   double sigma = 0.2;
// //   double l = 5;

// //   std::vector<Eigen::Matrix<double, 1, -1>> x_vec_1(3);
// //   for (size_t i = 0; i < x_vec_1.size(); ++i) {
// //     x_vec_1[i].resize(1, 3);
// //     x_vec_1[i] << 1, 2, 3;
// //   }

// //   std::vector<Eigen::Matrix<double, 1, -1>> x_vec_2(4);
// //   for (size_t i = 0; i < x_vec_2.size(); ++i) {
// //     x_vec_2[i].resize(1, 4);
// //     x_vec_2[i] << 4, 1, 3, 1;
// //   }
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_vec_1, x_vec_2, sigma, l),
// //                std::invalid_argument);
// // }

// // TEST(MathPrimMat, dim_mismatch_vec_eigen_mixed_gp_exponential_cov) {
// //   double sigma = 0.2;
// //   double l = 5;

// //   std::vector<Eigen::Matrix<double, 1, -1>> x_rvec_1(3);
// //   for (size_t i = 0; i < x_rvec_1.size(); ++i) {
// //     x_rvec_1[i].resize(1, 3);
// //     x_rvec_1[i] << 1, 2, 3;
// //   }

// //   std::vector<Eigen::Matrix<double, -1, 1>> x_vec_1(4);
// //   for (size_t i = 0; i < x_vec_1.size(); ++i) {
// //     x_vec_1[i].resize(4, 1);
// //     x_vec_1[i] << 4, 1, 3, 1;
// //   }

// //   std::vector<Eigen::Matrix<double, -1, 1>> x_vec_2(3);
// //   for (size_t i = 0; i < x_vec_2.size(); ++i) {
// //     x_vec_2[i].resize(3, 1);
// //     x_vec_2[i] << 1, 2, 3;
// //   }

// //   std::vector<Eigen::Matrix<double, 1, -1>> x_rvec_2(4);
// //   for (size_t i = 0; i < x_rvec_2.size(); ++i) {
// //     x_rvec_2[i].resize(1, 4);
// //     x_rvec_2[i] << 1, 2, 3, 4;
// //   }
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_rvec_1, x_vec_1, sigma, l),
// //                std::invalid_argument);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_vec_1, x_rvec_1, sigma, l),
// //                std::invalid_argument);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_rvec_2, x_vec_2, sigma, l),
// //                std::invalid_argument);
// //   EXPECT_THROW(stan::math::gp_exponential_cov(x_vec_2, x_rvec_2, sigma, l),
// //                std::invalid_argument);
// // }
