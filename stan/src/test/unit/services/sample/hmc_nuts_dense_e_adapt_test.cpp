#include <stan/services/sample/hmc_nuts_dense_e_adapt.hpp>
#include <gtest/gtest.h>
#include <stan/io/empty_var_context.hpp>
#include <test/test-models/good/optimization/rosenbrock.hpp>
#include <test/unit/services/instrumented_callbacks.hpp>
#include <iostream>

class ServicesSampleHmcNutsDenseEAdapt : public testing::Test {
public:
  ServicesSampleHmcNutsDenseEAdapt()
    : model(context, &model_log) {}

  std::stringstream model_log;
  stan::test::unit::instrumented_writer message, init, error;
  stan::test::unit::instrumented_writer parameter, diagnostic;
  stan::io::empty_var_context context;
  stan_model model;
};

TEST_F(ServicesSampleHmcNutsDenseEAdapt, call_count) {
  unsigned int random_seed = 0;
  unsigned int chain = 1;
  double init_radius = 0;
  int num_warmup = 200;
  int num_samples = 400;
  int num_thin = 5;
  bool save_warmup = true;
  int refresh = 0;
  double stepsize = 0.1;
  double stepsize_jitter = 0;
  int max_depth = 8;
  double delta = .1;
  double gamma = .1;
  double kappa = .1;
  double t0 = .1;
  unsigned int init_buffer = 50;
  unsigned int term_buffer = 50;
  unsigned int window = 100;
  stan::test::unit::instrumented_interrupt interrupt;
  EXPECT_EQ(interrupt.call_count(), 0);
      
  int return_code = stan::services::sample::hmc_nuts_dense_e_adapt(
      model, context, random_seed, chain, init_radius,
      num_warmup, num_samples, num_thin, save_warmup, refresh,
      stepsize, stepsize_jitter, max_depth, delta, gamma, kappa, t0,
      init_buffer, term_buffer, window,
      interrupt, message, error, init,
      parameter, diagnostic);
 
  EXPECT_EQ(0, return_code);

  int num_output_lines = (num_warmup+num_samples)/num_thin;
  EXPECT_EQ(num_warmup+num_samples, interrupt.call_count());
  EXPECT_EQ(1, parameter.call_count("vector_string"));
  EXPECT_EQ(num_output_lines, parameter.call_count("vector_double"));
  EXPECT_EQ(1, diagnostic.call_count("vector_string"));
  EXPECT_EQ(num_output_lines, diagnostic.call_count("vector_double"));
}

TEST_F(ServicesSampleHmcNutsDenseEAdapt, parameter_checks) {
  unsigned int random_seed = 0;
  unsigned int chain = 1;
  double init_radius = 0;
  int num_warmup = 200;
  int num_samples = 400;
  int num_thin = 5;
  bool save_warmup = true;
  int refresh = 0;
  double stepsize = 0.1;
  double stepsize_jitter = 0;
  int max_depth = 8;
  double delta = .1;
  double gamma = .1;
  double kappa = .1;
  double t0 = .1;
  unsigned int init_buffer = 50;
  unsigned int term_buffer = 50;
  unsigned int window = 100;
  stan::test::unit::instrumented_interrupt interrupt;
  EXPECT_EQ(interrupt.call_count(), 0);
      
  int return_code = stan::services::sample::hmc_nuts_dense_e_adapt(
      model, context, random_seed, chain, init_radius,
      num_warmup, num_samples, num_thin, save_warmup, refresh,
      stepsize, stepsize_jitter, max_depth, delta, gamma, kappa, t0,
      init_buffer, term_buffer, window,
      interrupt, message, error, init,
      parameter, diagnostic);
  EXPECT_EQ(return_code, 0);

  std::vector<std::vector<std::string> > parameter_names;
  parameter_names = parameter.vector_string_values();
  std::vector<std::vector<double> > parameter_values;
  parameter_values = parameter.vector_double_values();
  std::vector<std::vector<std::string> > diagnostic_names;
  diagnostic_names = diagnostic.vector_string_values();
  std::vector<std::vector<double> > diagnostic_values;
  diagnostic_values = diagnostic.vector_double_values();

  // Expectations of hmc nuts parameter names for rosenbrock model
  ASSERT_EQ(9, parameter_names[0].size());
  EXPECT_EQ("lp__", parameter_names[0][0]);
  EXPECT_EQ("accept_stat__", parameter_names[0][1]);
  EXPECT_EQ("stepsize__", parameter_names[0][2]);
  EXPECT_EQ("treedepth__", parameter_names[0][3]);
  EXPECT_EQ("n_leapfrog__", parameter_names[0][4]);
  EXPECT_EQ("divergent__", parameter_names[0][5]);
  EXPECT_EQ("energy__", parameter_names[0][6]);
  EXPECT_EQ("x", parameter_names[0][7]);
  EXPECT_EQ("y", parameter_names[0][8]);

  // Expect one name per parameter value.
  EXPECT_EQ(parameter_names[0].size(), parameter_values[0].size());
  EXPECT_EQ(diagnostic_names[0].size(), diagnostic_values[0].size());

  EXPECT_EQ((num_warmup+num_samples)/num_thin, parameter_values.size());
 
  // Expect one call to set parameter names, and one set of output per
  // iteration.
  EXPECT_EQ("lp__", diagnostic_names[0][0]);
  EXPECT_EQ("accept_stat__", diagnostic_names[0][1]);
}

TEST_F(ServicesSampleHmcNutsDenseEAdapt, return_checks) {
  unsigned int random_seed = 0;
  unsigned int chain = 1;
  double init_radius = 0;
  int num_warmup = 200;
  int num_samples = 400;
  int num_thin = 5;
  bool save_warmup = true;
  int refresh = 0;
  double stepsize = 0.1;
  double stepsize_jitter = 0;
  int max_depth = 8;
  double delta = .1;
  double gamma = .1;
  double kappa = .1;
  double t0 = .1;
  unsigned int init_buffer = 50;
  unsigned int term_buffer = 50;
  unsigned int window = 100;
  stan::test::unit::instrumented_interrupt interrupt;
  EXPECT_EQ(interrupt.call_count(), 0);
      
  int return_code = stan::services::sample::hmc_nuts_dense_e_adapt(
      model, context, random_seed, chain, init_radius,
      num_warmup, num_samples, num_thin, save_warmup, refresh,
      stepsize, stepsize_jitter, max_depth, delta, gamma, kappa, t0,
      init_buffer, term_buffer, window,
      interrupt, message, error, init,
      parameter, diagnostic);
  EXPECT_EQ(return_code, 0);

  std::vector<std::string> init_values;
  init_values = init.string_values();
  std::vector<std::string> error_values;
  error_values = error.string_values();

  EXPECT_EQ(0, init_values.size());
  EXPECT_EQ(0, error_values.size());
}

