#include <gtest/gtest.h>
#include <test/models/model_test_fixture.hpp>

class Models_BugsExamples_Vol2_Endo2 : 
  public Model_Test_Fixture<Models_BugsExamples_Vol2_Endo2> {
protected:
  virtual void SetUp() {}
public:
  static std::vector<std::string> get_model_path() {
    std::vector<std::string> model_path;
    model_path.push_back("models");
    model_path.push_back("bugs_examples");
    model_path.push_back("vol2");
    model_path.push_back("endo");
    model_path.push_back("endo2");
    return model_path;
  }

  static bool has_data() {
    return true;
  }
};

INSTANTIATE_TYPED_TEST_CASE_P(Models_BugsExamples_Vol2_Endo2,
			      Model_Test_Fixture,
			      Models_BugsExamples_Vol2_Endo2);
