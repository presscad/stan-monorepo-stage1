#include <gtest/gtest.h>
#include <boost/type_traits.hpp>
#include <stan/agrad/agrad.hpp>
#include <stan/meta/traits.hpp>
#include <stan/math/matrix.hpp>

TEST(MetaTraits, isConstant) {
  using stan::is_constant;
  EXPECT_TRUE(is_constant<double>::value);
  EXPECT_TRUE(is_constant<float>::value);
  EXPECT_TRUE(is_constant<unsigned int>::value);
  EXPECT_TRUE(is_constant<int>::value);
  EXPECT_FALSE(is_constant<stan::agrad::var>::value);
}

TEST(MetaTraits, is_vector) {
  using stan::is_vector;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  EXPECT_FALSE(is_vector<double>::value);
  EXPECT_FALSE(is_vector<int>::value);
  EXPECT_FALSE(is_vector<size_t>::value);

  EXPECT_FALSE(is_vector<const double>::value);
  EXPECT_FALSE(is_vector<const int>::value);
  EXPECT_FALSE(is_vector<const size_t>::value);

  EXPECT_TRUE(is_vector<std::vector<double> >::value);
  EXPECT_TRUE(is_vector<std::vector<int> >::value);
  EXPECT_TRUE(is_vector<std::vector<const double> >::value);
  EXPECT_TRUE(is_vector<std::vector<const int> >::value);

  typedef Matrix<double,Dynamic,1> temp_vec_d;
  EXPECT_TRUE(is_vector<temp_vec_d>::value);
  EXPECT_TRUE(is_vector<const temp_vec_d>::value);
  
  typedef Matrix<double,1,Dynamic> temp_rowvec_d;
  EXPECT_TRUE(is_vector<temp_rowvec_d>::value);
  EXPECT_TRUE(is_vector<const temp_rowvec_d>::value);

  typedef Matrix<double,Dynamic,Dynamic> temp_matrix_d;
  EXPECT_FALSE(is_vector<temp_matrix_d>::value);
  EXPECT_FALSE(is_vector<const temp_matrix_d>::value);
}

typedef Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> const_t1;
typedef std::vector<const_t1> const_t2;
typedef std::vector<const_t2> const_t3;

typedef Eigen::Matrix<double,Eigen::Dynamic,1> const_u1;
typedef std::vector<const_u1> const_u2;
typedef std::vector<const_u2> const_u3;

typedef Eigen::Matrix<double,1,Eigen::Dynamic> const_v1;
typedef std::vector<const_v1> const_v2;
typedef std::vector<const_v2> const_v3;

typedef Eigen::Matrix<stan::agrad::var,Eigen::Dynamic,Eigen::Dynamic> var_t1;
typedef std::vector<var_t1> var_t2;
typedef std::vector<var_t2> var_t3;

typedef Eigen::Matrix<stan::agrad::var,Eigen::Dynamic,1> var_u1;
typedef std::vector<var_u1> var_u2;
typedef std::vector<var_u2> var_u3;

typedef Eigen::Matrix<stan::agrad::var,1,Eigen::Dynamic> var_v1;
typedef std::vector<var_v1> var_v2;
typedef std::vector<var_v2> var_v3;


