#include <stan/services/optimize/bfgs.hpp>
#include <gtest/gtest.h>
#include <stan/io/empty_var_context.hpp>
#include <test/test-models/good/optimization/rosenbrock.hpp>
#include <stan/interface_callbacks/writer/stream_writer.hpp>

struct mock_callback {
  int n;
  mock_callback() : n(0) { }
  
  void operator()() {
    n++;
  }
};


class values
  : public stan::interface_callbacks::writer::stream_writer {
public:
  std::vector<std::string> names_;
  std::vector<std::vector<double> > states_;

  values(std::ostream& stream)
    : stan::interface_callbacks::writer::stream_writer(stream) {
  }
  
  /**
   * Writes a set of names.
   *
   * @param[in] names Names in a std::vector
   */
  void operator()(const std::vector<std::string>& names) {
    names_ = names;
  }

  /**
   * Writes a set of values.
   *
   * @param[in] state Values in a std::vector
   */
  void operator()(const std::vector<double>& state) {
    states_.push_back(state);
  }

};


class ServicesOptimizeBfgs : public testing::Test {
public:
  ServicesOptimizeBfgs()
    : message(message_ss),
      parameter(parameter_ss),
      model(context, &model_ss) {}

  std::stringstream message_ss, parameter_ss, model_ss;
  stan::interface_callbacks::writer::stream_writer message;//, parameter;
  values parameter;
  stan::io::empty_var_context context;
  stan_model model;
};


TEST_F(ServicesOptimizeBfgs, rosenbrock) {
  unsigned int seed = 0;
  unsigned int chain = 1;
  double init_radius = 0;

  bool save_iterations = true;
  int refresh = 0;
  mock_callback callback;
  
  int return_code = stan::services::optimize::bfgs(model, context,
                                                   seed, chain, init_radius,
                                                   0.001,
                                                   1e-12,
                                                   10000,
                                                   1e-8,
                                                   10000000,
                                                   1e-8,
                                                   2000,
                                                   save_iterations, refresh,
                                                   callback,
                                                   message, 
                                                   parameter);

  EXPECT_EQ("Initial log joint probability = -1\nOptimization terminated normally: \n  Convergence detected: relative gradient magnitude is below tolerance\n", message_ss.str());

  ASSERT_EQ(3, parameter.names_.size());
  EXPECT_EQ("lp__", parameter.names_[0]);
  EXPECT_EQ("x", parameter.names_[1]);
  EXPECT_EQ("y", parameter.names_[2]);

  EXPECT_EQ(20, parameter.states_.size());
  EXPECT_FLOAT_EQ(0, parameter.states_.front()[1])
    << "initial value should be (0, 0)";
  EXPECT_FLOAT_EQ(0, parameter.states_.front()[2])
    << "initial value should be (0, 0)";
  EXPECT_FLOAT_EQ(1, parameter.states_.back()[1])
    << "optimal value should be (1, 1)";
  EXPECT_FLOAT_EQ(1, parameter.states_.back()[2])
    << "optimal value should be (1, 1)";
  EXPECT_FLOAT_EQ(return_code, 0);
  EXPECT_EQ(19, callback.n);
}
