#include <gtest/gtest.h>
#include <test/models/model_test_fixture.hpp>

class Models_Transforms_BoundedDouble : 
  public Model_Test_Fixture<Models_Transforms_BoundedDouble> {
protected:
  virtual void SetUp() {
  }
public:
  static std::vector<std::string> get_model_path() {
    std::vector<std::string> model_path;
    model_path.push_back("models");
    model_path.push_back("transforms");
    model_path.push_back("bounded_double");
    return model_path;
  }
  static bool has_data() {
    return false;
  }

  static bool has_init() {
    return false;
  }

  static size_t num_iterations() {
    return iterations;
  }

  static void populate_chains() {
    default_populate_chains();
  }

  static std::vector<std::pair<size_t, double> >
  get_expected_values() {
    std::vector<std::pair<size_t, double> > expected_values;
    return expected_values;
  }

};

INSTANTIATE_TYPED_TEST_CASE_P(Models_Transforms_BoundedDouble,
			      Model_Test_Fixture,
			      Models_Transforms_BoundedDouble);