TEST(MetaTraits, isConstantStruct) {
  using stan::is_constant_struct;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  EXPECT_TRUE(is_constant_struct<int>::value);
  EXPECT_TRUE(is_constant_struct<double>::value);
  EXPECT_TRUE(is_constant_struct<float>::value);
  EXPECT_TRUE(is_constant_struct<long>::value);
  EXPECT_TRUE(is_constant_struct<vector<double> >::value);
  EXPECT_TRUE(is_constant_struct<vector<vector<double> > >::value);
  EXPECT_TRUE(is_constant_struct<vector<vector<vector<double> > > >::value);
  EXPECT_TRUE(is_constant_struct<const_t1>::value);
  EXPECT_TRUE(is_constant_struct<const_t2>::value);
  EXPECT_TRUE(is_constant_struct<const_t3>::value);
  EXPECT_TRUE(is_constant_struct<const_u1>::value);
  EXPECT_TRUE(is_constant_struct<const_u2>::value);
  EXPECT_TRUE(is_constant_struct<const_u3>::value);
  EXPECT_TRUE(is_constant_struct<const_v1>::value);
  EXPECT_TRUE(is_constant_struct<const_v2>::value);
  EXPECT_TRUE(is_constant_struct<const_v3>::value);

  EXPECT_FALSE(is_constant_struct<stan::agrad::var>::value);
  EXPECT_FALSE(is_constant_struct<vector<stan::agrad::var> >::value);
  EXPECT_FALSE(is_constant_struct<vector<vector<stan::agrad::var> > >::value);
  EXPECT_FALSE(is_constant_struct<vector<vector<vector<stan::agrad::var> > > >::value);
  EXPECT_FALSE(is_constant_struct<var_t1>::value);
  EXPECT_FALSE(is_constant_struct<var_t2>::value);
  EXPECT_FALSE(is_constant_struct<var_t3>::value);
  EXPECT_FALSE(is_constant_struct<var_u1>::value);
  EXPECT_FALSE(is_constant_struct<var_u2>::value);
  EXPECT_FALSE(is_constant_struct<var_u3>::value);
  EXPECT_FALSE(is_constant_struct<var_v1>::value);
  EXPECT_FALSE(is_constant_struct<var_v2>::value);
  EXPECT_FALSE(is_constant_struct<var_v3>::value);

}

TEST(MetaTraits, length) {
  using stan::length;
  EXPECT_EQ(1U, length(27.0));
  EXPECT_EQ(1U, length(3));
  std::vector<double> x(10);
  EXPECT_EQ(10U, length(x));
}

TEST(MetaTraits, VectorView)  {
  using std::vector;
  using stan::VectorView;
  using Eigen::Matrix;
  using Eigen::Dynamic;

  vector<double> x(10);
  for (size_t n = 0; n < 10; ++n) x[n] = n;
  VectorView<vector<double> > xv(x);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(x[n], xv[n]);

  const vector<double> y(x);
  VectorView<const vector<double> > yv(y);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(y[n], yv[n]);

  Matrix<double,Dynamic,1> a(10);
  for (size_t n = 0; n < 10; ++n) a[n] = n;
  VectorView<Matrix<double,Dynamic,1> > av(a);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(a[n], av[n]);

  const Matrix<double,Dynamic,1> b(a);
  VectorView<const Matrix<double,Dynamic,1> > bv(b);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(b[n], bv[n]);

  Matrix<double,1,Dynamic> c(10);
  for (size_t n = 0; n < 10; ++n) c[n] = n;
  VectorView<Matrix<double,1,Dynamic> > cv(c);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(c[n], cv[n]);

  const Matrix<double,1,Dynamic> d(c);
  VectorView<const Matrix<double,Dynamic,1> > dv(d);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(d[n], dv[n]);
}

TEST(MetaTraits, AmbiguousVector) {
  using stan::AmbiguousVector;
  AmbiguousVector<double,true> av(10);
  for (size_t n = 0; n < 10; ++n)
    av[n] = n * n;
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(n * n, av[n]);
  EXPECT_EQ(10U, av.size());

  AmbiguousVector<double,false> bv(112); // 112 ignored
  EXPECT_EQ(1U, bv.size());
  bv[0] = 12.0;
  EXPECT_EQ(12.0, bv[0]);
}

TEST(MetaTraits, scalar_type) {
  using boost::is_same;
  using stan::scalar_type;
  using std::vector;

  stan::scalar_type<double>::type x = 5.0;
  EXPECT_EQ(5.0,x);

  stan::scalar_type<std::vector<int> >::type n = 1;
  EXPECT_EQ(1,n);

  // hack to get value of template into Google test macro 
  bool b1 = is_same<double,double>::value;
  EXPECT_TRUE(b1);

  bool b2 = is_same<double,int>::value;
  EXPECT_FALSE(b2);

  bool b3 = is_same<double, scalar_type<vector<double> >::type>::value;
  EXPECT_TRUE(b3);

  bool b4 = is_same<double, scalar_type<double>::type>::value;
  EXPECT_TRUE(b4);

  bool b5 = is_same<int, scalar_type<double>::type>::value;
  EXPECT_FALSE(b5);
}
