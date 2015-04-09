#include <test/test-models/good/variational/univariate_with_constraint.hpp>
#include <stan/variational/advi.hpp>
#include <gtest/gtest.h>
#include <test/unit/util.hpp>
#include <vector>
#include <string>
#include <boost/random/additive_combine.hpp> // L'Ecuyer RNG

typedef boost::ecuyer1988 rng_t;
typedef univariate_with_constraint_model_namespace::univariate_with_constraint_model Model;

TEST(advi_test, univar_with_constraint_fullrank) {

  // Create mock data_var_context
  static const std::string DATA = "";
  std::stringstream data_stream(DATA);
  stan::io::dump dummy_context(data_stream);

  // Instantiate model
  Model my_model(dummy_context);

  // RNG
  rng_t base_rng(0);

  // Dummy input
  Eigen::VectorXd cont_params = Eigen::VectorXd::Zero(1);
  cont_params(0) = -0.75;

  // ADVI
  stan::variational::advi<Model, rng_t> test_advi(my_model,
                                                  cont_params,
                                                  0,
                                                  10,
                                                  5e5, // absurdly high!
                                                  0.1,
                                                  base_rng,
                                                  100,
                                                  &std::cout,
                                                  &std::cout,
                                                  &std::cout);

  // Create some arbitrary variational q() family to calculate the ELBO over
  Eigen::VectorXd mu     = Eigen::VectorXd::Constant(my_model.num_params_r(),
                                                     log(1.88));
  Eigen::MatrixXd L_chol = Eigen::MatrixXd::Identity(my_model.num_params_r(),
                                                     my_model.num_params_r());
  stan::variational::advi_params_fullrank muL =
    stan::variational::advi_params_fullrank(mu, L_chol);

  double elbo = 0.0;
  elbo = test_advi.calc_ELBO(muL);

  // Can calculate ELBO analytically + moment generating function of Gaussians
  double one_over_sigma_j_sq = 1.0 + 2*1.0;
  double sigma_j_sq = 1.0/one_over_sigma_j_sq;

  double mu_j = (1.5/1.0 + 1.6/1.0 + 1.4/1.0) * sigma_j_sq;

  double S_j = 1.0/(2.0*stan::math::pi())
               * sqrt( sigma_j_sq / (1.0) )
               * exp( -0.5 * ( pow(1.5,2)
                               + pow(1.4,2)
                               + pow(1.6,2)
                               - pow(mu_j,2)/sigma_j_sq ) );

  double elbo_true = 0.0;

  elbo_true += log(S_j);
  elbo_true += log(1.0/( sqrt( sigma_j_sq * 2.0 * stan::math::pi() ) ));
  elbo_true += -0.5*one_over_sigma_j_sq * ( exp(2.0*log(1.88)) * exp(2.0*1.0) );
  elbo_true += -0.5*one_over_sigma_j_sq * ( -2.0*mu_j*exp(log(1.88))*exp(0.5*1.0) );
  elbo_true += -0.5*one_over_sigma_j_sq * ( pow(mu_j, 2.0) );
  elbo_true += log(1.88);
  elbo_true += 0.5 * (1 + log(2.0*stan::math::pi()));

  double const EPSILON = 1.0;
  EXPECT_NEAR(elbo_true, elbo, EPSILON);

  Eigen::VectorXd mu_grad = Eigen::VectorXd::Zero(3);
  Eigen::MatrixXd L_grad  = Eigen::MatrixXd::Identity(my_model.num_params_r(),
                                                     my_model.num_params_r());

  std::string error = "stan::variational::advi.calc_combined_grad: "
                      "Dimension of mu grad vector (3) and Dimension of mean "
                      "vector in variational q (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(muL, mu_grad, L_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(0);
  error = "stan::variational::advi.calc_combined_grad: "
          "Dimension of mu grad vector (0) and Dimension of mean "
          "vector in variational q (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(muL, mu_grad, L_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(my_model.num_params_r());
  L_grad  = Eigen::MatrixXd::Identity(3,3);

  error = "stan::variational::advi.calc_combined_grad: "
          "Dimension of scale matrix (3) and Dimension of mean "
          "vector in variational q (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(muL, mu_grad, L_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(my_model.num_params_r());
  L_grad  = Eigen::MatrixXd::Identity(0,0);

  error = "stan::variational::advi.calc_combined_grad: "
          "Dimension of scale matrix (0) and Dimension of mean "
          "vector in variational q (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(muL, mu_grad, L_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(my_model.num_params_r());
  L_grad  = Eigen::MatrixXd::Identity(1,4);

  error = "stan::variational::advi.calc_combined_grad: "
          "Expecting a square matrix; rows of Scale matrix (1) and "
          "columns of Scale matrix (4) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(muL, mu_grad, L_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(3);
  L_grad  = Eigen::MatrixXd::Identity(3,3);
  stan::variational::advi_params_fullrank muL_wrongdim =
    stan::variational::advi_params_fullrank(mu_grad, L_grad);

  error = "stan::variational::advi.calc_combined_grad: Dimension of muL (3) "
          "and Dimension of variables in model (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(muL_wrongdim, mu_grad, L_grad),
                   std::invalid_argument, error);

}

