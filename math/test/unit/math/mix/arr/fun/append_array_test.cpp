#include <stan/math/mix/arr.hpp>
#include <gtest/gtest.h>

TEST(AgradMix, append_array_fvar_var_double) {
  std::vector<double> x(2);
  std::vector<stan::math::fvar<stan::math::var > > y(3), result;

  x[0] = 1.0;
  x[1] = 2.0;
  y[0] = 5.0;
  y[0].d_ = 1.5;
  y[1] = 6.0;
  y[1].d_ = -2.5;
  y[2] = 7.0;
  y[2].d_ = -3.5;

  EXPECT_NO_THROW(result = stan::math::append_array(y, x));
  EXPECT_EQ(5, result.size());
  EXPECT_FLOAT_EQ(5.0, result[0].val().val());
  EXPECT_FLOAT_EQ(6.0, result[1].val().val());
  EXPECT_FLOAT_EQ(7.0, result[2].val().val());
  EXPECT_FLOAT_EQ(1.0, result[3].val().val());
  EXPECT_FLOAT_EQ(2.0, result[4].val().val());

  EXPECT_FLOAT_EQ(1.5, result[0].tangent().val());
  EXPECT_FLOAT_EQ(-2.5, result[1].tangent().val());
  EXPECT_FLOAT_EQ(-3.5, result[2].tangent().val());
  EXPECT_FLOAT_EQ(0.0, result[3].tangent().val());
  EXPECT_FLOAT_EQ(0.0, result[4].tangent().val());

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, y[j].val().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, y[j].tangent().adj());
    }
  }
}

TEST(AgradMix, append_array_double_fvar_var) {
  std::vector<double> x(2);
  std::vector<stan::math::fvar<stan::math::var> > y(3), result;

  x[0] = 1.0;
  x[1] = 2.0;
  y[0] = 5.0;
  y[0].d_ = 1.5;
  y[1] = 6.0;
  y[1].d_ = -2.5;
  y[2] = 7.0;
  y[2].d_ = -3.5;

  EXPECT_NO_THROW(result = stan::math::append_array(x, y));
  EXPECT_EQ(5, result.size());
  EXPECT_FLOAT_EQ(1.0, result[0].val().val());
  EXPECT_FLOAT_EQ(2.0, result[1].val().val());
  EXPECT_FLOAT_EQ(5.0, result[2].val().val());
  EXPECT_FLOAT_EQ(6.0, result[3].val().val());
  EXPECT_FLOAT_EQ(7.0, result[4].val().val());

  EXPECT_FLOAT_EQ(0.0, result[0].tangent().val());
  EXPECT_FLOAT_EQ(0.0, result[1].tangent().val());
  EXPECT_FLOAT_EQ(1.5, result[2].tangent().val());
  EXPECT_FLOAT_EQ(-2.5, result[3].tangent().val());
  EXPECT_FLOAT_EQ(-3.5, result[4].tangent().val());

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().adj());
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].tangent().adj());
    }
  }
}

TEST(AgradMix, append_array_fvar_var_fvar_var) {
  std::vector<stan::math::fvar<stan::math::var> > x(2), y(3), result;

  x[0] = 1.0;
  x[0].d_ = 2.5;
  x[1] = 2.0;
  x[1].d_ = 3.5;
  y[0] = 5.0;
  y[0].d_ = 1.5;
  y[1] = 6.0;
  y[1].d_ = -2.5;
  y[2] = 7.0;
  y[2].d_ = -3.5;

  EXPECT_NO_THROW(result = stan::math::append_array(x, y));
  EXPECT_EQ(5, result.size());
  EXPECT_FLOAT_EQ(1.0, result[0].val().val());
  EXPECT_FLOAT_EQ(2.0, result[1].val().val());
  EXPECT_FLOAT_EQ(5.0, result[2].val().val());
  EXPECT_FLOAT_EQ(6.0, result[3].val().val());
  EXPECT_FLOAT_EQ(7.0, result[4].val().val());

  EXPECT_FLOAT_EQ(2.5, result[0].tangent().val());
  EXPECT_FLOAT_EQ(3.5, result[1].tangent().val());
  EXPECT_FLOAT_EQ(1.5, result[2].tangent().val());
  EXPECT_FLOAT_EQ(-2.5, result[3].tangent().val());
  EXPECT_FLOAT_EQ(-3.5, result[4].tangent().val());

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().adj());
    }

    for(size_t j = 0; j < x.size(); j++) {
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, x[j].val().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().adj());
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].tangent().adj());
    }

    for(size_t j = 0; j < x.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, x[j].val().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, x[j].tangent().adj());
    }
  }
}

