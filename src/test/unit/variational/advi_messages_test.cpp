#include <test/test-models/good/variational/univariate_no_constraint.hpp>
#include <stan/variational/advi.hpp>
#include <stan/interface_callbacks/writer/stream_writer.hpp>
#include <gtest/gtest.h>
#include <test/unit/util.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <boost/random/additive_combine.hpp> // L'Ecuyer RNG

typedef boost::ecuyer1988 rng_t;

class advi_test : public ::testing::Test {
public:
  advi_test()
    : message_writer(message_stream_),
      parameter_writer(parameter_stream_),
      diagnostic_writer(diagnostic_stream_) { }
  
  void SetUp() {
    err_msg1 = "Informational Message: The maximum number of iterations is reached!";
    err_msg2 = "Informational Message: The ELBO at a previous iteration is larger than the ELBO upon convergence!";

    // Create mock data_var_context
    static const std::string DATA = "";
    std::stringstream data_stream(DATA);
    stan::io::dump data_var_context(data_stream);
    // data_stream.close();

    model_ = new stan_model(data_var_context, &model_stream_);
    cont_params_ = Eigen::VectorXd::Zero(model_->num_params_r());
    base_rng_.seed(3021828106u);
    model_stream_.str("");
    message_stream_.str("");
    parameter_stream_.str("");
    diagnostic_stream_.str("");

    advi_meanfield_ = new stan::variational::advi<stan_model, stan::variational::normal_meanfield, rng_t>
      (*model_, cont_params_, base_rng_,
       1, 100,
       1, 1);
    advi_fullrank_ = new stan::variational::advi<stan_model, stan::variational::normal_fullrank, rng_t>
      (*model_, cont_params_, base_rng_,
       1, 100,
       1, 1);
  }

  void TearDown() {
    delete advi_meanfield_;
    delete advi_fullrank_;
    delete model_;
  }

  std::string err_msg1;
  std::string err_msg2;

  stan::variational::advi<stan_model, stan::variational::normal_meanfield, rng_t> *advi_meanfield_;
  stan::variational::advi<stan_model, stan::variational::normal_fullrank, rng_t> *advi_fullrank_;
  std::stringstream model_stream_;
  std::stringstream message_stream_;
  std::stringstream parameter_stream_;
  std::stringstream diagnostic_stream_;
  stan::interface_callbacks::writer::stream_writer message_writer;
  stan::interface_callbacks::writer::stream_writer parameter_writer;
  stan::interface_callbacks::writer::stream_writer diagnostic_writer;
  
private:
  stan_model *model_;
  rng_t base_rng_;
  Eigen::VectorXd cont_params_;
};


TEST_F(advi_test, max_iteration_warn_meanfield) {
  EXPECT_EQ(0, advi_meanfield_->run(10, 0, 50, 0.01, 1,
                                    message_writer,
                                    parameter_writer,
                                    diagnostic_writer));
  EXPECT_TRUE(message_stream_.str().find(err_msg1) != std::string::npos)
    << "The message should have err_msg1 inside it.";
}

TEST_F(advi_test, max_iteration_warn_fullrank) {
  EXPECT_EQ(0, advi_fullrank_->run(10, 0, 50, 0.01, 1,
                                   message_writer,
                                   parameter_writer,
                                   diagnostic_writer));
  EXPECT_TRUE(message_stream_.str().find(err_msg1) != std::string::npos)
    << "The message should have err_msg1 inside it.";
}

TEST_F(advi_test, prev_elbo_larger_meanfield) {
  EXPECT_EQ(0, advi_meanfield_->run(10, 0, 50, 0.1, 100,
                                    message_writer,
                                    parameter_writer,
                                    diagnostic_writer));
  EXPECT_TRUE(message_stream_.str().find(err_msg2) != std::string::npos)
    << "The message should have err_msg2 inside it.";
}

TEST_F(advi_test, prev_elbo_larger_fullrank) {
  EXPECT_EQ(0, advi_fullrank_->run(10, 0, 50, 0.2, 100,
                                   message_writer,
                                   parameter_writer,
                                   diagnostic_writer));
  EXPECT_TRUE(message_stream_.str().find(err_msg2) != std::string::npos)
    << "The message should have err_msg2 inside it.";
}