TEST(advi_test, univar_with_constraint_meanfield) {

  // Create mock data_var_context
  static const std::string DATA = "";
  std::stringstream data_stream(DATA);
  stan::io::dump dummy_context(data_stream);

  // Instantiate model
  Model my_model(dummy_context);

  // RNG
  rng_t base_rng(0);

  // Dummy input
  Eigen::VectorXd cont_params = Eigen::VectorXd::Zero(1);
  cont_params(0) = -0.75;

  // ADVI
  stan::variational::advi<Model, rng_t> test_advi(my_model,
                                                  cont_params,
                                                  0,
                                                  10,
                                                  5e5, // absurdly high!
                                                  0.1,
                                                  base_rng,
                                                  100,
                                                  &std::cout,
                                                  &std::cout,
                                                  &std::cout);

  // Create some arbitrary variational q() family to calculate the ELBO over
  Eigen::VectorXd mu  = Eigen::VectorXd::Constant(my_model.num_params_r(),
                                                     log(1.88));
  Eigen::MatrixXd sigma_tilde  = Eigen::VectorXd::Constant(
                                          my_model.num_params_r(),
                                          0.0); // initializing sigma_tilde = 0
                                                // means sigma = 1
  stan::variational::advi_params_meanfield musigmatilde =
    stan::variational::advi_params_meanfield(mu,sigma_tilde);

  double elbo = 0.0;
  elbo = test_advi.calc_ELBO(musigmatilde);

  // Can calculate ELBO analytically + moment generating function of Gaussians
  double one_over_sigma_j_sq = 1.0 + 2*1.0;
  double sigma_j_sq = 1.0/one_over_sigma_j_sq;

  double mu_j = (1.5/1.0 + 1.6/1.0 + 1.4/1.0) * sigma_j_sq;

  double S_j = 1.0/(2.0*stan::math::pi())
               * sqrt( sigma_j_sq / (1.0) )
               * exp( -0.5 * ( pow(1.5,2)
                               + pow(1.4,2)
                               + pow(1.6,2)
                               - pow(mu_j,2)/sigma_j_sq ) );

  double elbo_true = 0.0;

  elbo_true += log(S_j);
  elbo_true += log(1.0/( sqrt( sigma_j_sq * 2.0 * stan::math::pi() ) ));
  elbo_true += -0.5*one_over_sigma_j_sq * ( exp(2.0*log(1.88)) * exp(2.0*1.0) );
  elbo_true += -0.5*one_over_sigma_j_sq * ( -2.0*mu_j*exp(log(1.88))*exp(0.5*1.0) );
  elbo_true += -0.5*one_over_sigma_j_sq * ( pow(mu_j, 2.0) );
  elbo_true += log(1.88);
  elbo_true += 0.5 * (1 + log(2.0*stan::math::pi()));


  double const EPSILON = 1.0;
  EXPECT_NEAR(elbo_true, elbo, EPSILON);

  Eigen::VectorXd mu_grad = Eigen::VectorXd::Zero(3);
  Eigen::VectorXd st_grad = Eigen::VectorXd::Zero(my_model.num_params_r());

  std::string error = "stan::variational::advi.calc_combined_grad: "
                      "Dimension of mu grad vector (3) and Dimension of mean "
                      "vector in variational q (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(musigmatilde, mu_grad, st_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(0);
  error = "stan::variational::advi.calc_combined_grad: "
          "Dimension of mu grad vector (0) and Dimension of mean "
          "vector in variational q (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(musigmatilde, mu_grad, st_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(my_model.num_params_r());
  st_grad  = Eigen::VectorXd::Zero(3);

  error = "stan::variational::advi.calc_combined_grad: "
          "Dimension of sigma_tilde grad vector (3) and Dimension of "
          "mean vector in variational q (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(musigmatilde, mu_grad, st_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(my_model.num_params_r());
  st_grad  = Eigen::VectorXd::Zero(0);

  error = "stan::variational::advi.calc_combined_grad: "
          "Dimension of sigma_tilde grad vector (0) and Dimension of "
          "mean vector in variational q (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(musigmatilde, mu_grad, st_grad),
                   std::invalid_argument, error);

  mu_grad = Eigen::VectorXd::Zero(3);
  st_grad  = Eigen::VectorXd::Zero(3);
  stan::variational::advi_params_meanfield mst_wrongdim =
    stan::variational::advi_params_meanfield(mu_grad, st_grad);

  error = "stan::variational::advi.calc_combined_grad: "
          "Dimension of musigmatilde (3) and Dimension of "
          "variables in model (1) must match in size";
  EXPECT_THROW_MSG(test_advi.calc_combined_grad(mst_wrongdim, mu_grad, st_grad),
                   std::invalid_argument, error);

}


