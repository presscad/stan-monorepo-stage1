#include <gtest/gtest.h>
#include <boost/type_traits.hpp>
#include <stan/math/fwd/core/fvar.hpp>
#include <stan/math/prim/scal/meta/error_index.hpp>
#include <stan/math/prim/scal/meta/is_constant.hpp>
#include <stan/math/prim/scal/meta/is_constant_struct.hpp>
#include <stan/math/prim/scal/meta/contains_nonconstant_struct.hpp>
#include <stan/math/prim/scal/meta/is_vector.hpp>
#include <stan/math/prim/scal/meta/contains_vector.hpp>
#include <stan/math/prim/scal/meta/scalar_type.hpp>
#include <stan/math/prim/scal/meta/get.hpp>
#include <stan/math/prim/scal/meta/length.hpp>
#include <stan/math/prim/scal/meta/size_of.hpp>
#include <stan/math/prim/scal/meta/max_size.hpp>
#include <stan/math/prim/scal/meta/is_vector_like.hpp>
#include <stan/math/prim/scal/meta/VectorView.hpp>
#include <stan/math/prim/scal/meta/VectorBuilder.hpp>
#include <stan/math/prim/scal/meta/return_type.hpp>
#include <stan/math/prim/scal/meta/is_fvar.hpp>
#include <stan/math/prim/scal/meta/is_var.hpp>
#include <stan/math/prim/scal/meta/partials_type.hpp>
#include <stan/math/prim/scal/meta/contains_fvar.hpp>
#include <stan/math/prim/scal/meta/partials_return_type.hpp>
#include <stan/math/prim/scal/meta/is_var_or_arithmetic.hpp>
#include <stan/math/prim/scal/meta/scalar_type_pre.hpp>
#include <stan/math/prim/scal/meta/VectorViewMvt.hpp>
#include <stan/math/prim/scal/meta/length.hpp>
#include <stan/math/prim/scal/meta/max_size_mvt.hpp>
#include <stan/math/fwd/scal/meta/is_fvar.hpp>
#include <stan/math/rev/scal/meta/is_var.hpp>

using stan::length;

TEST(MetaTraits, error_index) {
  EXPECT_EQ(1, int(stan::error_index::value));
}

