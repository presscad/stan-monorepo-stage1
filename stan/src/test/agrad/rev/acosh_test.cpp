#include <stan/agrad/rev/acosh.hpp>
#include <test/agrad/util.hpp>
#include <gtest/gtest.h>
#include <stan/math/constants.hpp>

TEST(AgradRev,acosh_val) {
  AVAR a = 1.3;
  AVAR f = acosh(a);
  EXPECT_FLOAT_EQ(acosh(1.3), f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(1.0/sqrt(1.3 * 1.3  - 1.0), g[0]);
}

TEST(AgradRev,acosh_1) {
  AVAR a = 1;
  AVAR f = acosh(a);
  EXPECT_FLOAT_EQ(0.0, f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(1.0/sqrt(-1.0 * -1.0 - 1.0), g[0]);
}

TEST(AgradRev,acosh_inf) {
  double inf = std::numeric_limits<double>::infinity();
  AVAR a = inf;
  AVAR f = acosh(a);
  EXPECT_FLOAT_EQ(inf, f.val());
  
  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ((0.0), g[0]);
}

TEST(AgradRev,acosh_out_of_bounds) {
  double inf = std::numeric_limits<double>::infinity();
  AVAR a = 1.0 - stan::math::EPSILON;
  AVAR b = 0.0;
  EXPECT_THROW(acosh(a),std::domain_error);
  EXPECT_THROW(acosh(b),std::domain_error);
}