TEST(AgradMix, append_array_fvar_fvar_var_double) {
  std::vector<double> x(2);
  std::vector<stan::math::fvar<stan::math::fvar<stan::math::var> > > y(3), result;

  x[0] = 1.0;
  x[1] = 2.0;
  y[0] = 5.0;
  y[0].d_ = 1.5;
  y[1] = 6.0;
  y[1].d_ = -2.5;
  y[2] = 7.0;
  y[2].d_ = -3.5;

  EXPECT_NO_THROW(result = stan::math::append_array(y, x));
  EXPECT_EQ(5, result.size());
  EXPECT_FLOAT_EQ(5.0, result[0].val().val().val());
  EXPECT_FLOAT_EQ(6.0, result[1].val().val().val());
  EXPECT_FLOAT_EQ(7.0, result[2].val().val().val());
  EXPECT_FLOAT_EQ(1.0, result[3].val().val().val());
  EXPECT_FLOAT_EQ(2.0, result[4].val().val().val());

  EXPECT_FLOAT_EQ(1.5, result[0].tangent().val().val());
  EXPECT_FLOAT_EQ(-2.5, result[1].tangent().val().val());
  EXPECT_FLOAT_EQ(-3.5, result[2].tangent().val().val());
  EXPECT_FLOAT_EQ(0.0, result[3].tangent().val().val());
  EXPECT_FLOAT_EQ(0.0, result[4].tangent().val().val());

  for(size_t i = 0; i < result.size(); i++) {
    EXPECT_FLOAT_EQ(0.0, result[i].val().tangent().val());
    EXPECT_FLOAT_EQ(0.0, result[i].tangent().tangent().val());
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, y[j].tangent().tangent().adj());
    }
  }
}

TEST(AgradMix, append_array_double_fvar_fvar_var) {
  std::vector<double> x(2);
  std::vector<stan::math::fvar<stan::math::fvar<stan::math::var> > > y(3), result;

  x[0] = 1.0;
  x[1] = 2.0;
  y[0] = 5.0;
  y[0].d_ = 1.5;
  y[1] = 6.0;
  y[1].d_ = -2.5;
  y[2] = 7.0;
  y[2].d_ = -3.5;

  EXPECT_NO_THROW(result = stan::math::append_array(x, y));
  EXPECT_EQ(5, result.size());
  EXPECT_FLOAT_EQ(1.0, result[0].val().val().val());
  EXPECT_FLOAT_EQ(2.0, result[1].val().val().val());
  EXPECT_FLOAT_EQ(5.0, result[2].val().val().val());
  EXPECT_FLOAT_EQ(6.0, result[3].val().val().val());
  EXPECT_FLOAT_EQ(7.0, result[4].val().val().val());

  EXPECT_FLOAT_EQ(0.0, result[0].tangent().val().val());
  EXPECT_FLOAT_EQ(0.0, result[1].tangent().val().val());
  EXPECT_FLOAT_EQ(1.5, result[2].tangent().val().val());
  EXPECT_FLOAT_EQ(-2.5, result[3].tangent().val().val());
  EXPECT_FLOAT_EQ(-3.5, result[4].tangent().val().val());

  for(size_t i = 0; i < result.size(); i++) {
    EXPECT_FLOAT_EQ(0.0, result[i].val().tangent().val());
    EXPECT_FLOAT_EQ(0.0, result[i].tangent().tangent().val());
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].tangent().tangent().adj());
    }
  }
}

TEST(AgradMix, append_array_fvar_fvar_var_fvar_fvar_var) {
  std::vector<stan::math::fvar<stan::math::fvar<stan::math::var> > > x(2), y(3), result;

  x[0] = 1.0;
  x[0].d_ = 2.5;
  x[1] = 2.0;
  x[1].d_ = 3.5;
  y[0] = 5.0;
  y[0].d_ = 1.5;
  y[1] = 6.0;
  y[1].d_ = -2.5;
  y[2] = 7.0;
  y[2].d_ = -3.5;

  EXPECT_NO_THROW(result = stan::math::append_array(x, y));
  EXPECT_EQ(5, result.size());
  EXPECT_FLOAT_EQ(1.0, result[0].val().val().val());
  EXPECT_FLOAT_EQ(2.0, result[1].val().val().val());
  EXPECT_FLOAT_EQ(5.0, result[2].val().val().val());
  EXPECT_FLOAT_EQ(6.0, result[3].val().val().val());
  EXPECT_FLOAT_EQ(7.0, result[4].val().val().val());

  EXPECT_FLOAT_EQ(2.5, result[0].tangent().val().val());
  EXPECT_FLOAT_EQ(3.5, result[1].tangent().val().val());
  EXPECT_FLOAT_EQ(1.5, result[2].tangent().val().val());
  EXPECT_FLOAT_EQ(-2.5, result[3].tangent().val().val());
  EXPECT_FLOAT_EQ(-3.5, result[4].tangent().val().val());

  for(size_t i = 0; i < result.size(); i++) {
    EXPECT_FLOAT_EQ(0.0, result[i].tangent().tangent().val());
    EXPECT_FLOAT_EQ(0.0, result[i].val().tangent().val());
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }

    for(size_t j = 0; j < x.size(); j++) {
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, x[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].val().tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }

    for(size_t j = 0; j < x.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, x[j].val().val().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, x[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().val().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().tangent().adj());
    }

    for(size_t j = 0; j < x.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, x[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].val().tangent().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, x[j].tangent().val().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].tangent().tangent().adj());
    }
  }

  for(size_t i = 0; i < result.size(); i++) {
    stan::math::set_zero_all_adjoints();

    result[i].tangent().tangent().grad();

    for(size_t j = 0; j < y.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, y[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, y[j].tangent().val().adj());
      EXPECT_FLOAT_EQ((i - 2 == j) ? 1.0 : 0.0, y[j].tangent().tangent().adj());
    }

    for(size_t j = 0; j < x.size(); j++) {
      EXPECT_FLOAT_EQ(0.0, x[j].val().val().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].val().tangent().adj());
      EXPECT_FLOAT_EQ(0.0, x[j].tangent().val().adj());
      EXPECT_FLOAT_EQ((i == j) ? 1.0 : 0.0, x[j].tangent().tangent().adj());
    }
  }
}
