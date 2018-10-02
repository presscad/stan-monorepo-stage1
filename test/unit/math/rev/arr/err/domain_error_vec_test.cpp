#include <gtest/gtest.h>
#include <stan/math/rev/arr.hpp>
#include <string>
#include <vector>

const char *function_ = "function";
const char *y_name_ = "y";
const char *msg1_ = "error_message ";
const char *msg2_ = " second message";

class ErrorHandlingScalar_domain_error_vec : public ::testing::Test {
public:
  void SetUp() { index_ = 0; }

  template <class T> std::string expected_message_with_message(T y) {
    using stan::math::value_type;
    std::stringstream expected_message;
    expected_message << "function: " << y_name_ << "[" << 1 + index_ << "] "
                     << "error_message " << y[index_] << " second message";
    return expected_message.str();
  }

  template <class T> std::string expected_message_without_message(T y) {
    using stan::math::value_type;
    std::stringstream expected_message;
    expected_message << "function: " << y_name_ << "[" << 1 + index_ << "] "
                     << "error_message " << y[index_];
    return expected_message.str();
  }

  template <class T> void test_throw(T y) {
    try {
      stan::math::domain_error_vec<T>(function_, y_name_, y, index_, msg1_,
                                      msg2_);
      FAIL() << "expecting call to domain_error_vec<> to throw a domain_error, "
             << "but threw nothing";
    } catch (std::domain_error &e) {
      EXPECT_EQ(expected_message_with_message(y), e.what());
    } catch (...) {
      FAIL() << "expecting call to domain_error_vec<> to throw a domain_error, "
             << "but threw a different type";
    }

    try {
      stan::math::domain_error_vec<T>(function_, y_name_, y, index_, msg1_);
      FAIL() << "expecting call to domain_error_vec<> to throw a domain_error, "
             << "but threw nothing";
    } catch (std::domain_error &e) {
      EXPECT_EQ(expected_message_without_message(y), e.what());
    } catch (...) {
      FAIL() << "expecting call to domain_error_vec<> to throw a domain_error, "
             << "but threw a different type";
    }
  }

  size_t index_;
};

TEST_F(ErrorHandlingScalar_domain_error_vec, vvar) {
  std::vector<stan::math::var> y;
  y.push_back(10);

  test_throw<std::vector<stan::math::var>>(y);
}