TEST(MetaTraits, isConstant) {
  using stan::is_constant;
  using stan::agrad::fvar;
  using stan::agrad::var;

  EXPECT_TRUE(is_constant<double>::value);
  EXPECT_TRUE(is_constant<float>::value);
  EXPECT_TRUE(is_constant<unsigned int>::value);
  EXPECT_TRUE(is_constant<int>::value);
  EXPECT_FALSE(is_constant<var>::value);
  EXPECT_FALSE(is_constant<fvar<var> >::value);
  EXPECT_FALSE(is_constant<fvar<double> >::value);
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

TEST(MetaTraits, contains_vector) {
  using stan::contains_vector;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  EXPECT_FALSE(contains_vector<double>::value);
  EXPECT_FALSE(contains_vector<int>::value);
  EXPECT_FALSE(contains_vector<size_t>::value);

  EXPECT_FALSE(contains_vector<const double>::value);
  EXPECT_FALSE(contains_vector<const int>::value);
  EXPECT_FALSE(contains_vector<const size_t>::value);

  EXPECT_TRUE(contains_vector<std::vector<double> >::value);
  EXPECT_TRUE(contains_vector<std::vector<int> >::value);
  EXPECT_TRUE(contains_vector<std::vector<const double> >::value);
  EXPECT_TRUE(contains_vector<std::vector<const int> >::value);

  typedef Matrix<double,Dynamic,1> temp_vec_d;
  EXPECT_TRUE(contains_vector<temp_vec_d>::value);
  EXPECT_TRUE(contains_vector<const temp_vec_d>::value);
  
  typedef Matrix<double,1,Dynamic> temp_rowvec_d;
  EXPECT_TRUE(contains_vector<temp_rowvec_d>::value);
  EXPECT_TRUE(contains_vector<const temp_rowvec_d>::value);

  typedef Matrix<double,Dynamic,Dynamic> temp_matrix_d;
  EXPECT_FALSE(contains_vector<temp_matrix_d>::value);
  EXPECT_FALSE(contains_vector<const temp_matrix_d>::value);

  bool temp = contains_vector<temp_vec_d, temp_vec_d, 
                              double, temp_matrix_d>::value;
  EXPECT_TRUE(temp);

  temp = contains_vector<double, temp_matrix_d, temp_matrix_d>::value;
  EXPECT_FALSE(temp);
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

TEST(MetaTraits, containsNonconstantStruct) {
  using stan::contains_nonconstant_struct;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  EXPECT_FALSE(contains_nonconstant_struct<int>::value);
  EXPECT_FALSE(contains_nonconstant_struct<double>::value);
  EXPECT_FALSE(contains_nonconstant_struct<float>::value);
  EXPECT_FALSE(contains_nonconstant_struct<long>::value);
  EXPECT_FALSE(contains_nonconstant_struct<vector<double> >::value);
  EXPECT_FALSE(contains_nonconstant_struct<vector<vector<double> > >::value);
  EXPECT_FALSE(contains_nonconstant_struct<vector<vector<vector<double> > > >::value);
  EXPECT_FALSE(contains_nonconstant_struct<const_t1>::value);
  EXPECT_FALSE(contains_nonconstant_struct<const_t3>::value);
  EXPECT_FALSE(contains_nonconstant_struct<const_u1>::value);
  EXPECT_FALSE(contains_nonconstant_struct<const_u3>::value);
  EXPECT_FALSE(contains_nonconstant_struct<const_v2>::value);

  EXPECT_TRUE(contains_nonconstant_struct<stan::agrad::var>::value);
  EXPECT_TRUE(contains_nonconstant_struct<vector<stan::agrad::var> >::value);
  EXPECT_TRUE(contains_nonconstant_struct<vector<vector<stan::agrad::var> > >::value);
  EXPECT_TRUE(contains_nonconstant_struct<vector<vector<vector<stan::agrad::var> > > >::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_t1>::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_t2>::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_t3>::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_u1>::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_u2>::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_u3>::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_v1>::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_v2>::value);
  EXPECT_TRUE(contains_nonconstant_struct<var_v3>::value);

  bool temp = contains_nonconstant_struct<var_v3,var_v2,var_v1,double,int>::value;
  EXPECT_TRUE(temp);

  temp = contains_nonconstant_struct<const_v3,const_v2,const_v1,double,int>::value;
  EXPECT_FALSE(temp);
}

TEST(MetaTraits, length) {
  using stan::length;
  EXPECT_EQ(1U, length(27.0));
  EXPECT_EQ(1U, length(3));
  std::vector<double> x(10);
  EXPECT_EQ(10U, length(x));

  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> m(2,3);
  m << 1, 2, 3, 4, 5, 6;
  EXPECT_EQ(6U, length(m));

  Eigen::Matrix<double,Eigen::Dynamic,1> rv(2);
  rv << 1, 2;
  EXPECT_EQ(2U, length(rv));

  Eigen::Matrix<double,1,Eigen::Dynamic> v(2);
  v << 1, 2;
  EXPECT_EQ(2U, length(v));
}

TEST(MetaTraits, get) {
  using stan::get;

  EXPECT_FLOAT_EQ(2.0, get(2.0,1));

  std::vector<double> x(3);
  x[1] = 5.0;
  EXPECT_EQ(5.0, get(x,1));

  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> m(2,3);
  m << 1, 3, 5, 
       2, 4, 6;
  EXPECT_EQ(1.0, get(m,0));
  EXPECT_EQ(3.0, get(m,2));
  EXPECT_EQ(6.0, get(m,5));

  Eigen::Matrix<double,Eigen::Dynamic,1> rv(2);
  rv << 1, 2;
  EXPECT_EQ(1.0, get(rv,0));
  EXPECT_EQ(2.0, get(rv,1));

  Eigen::Matrix<double,1,Eigen::Dynamic> v(2);
  v << 1, 2;
  EXPECT_EQ(1.0, get(v,0));
  EXPECT_EQ(2.0, get(v,1));
}

TEST(MetaTraits, VectorView_double)  {
  using stan::VectorView;

  double d(10);
  VectorView<double> dv(d);
  EXPECT_FLOAT_EQ(d, dv[0]);
  dv[1] = 2.0;
  EXPECT_FLOAT_EQ(2.0, dv[0]);
  EXPECT_FLOAT_EQ(2.0, d);

  const double c(10);
  VectorView<const double> cv(c);
  EXPECT_FLOAT_EQ(c, cv[0]);
}
TEST(MetaTraits, VectorView_var) {
  using stan::VectorView;
  using stan::agrad::var;
  
  var d(10);
  VectorView<var> dv(d);
  EXPECT_FLOAT_EQ(d.val(), dv[0].val());
  dv[1] = 2.0;
  EXPECT_FLOAT_EQ(2.0, dv[0].val());
  EXPECT_FLOAT_EQ(2.0, d.val());

  const var c(10);
  VectorView<const var> cv(c);
  EXPECT_FLOAT_EQ(c.val(), cv[0].val());
}
TEST(MetaTraits, VectorView_vector_double) {
  using stan::VectorView;
  using std::vector;
  
  vector<double> x(10);
  for (size_t n = 0; n < 10; ++n) 
    x[n] = n;
  VectorView<vector<double> > xv(x);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(x[n], xv[n]);
  for (size_t n = 0; n < 10; ++n)
    xv[n] = 10+n;
  for (size_t n = 0; n < 10; ++n) {
    EXPECT_FLOAT_EQ(x[n], xv[n]);
    EXPECT_FLOAT_EQ(10+n, xv[n]);
  }

  const vector<double> y(x);
  VectorView<const vector<double> > yv(y);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(y[n], yv[n]);
}
TEST(MetaTraits, VectorView_vector_var) {
  using stan::VectorView;
  using std::vector;
  using stan::agrad::var;
  
  vector<var> x(10);
  for (size_t n = 0; n < 10; ++n) 
    x[n] = n;
  VectorView<vector<var> > xv(x);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(x[n].val(), xv[n].val());
  for (size_t n = 0; n < 10; ++n)
    xv[n] = 10+n;
  for (size_t n = 0; n < 10; ++n) {
    EXPECT_FLOAT_EQ(x[n].val(), xv[n].val());
    EXPECT_FLOAT_EQ(10+n, xv[n].val());
  }

  const vector<var> y(x);
  VectorView<const vector<var> > yv(y);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(y[n].val(), yv[n].val());
}
TEST(MetaTraits, VectorView_matrix_double) {
  using stan::VectorView;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  
  Matrix<double,Dynamic,1> a(10);
  for (size_t n = 0; n < 10; ++n) 
    a[n] = n;
  VectorView<Matrix<double,Dynamic,1> > av(a);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(a[n], av[n]);
  for (size_t n = 0; n < 10; ++n)
    av[n] = n+10;
  for (size_t n = 0; n < 10; ++n) {
    EXPECT_FLOAT_EQ(10+n, av[n]);
    EXPECT_FLOAT_EQ(10+n, a[n]);
  }

  const Matrix<double,Dynamic,1> b(a);
  VectorView<const Matrix<double,Dynamic,1> > bv(b);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(b[n], bv[n]);
  
  Matrix<double,1,Dynamic> c(10);
  for (size_t n = 0; n < 10; ++n) 
    c[n] = n;
  VectorView<Matrix<double,1,Dynamic> > cv(c);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(c[n], cv[n]);
  for (size_t n = 0; n < 10; ++n) 
    cv[n] = n+10;
  for (size_t n = 0; n < 10; ++n) {
    EXPECT_FLOAT_EQ(10+n, cv[n]);
    EXPECT_FLOAT_EQ(10+n, c[n]);
  }

  const Matrix<double,1,Dynamic> d(c);
  VectorView<const Matrix<double,1,Dynamic>, 
          stan::is_vector<Matrix<double,1,Dynamic> >::value > dv(d);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(d[n], dv[n]);
}
TEST(MetaTraits, VectorView_matrix_var) {
  using stan::VectorView;
  using stan::agrad::var;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  
  Matrix<var,Dynamic,1> a(10);
  for (size_t n = 0; n < 10; ++n) 
    a[n] = n;
  VectorView<Matrix<var,Dynamic,1> > av(a);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(a[n].val(), av[n].val());
  for (size_t n = 0; n < 10; ++n)
    av[n] = n+10;
  for (size_t n = 0; n < 10; ++n) {
    EXPECT_FLOAT_EQ(10+n, av[n].val());
    EXPECT_FLOAT_EQ(10+n, a[n].val());
  }

  const Matrix<var,Dynamic,1> b(a);
  VectorView<const Matrix<var,Dynamic,1> > bv(b);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(b[n].val(), bv[n].val());
  
  Matrix<var,1,Dynamic> c(10);
  for (size_t n = 0; n < 10; ++n) 
    c[n] = n;
  VectorView<Matrix<var,1,Dynamic> > cv(c);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(c[n].val(), cv[n].val());
  for (size_t n = 0; n < 10; ++n) 
    cv[n] = n+10;
  for (size_t n = 0; n < 10; ++n) {
    EXPECT_FLOAT_EQ(10+n, cv[n].val());
    EXPECT_FLOAT_EQ(10+n, c[n].val());
  }

  const Matrix<var,1,Dynamic> d(c);
  VectorView<const Matrix<var,1,Dynamic> > dv(d);
  for (size_t n = 0; n < 10; ++n)
    EXPECT_FLOAT_EQ(d[n].val(), dv[n].val());
}
TEST(MetaTraits, VectorView_double_star) {
  using stan::VectorView;
  double a[10];
  double *a_star = &a[0];
  for (size_t n = 0; n < 10; ++n)
    a[n] = n;
  VectorView<double*,true> av(a_star);
  for (size_t n = 0; n < 10; ++n) 
    EXPECT_FLOAT_EQ(a[n], av[n]);
  for (size_t n = 0; n < 10; ++n)
    av[n] = n+10;
  for (size_t n = 0; n < 10; ++n) {
    EXPECT_FLOAT_EQ(n+10, a[n]);
    EXPECT_FLOAT_EQ(n+10, av[n]);
  }

  double b(20);
  double *b_star = &b;
  VectorView<double*,false> bv(b_star);
  for (size_t n = 0; n < 10; ++n) 
    EXPECT_FLOAT_EQ(20, bv[n]);
  bv[1] = 10;
  EXPECT_FLOAT_EQ(10, bv[0]);
  EXPECT_FLOAT_EQ(10, b);
}

TEST(MetaTraits, VectorBuilderHelper_false_false) {
  using std::vector;
  using stan::VectorBuilderHelper;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::agrad::var;

  double a_double(1);
  std::vector<double> a_std_vector(3);
  Matrix<double,Dynamic,1> a_vector(4);
  Matrix<double,1,Dynamic> a_row_vector(5);

  VectorBuilderHelper<double,false,false> dvv1(length(a_double));
  EXPECT_THROW(dvv1[0], std::logic_error);

  VectorBuilderHelper<double,false,false> dvv2(length(a_std_vector));
  EXPECT_THROW(dvv2[0], std::logic_error);
  
  VectorBuilderHelper<double,false,false> dvv3(length(a_vector));
  EXPECT_THROW(dvv3[0], std::logic_error);
  
  VectorBuilderHelper<double,false,false> dvv4(length(a_row_vector));
  EXPECT_THROW(dvv4[0], std::logic_error);
}

TEST(MetaTraits, VectorBuilderHelper_true_false) {
  using std::vector;
  using stan::VectorBuilderHelper;
  using Eigen::Matrix;
  using Eigen::Dynamic;

  double a_double(1);
  std::vector<double> a_std_vector(3);
  Matrix<double,Dynamic,1> a_vector(4);
  Matrix<double,1,Dynamic> a_row_vector(5);

  VectorBuilderHelper<double,true,false> dvv1(length(a_double));
  EXPECT_FLOAT_EQ(0.0, dvv1[0]);
  EXPECT_FLOAT_EQ(0.0, dvv1[1]);
  EXPECT_FLOAT_EQ(0.0, dvv1[100]);

  VectorBuilderHelper<double,true,false> dvv2(length(a_std_vector));
  EXPECT_FLOAT_EQ(0.0, dvv2[0]);
  EXPECT_FLOAT_EQ(0.0, dvv2[1]);
  EXPECT_FLOAT_EQ(0.0, dvv2[2]);  
  
  VectorBuilderHelper<double,true,false> dvv3(length(a_vector));
  EXPECT_FLOAT_EQ(0.0, dvv3[0]);
  EXPECT_FLOAT_EQ(0.0, dvv3[1]);
  EXPECT_FLOAT_EQ(0.0, dvv3[2]);  
  
  VectorBuilderHelper<double,true,false> dvv4(length(a_row_vector));
  EXPECT_FLOAT_EQ(0.0, dvv4[0]);
  EXPECT_FLOAT_EQ(0.0, dvv4[1]);
  EXPECT_FLOAT_EQ(0.0, dvv4[2]);
}

TEST(MetaTraits, VectorBuilderHelper_false_true) {
  using std::vector;
  using stan::VectorBuilderHelper;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::agrad::var;

  var a_var(1);
  std::vector<var> a_std_vector(3);
  Matrix<var,Dynamic,1> a_vector(4);
  Matrix<var,1,Dynamic> a_row_vector(5);

  VectorBuilderHelper<double,false,true> dvv1(length(a_var));
  EXPECT_THROW(dvv1[0], std::logic_error);

  VectorBuilderHelper<double,false,true> dvv2(length(a_std_vector));
  EXPECT_THROW(dvv2[0], std::logic_error);
  
  VectorBuilderHelper<double,false,true> dvv3(length(a_vector));
  EXPECT_THROW(dvv3[0], std::logic_error);
  
  VectorBuilderHelper<double,false,true> dvv4(length(a_row_vector));
  EXPECT_THROW(dvv4[0], std::logic_error);
}

TEST(MetaTraits, VectorBuilderHelper_true_true) {
  using std::vector;
  using stan::VectorBuilderHelper;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::agrad::var;

  var a_var(1);
  std::vector<var> a_std_vector(3);
  Matrix<var,Dynamic,1> a_vector(4);
  Matrix<var,1,Dynamic> a_row_vector(5);

  VectorBuilderHelper<double,true,true> dvv1(length(a_var));
  dvv1[0] = 0.0;
  EXPECT_FLOAT_EQ(0.0, dvv1[0]);

  VectorBuilderHelper<double,true,true> dvv2(length(a_std_vector));
  dvv2[0] = 0.0;
  dvv2[1] = 1.0;
  dvv2[2] = 2.0;
  EXPECT_FLOAT_EQ(0.0, dvv2[0]);
  EXPECT_FLOAT_EQ(1.0, dvv2[1]);
  EXPECT_FLOAT_EQ(2.0, dvv2[2]);  
  
  VectorBuilderHelper<double,true,true> dvv3(length(a_vector));
  dvv3[0] = 0.0;
  dvv3[1] = 1.0;
  dvv3[2] = 2.0;
  EXPECT_FLOAT_EQ(0.0, dvv3[0]);
  EXPECT_FLOAT_EQ(1.0, dvv3[1]);
  EXPECT_FLOAT_EQ(2.0, dvv3[2]);  
  
  VectorBuilderHelper<double,true,true> dvv4(length(a_row_vector));
  dvv4[0] = 0.0;
  dvv4[1] = 1.0;
  dvv4[2] = 2.0;
  EXPECT_FLOAT_EQ(0.0, dvv4[0]);
  EXPECT_FLOAT_EQ(1.0, dvv4[1]);
  EXPECT_FLOAT_EQ(2.0, dvv4[2]);
}

TEST(MetaTraits, VectorBuilder_false_false) {
  using std::vector;
  using stan::VectorBuilder;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::agrad::var;

  double a_double(1);
  std::vector<double> a_std_vector(3);
  Matrix<double,Dynamic,1> a_vector(4);
  Matrix<double,1,Dynamic> a_row_vector(5);

  VectorBuilder<false,double,double> dvv1(length(a_double));
  EXPECT_THROW(dvv1[0], std::logic_error);

  VectorBuilder<false,double,double> dvv2(length(a_std_vector));
  EXPECT_THROW(dvv2[0], std::logic_error);
  
  VectorBuilder<false,double,double> dvv3(length(a_vector));
  EXPECT_THROW(dvv3[0], std::logic_error);
  
  VectorBuilder<false,double,double> dvv4(length(a_row_vector));
  EXPECT_THROW(dvv4[0], std::logic_error);
}
TEST(MetaTraits, VectorBuilder_true_false) {
  using std::vector;
  using stan::VectorBuilder;
  using Eigen::Matrix;
  using Eigen::Dynamic;

  double a_double(1);
  std::vector<double> a_std_vector(3);
  Matrix<double,Dynamic,1> a_vector(4);
  Matrix<double,1,Dynamic> a_row_vector(5);

  VectorBuilder<true,double,double> dvv1(length(a_double));
  EXPECT_FLOAT_EQ(0.0, dvv1[0]);
  EXPECT_FLOAT_EQ(0.0, dvv1[1]);
  EXPECT_FLOAT_EQ(0.0, dvv1[100]);

  VectorBuilder<true,double,double> dvv2(length(a_std_vector));
  EXPECT_FLOAT_EQ(0.0, dvv2[0]);
  EXPECT_FLOAT_EQ(0.0, dvv2[1]);
  EXPECT_FLOAT_EQ(0.0, dvv2[2]);  
  
  VectorBuilder<true,double,double> dvv3(length(a_vector));
  EXPECT_FLOAT_EQ(0.0, dvv3[0]);
  EXPECT_FLOAT_EQ(0.0, dvv3[1]);
  EXPECT_FLOAT_EQ(0.0, dvv3[2]);  
  
  VectorBuilder<true,double,double> dvv4(length(a_row_vector));
  EXPECT_FLOAT_EQ(0.0, dvv4[0]);
  EXPECT_FLOAT_EQ(0.0, dvv4[1]);
  EXPECT_FLOAT_EQ(0.0, dvv4[2]);
}

TEST(MetaTraits, VectorBuilder_false_true) {
  using std::vector;
  using stan::VectorBuilder;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::agrad::var;

  var a_var(1);
  std::vector<var> a_std_vector(3);
  Matrix<var,Dynamic,1> a_vector(4);
  Matrix<var,1,Dynamic> a_row_vector(5);

  VectorBuilder<false,double,std::vector<var> > dvv1(length(a_var));
  EXPECT_THROW(dvv1[0], std::logic_error);

  VectorBuilder<false,double,std::vector<var> > dvv2(length(a_std_vector));
  EXPECT_THROW(dvv2[0], std::logic_error);
  
  VectorBuilder<false,double,Matrix<var,Dynamic,1> > dvv3(length(a_vector));
  EXPECT_THROW(dvv3[0], std::logic_error);
  
  VectorBuilder<false,double,Matrix<var,1,Dynamic> > dvv4(length(a_row_vector));
  EXPECT_THROW(dvv4[0], std::logic_error);
}

TEST(MetaTraits, VectorBuilder_true_true) {
  using std::vector;
  using stan::VectorBuilder;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::agrad::var;

  var a_var(1);
  std::vector<var> a_std_vector(3);
  Matrix<var,Dynamic,1> a_vector(4);
  Matrix<var,1,Dynamic> a_row_vector(5);

  VectorBuilder<true,double,std::vector<var> > dvv1(length(a_var));
  dvv1[0] = 0.0;
  EXPECT_FLOAT_EQ(0.0, dvv1[0]);

  VectorBuilder<true,double,std::vector<var> > dvv2(length(a_std_vector));
  dvv2[0] = 0.0;
  dvv2[1] = 1.0;
  dvv2[2] = 2.0;
  EXPECT_FLOAT_EQ(0.0, dvv2[0]);
  EXPECT_FLOAT_EQ(1.0, dvv2[1]);
  EXPECT_FLOAT_EQ(2.0, dvv2[2]);  
  
  VectorBuilder<true,double,Matrix<var,Dynamic,1> > dvv3(length(a_vector));
  dvv3[0] = 0.0;
  dvv3[1] = 1.0;
  dvv3[2] = 2.0;
  EXPECT_FLOAT_EQ(0.0, dvv3[0]);
  EXPECT_FLOAT_EQ(1.0, dvv3[1]);
  EXPECT_FLOAT_EQ(2.0, dvv3[2]);  
  
  VectorBuilder<true,double,Matrix<var,1,Dynamic> > dvv4(length(a_row_vector));
  dvv4[0] = 0.0;
  dvv4[1] = 1.0;
  dvv4[2] = 2.0;
  EXPECT_FLOAT_EQ(0.0, dvv4[0]);
  EXPECT_FLOAT_EQ(1.0, dvv4[1]);
  EXPECT_FLOAT_EQ(2.0, dvv4[2]);
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

TEST(MetaTraits,VectorView) {
  using stan::VectorView;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;

  double x = 5;
  VectorView<const double> x_VectorView(x);
  EXPECT_FLOAT_EQ(x,x_VectorView[0]);
  EXPECT_FLOAT_EQ(x,x_VectorView[1]);
  EXPECT_FLOAT_EQ(x,x_VectorView[2]);

  vector<double> sv;
  sv.push_back(1.0);
  sv.push_back(4.0);
  sv.push_back(9.0);
  VectorView<const vector<double> > sv_VectorView(sv);
  EXPECT_FLOAT_EQ(1.0,sv_VectorView[0]);
  EXPECT_FLOAT_EQ(4.0,sv_VectorView[1]);
  EXPECT_FLOAT_EQ(9.0,sv_VectorView[2]);

  Matrix<double,Dynamic,1> v(3);
  v << 1.0, 4.0, 9.0;
  VectorView<const Matrix<double,Dynamic,1> > v_VectorView(v);
  EXPECT_FLOAT_EQ(1.0,v_VectorView[0]);
  EXPECT_FLOAT_EQ(4.0,v_VectorView[1]);
  EXPECT_FLOAT_EQ(9.0,v_VectorView[2]);

  Matrix<double,1,Dynamic> rv(3);
  rv << 1.0, 4.0, 9.0;
  VectorView<const Matrix<double,1,Dynamic> > rv_VectorView(rv);
  EXPECT_FLOAT_EQ(1.0,rv_VectorView[0]);
  EXPECT_FLOAT_EQ(4.0,rv_VectorView[1]);
  EXPECT_FLOAT_EQ(9.0,rv_VectorView[2]);

  Matrix<double,Dynamic,Dynamic> m(2,3);
  m << 1.0, 2.0, 3.0, -100.0, -200.0, -300.0;
  VectorView<const Matrix<double,Dynamic,Dynamic> > m_VectorView(m);
  int pos = 0;
  for (int j = 0; j < 3; ++j) {
    for (int i = 0; i < 2; ++i) {
      EXPECT_FLOAT_EQ(m(i,j),m_VectorView[pos]);
      ++pos;
    }
  }
}

TEST(MetaTraits,containsFvar) {
  using stan::agrad::var;
  using stan::agrad::fvar;
  using stan::contains_fvar;
  EXPECT_FALSE(contains_fvar<double>::value);
  EXPECT_FALSE(contains_fvar<var>::value);
  EXPECT_FALSE(contains_fvar<std::vector<var> >::value);
  EXPECT_FALSE((contains_fvar<double,int,var>::value));
  EXPECT_TRUE((contains_fvar<fvar<double> >::value));
  EXPECT_TRUE((contains_fvar<double, fvar<double> >::value));
  EXPECT_TRUE((contains_fvar<double, fvar<var>, int >::value));
  EXPECT_TRUE((contains_fvar<fvar<double>, fvar<var> >::value));
  EXPECT_TRUE((contains_fvar<fvar<fvar<double> > >::value));
}
TEST(MetaTraits, partials_type) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::partials_type;

  stan::partials_type<fvar<double> >::type a(2.0);
  EXPECT_EQ(2.0,a);
  stan::partials_type<fvar<double> >::type b(4.0);
  EXPECT_EQ(4.0,b);
  stan::partials_type<fvar<fvar<double> > >::type c(7.0,1.0);
  EXPECT_EQ(7.0,c.val_);
  EXPECT_EQ(1.0,c.d_);
  stan::partials_type<fvar<fvar<var> > >::type d(7.0,1.0);
  EXPECT_EQ(7.0,d.val_.val());
  EXPECT_EQ(1.0,d.d_.val());
  stan::partials_type<fvar<var> >::type e(2.0);
  EXPECT_EQ(2.0,e.val());
  stan::partials_type<var>::type f(2.0);
  EXPECT_EQ(2.0,f);
}
TEST(MetaTraits, partials_return_type) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::partials_return_type;

  partials_return_type<double,fvar<double>, std::vector<fvar<double> > >::type a(5.0);
  EXPECT_EQ(5.0,a);

  partials_return_type<double,fvar<fvar<double> > >::type b(3.0,2.0);
  EXPECT_EQ(3.0,b.val_);
  EXPECT_EQ(2.0,b.d_);

  partials_return_type<double,fvar<fvar<var> > >::type c(3.0,2.0);
  EXPECT_EQ(3.0,c.val_.val());
  EXPECT_EQ(2.0,c.d_.val());

  partials_return_type<double,double,var,fvar<fvar<var> > >::type d(3.0,2.0);
  EXPECT_EQ(3.0,d.val_.val());
  EXPECT_EQ(2.0,d.d_.val());

  partials_return_type<double,double, fvar<fvar<double> >, fvar<fvar<double> > >::type e(3.0,2.0);
  EXPECT_EQ(3.0,e.val_);
  EXPECT_EQ(2.0,e.d_);

  partials_return_type<double,stan::agrad::var>::type f(5.0);
  EXPECT_EQ(5.0,f);

  partials_return_type<double,stan::agrad::var,std::vector<stan::agrad::var> >::type g(5.0);
  EXPECT_EQ(5.0,g);
}
