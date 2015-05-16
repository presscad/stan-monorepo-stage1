#include <iostream>
#include <vector>
#include <stan/model/indexing/rvalue.hpp>
#include <gtest/gtest.h>

using stan::model::nil_index_list;
using stan::model::cons_index_list;
using stan::model::index_uni;
using stan::model::index_multi;
using stan::model::index_omni;
using stan::model::index_min;
using stan::model::index_max;
using stan::model::index_min_max;

TEST(ModelIndexing, rvalue_vector_nil) {
  std::vector<double> x;
  x.push_back(1.1);
  x.push_back(2.2);

  std::vector<double> rx = rvalue(x, nil_index_list());
  EXPECT_EQ(2,rx.size());
  EXPECT_FLOAT_EQ(1.1, rx[0]);
  EXPECT_FLOAT_EQ(2.2, rx[1]);
}
TEST(ModelIndexing, rvalue_vector_uni_nil) {
  std::vector<double> x;
  x.push_back(1.1);
  x.push_back(2.2);
  x.push_back(3.3);

  for (size_t k = 0; k < x.size(); ++k)
    EXPECT_EQ(x[k], rvalue(x, index_list(index_uni(k))));
}
TEST(ModelIndexing, rvalue_vector_multi_nil) {
  std::vector<double> x;
  x.push_back(1.1);
  x.push_back(2.2);
  x.push_back(3.3);
  x.push_back(4.4);
  x.push_back(5.5);
  x.push_back(6.6);

  std::vector<int> idxs;
  idxs.push_back(0);
  idxs.push_back(3);
  idxs.push_back(4);
  
  std::vector<double> rx = rvalue(x, index_list(index_multi(idxs)));
  EXPECT_FLOAT_EQ(3, rx.size());
  EXPECT_FLOAT_EQ(x[0], rx[0]);
  EXPECT_FLOAT_EQ(x[3], rx[1]);
  EXPECT_FLOAT_EQ(x[4], rx[2]);
}
TEST(ModelIndexing, rvalue_vector_omni_nil) {
  std::vector<double> x;
  x.push_back(1.1);
  x.push_back(2.2);
  x.push_back(3.3);

  std::vector<double> rx = rvalue(x, index_list(index_omni()));
  EXPECT_FLOAT_EQ(3, rx.size());
  for (size_t n = 0; n < rx.size(); ++n)
    EXPECT_FLOAT_EQ(x[n], rx[n]);
}
TEST(ModelIndexing, rvalue_vector_min_nil) {
  std::vector<double> x;
  x.push_back(1.1);
  x.push_back(2.2);
  x.push_back(3.3);

  for (int k = 0; k < 4; ++k) {
    std::vector<double> rx = rvalue(x, index_list(index_min(k)));
    EXPECT_FLOAT_EQ(3 - k, rx.size());
    for (size_t n = 0; n < rx.size(); ++n)
      EXPECT_FLOAT_EQ(x[n + k], rx[n]);
  }
}
TEST(ModelIndexing, rvalue_vector_max_nil) {
  std::vector<double> x;
  x.push_back(1.1);
  x.push_back(2.2);
  x.push_back(3.3);

  for (int k = 0; k < 3; ++k) {
    std::vector<double> rx = rvalue(x, index_list(index_max(k)));
    EXPECT_FLOAT_EQ(k + 1, rx.size());
    for (size_t n = 0; n < rx.size(); ++n)
      EXPECT_FLOAT_EQ(x[n], rx[n]);
  }
}
TEST(ModelIndexing, rvalue_vector_min_max_nil) {
  std::vector<double> x;
  x.push_back(1.1);
  x.push_back(2.2);
  x.push_back(3.3);
  x.push_back(4.4);

  for (int mn = 0; mn < 4; ++mn) {
    for (int mx = mn; mx < 4; ++mx) {
      std::vector<double> rx = rvalue(x, index_list(index_min_max(mn, mx)));
      EXPECT_FLOAT_EQ(mx - mn + 1, rx.size());
      for (int n = mn; n <= mx; ++n)
        EXPECT_FLOAT_EQ(x[n], rx[n - mn]);
    }
  }
}

TEST(ModelIndexing, rvalue_doubless_uni_uni) {
  using std::vector;
  
  vector<double> x0;
  x0.push_back(0.0);
  x0.push_back(0.1);

  vector<double> x1;
  x1.push_back(1.0);
  x1.push_back(1.1);

  vector<vector<double> > x;
  x.push_back(x0);
  x.push_back(x1);
  
  for (int m = 0; m < 2; ++m)
    for (int n = 0; n < 2; ++n)
      EXPECT_FLOAT_EQ(m + n / 10.0, 
                      rvalue(x, index_list(index_uni(m), index_uni(n))));
}

TEST(ModelIndexing, rvalue_doubless_uni_multi) {
  using std::vector;
  
  vector<double> x0;
  x0.push_back(0.0);
  x0.push_back(0.1);
  x0.push_back(0.2);

  vector<double> x1;
  x1.push_back(1.0);
  x1.push_back(1.1);
  x1.push_back(1.2);

  vector<double> x2;
  x2.push_back(2.0);
  x2.push_back(2.1);
  x2.push_back(2.2);

  vector<vector<double> > x;
  x.push_back(x0);
  x.push_back(x1);
  x.push_back(x2);

  vector<double> y = rvalue(x, index_list(index_uni(0), index_min(1)));
  EXPECT_EQ(2, y.size());
  EXPECT_FLOAT_EQ(0.1, y[0]);
  EXPECT_FLOAT_EQ(0.2, y[1]);

  y = rvalue(x, index_list(index_uni(1), index_max(1)));
  EXPECT_EQ(2, y.size());
  EXPECT_FLOAT_EQ(1.0, y[0]);
  EXPECT_FLOAT_EQ(1.1, y[1]);

  y = rvalue(x, index_list(index_uni(1), index_min_max(1,2)));
  EXPECT_EQ(2, y.size());
  EXPECT_FLOAT_EQ(1.1, y[0]);
  EXPECT_FLOAT_EQ(1.2, y[1]);

  y = rvalue(x, index_list(index_uni(1), index_min_max(1,1)));
  EXPECT_EQ(1, y.size());
  EXPECT_FLOAT_EQ(1.1, y[0]);

  y = rvalue(x, index_list(index_uni(2), index_omni()));
  EXPECT_EQ(3, y.size());
  EXPECT_FLOAT_EQ(2.0, y[0]);
  EXPECT_FLOAT_EQ(2.1, y[1]);
  EXPECT_FLOAT_EQ(2.2, y[2]);

  vector<int> ns;
  ns.push_back(2);
  ns.push_back(0);
  y = rvalue(x, index_list(index_uni(0), index_multi(ns)));
  EXPECT_EQ(2, y.size());
  EXPECT_FLOAT_EQ(0.2, y[0]);
  EXPECT_FLOAT_EQ(0.0, y[1]);
}


TEST(ModelIndexing, rvalue_doubless_multi_uni) {
  using std::vector;
  
  vector<double> x0;
  x0.push_back(0.0);
  x0.push_back(0.1);
  x0.push_back(0.2);

  vector<double> x1;
  x1.push_back(1.0);
  x1.push_back(1.1);
  x1.push_back(1.2);

  vector<double> x2;
  x2.push_back(2.0);
  x2.push_back(2.1);
  x2.push_back(2.2);

  vector<vector<double> > x;
  x.push_back(x0);
  x.push_back(x1);
  x.push_back(x2);

  vector<double> y = rvalue(x, index_list(index_min(1), index_uni(0)));
  EXPECT_EQ(2, y.size());
  EXPECT_FLOAT_EQ(1.0, y[0]);
  EXPECT_FLOAT_EQ(2.0, y[1]);

  y = rvalue(x, index_list(index_max(1), index_uni(2)));
  EXPECT_EQ(2, y.size());
  EXPECT_FLOAT_EQ(0.2, y[0]);
  EXPECT_FLOAT_EQ(1.2, y[1]);

  y = rvalue(x, index_list(index_min_max(1,2), index_uni(1)));
  EXPECT_EQ(2, y.size());
  EXPECT_FLOAT_EQ(1.1, y[0]);
  EXPECT_FLOAT_EQ(2.1, y[1]);

  y = rvalue(x, index_list(index_min_max(1,1), index_uni(1)));
  EXPECT_EQ(1, y.size());
  EXPECT_FLOAT_EQ(1.1, y[0]);

  y = rvalue(x, index_list(index_omni(), index_uni(2)));
  EXPECT_EQ(3, y.size());
  EXPECT_FLOAT_EQ(0.2, y[0]);
  EXPECT_FLOAT_EQ(1.2, y[1]);
  EXPECT_FLOAT_EQ(2.2, y[2]);

  vector<int> ns;
  ns.push_back(2);
  ns.push_back(0);
  y = rvalue(x, index_list(index_multi(ns), index_uni(0)));
  EXPECT_EQ(2, y.size());
  EXPECT_FLOAT_EQ(2.0, y[0]);
  EXPECT_FLOAT_EQ(0.0, y[1]);
}

TEST(ModelIndexing, rvalue_doubless_multi_multi) {
  using std::vector;
  
  vector<double> x0;
  x0.push_back(0.0);
  x0.push_back(0.1);
  x0.push_back(0.2);

  vector<double> x1;
  x1.push_back(1.0);
  x1.push_back(1.1);
  x1.push_back(1.2);

  vector<double> x2;
  x2.push_back(2.0);
  x2.push_back(2.1);
  x2.push_back(2.2);

  vector<vector<double> > x;
  x.push_back(x0);
  x.push_back(x1);
  x.push_back(x2);

  vector<vector<double> > y = rvalue(x, index_list(index_max(1), index_min(1)));
  EXPECT_EQ(2, y.size());
  EXPECT_EQ(2, y[0].size());
  EXPECT_EQ(2, y[1].size());
  EXPECT_FLOAT_EQ(0.1, y[0][0]);
  EXPECT_FLOAT_EQ(0.2, y[0][1]);
  EXPECT_FLOAT_EQ(1.1, y[1][0]);
  EXPECT_FLOAT_EQ(1.2, y[1][1]);
}

template <typename T>
void vector_uni_test() {
  T v(3);
  v << 0, 1, 2;
  
  EXPECT_FLOAT_EQ(0, rvalue(v, index_list(index_uni(0))));
  EXPECT_FLOAT_EQ(1, rvalue(v, index_list(index_uni(1))));
  EXPECT_FLOAT_EQ(2, rvalue(v, index_list(index_uni(2))));
}
TEST(ModelIndexing, rvalueVectorUni) {
  vector_uni_test<Eigen::VectorXd>();
}
TEST(ModelIndexing, rvalueRowVectorUni) {
  vector_uni_test<Eigen::RowVectorXd>();
}

template <typename T>
void vector_multi_test() {
  T v(5);
  v << 0, 1, 2, 3, 4;
  
  T vi = rvalue(v, index_list(index_omni()));
  EXPECT_EQ(5, vi.size());
  EXPECT_FLOAT_EQ(0, vi(0));
  EXPECT_FLOAT_EQ(2, vi(2));
  EXPECT_FLOAT_EQ(4, vi(4));
  
  vi = rvalue(v, index_list(index_min(2)));
  EXPECT_EQ(3, vi.size());
  EXPECT_FLOAT_EQ(2, vi(0));
  EXPECT_FLOAT_EQ(4, vi(2));

  vi = rvalue(v, index_list(index_max(2)));
  EXPECT_EQ(3, vi.size());
  EXPECT_FLOAT_EQ(0, vi(0));
  EXPECT_FLOAT_EQ(2, vi(2));

  vi = rvalue(v, index_list(index_min_max(1,3)));
  EXPECT_EQ(3, vi.size());
  EXPECT_FLOAT_EQ(1, vi(0));
  EXPECT_FLOAT_EQ(3, vi(2));

  std::vector<int> ns;
  ns.push_back(3);
  ns.push_back(1);
  ns.push_back(1);
  ns.push_back(0);
  ns.push_back(4);
  ns.push_back(1);
  ns.push_back(3);
  
  vi = rvalue(v, index_list(index_multi(ns)));
  EXPECT_EQ(7, vi.size());
  EXPECT_FLOAT_EQ(3.0, vi(0));
  EXPECT_FLOAT_EQ(1.0, vi(2));
  EXPECT_FLOAT_EQ(4.0, vi(4));
  EXPECT_FLOAT_EQ(3.0, vi(6));
}
TEST(ModelIndexing, rvalueVectorMulti) {
  vector_multi_test<Eigen::VectorXd>();
}
TEST(ModelIndexing, rvalueRowVectorMulti) {
  vector_multi_test<Eigen::RowVectorXd>();
}

TEST(ModelIndexing, rvalueMatrixUni) {
  using Eigen::MatrixXd;
  using Eigen::RowVectorXd;
  using Eigen::VectorXd;
  
  MatrixXd m(4,3);
  m << 
    0.0, 0.1, 0.2, 
    1.0, 1.1, 1.2,
    2.0, 2.1, 2.2,
    3.0, 3.1, 3.2;
  
  RowVectorXd v = rvalue(m, index_list(index_uni(0)));
  EXPECT_EQ(3, v.size());
  EXPECT_FLOAT_EQ(0.0, v(0));
  EXPECT_FLOAT_EQ(0.1, v(1));
  EXPECT_FLOAT_EQ(0.2, v(2));

  v = rvalue(m, index_list(index_uni(1)));
  EXPECT_EQ(3, v.size());
  EXPECT_FLOAT_EQ(1.0, v(0));
  EXPECT_FLOAT_EQ(1.1, v(1));
  EXPECT_FLOAT_EQ(1.2, v(2));
}

TEST(ModelIndexing, rvalueMatrixMulti) {
  using Eigen::MatrixXd;
  using Eigen::RowVectorXd;
  using Eigen::VectorXd;
  
  MatrixXd m(4,3);
  m << 
    0.0, 0.1, 0.2, 
    1.0, 1.1, 1.2,
    2.0, 2.1, 2.2,
    3.0, 3.1, 3.2;
  
  MatrixXd a = rvalue(m, index_list(index_min(2)));
  EXPECT_EQ(2, a.rows());
  EXPECT_EQ(3, a.cols());
  EXPECT_FLOAT_EQ(2.0, a(0,0));
  EXPECT_FLOAT_EQ(2.1, a(0,1));
  EXPECT_FLOAT_EQ(2.2, a(0,2));
  EXPECT_FLOAT_EQ(3.0, a(1,0));
  EXPECT_FLOAT_EQ(3.1, a(1,1));
  EXPECT_FLOAT_EQ(3.2, a(1,2));

  a = rvalue(m, index_list(index_max(1)));
  EXPECT_EQ(2, a.rows());
  EXPECT_EQ(3, a.cols());
  EXPECT_FLOAT_EQ(0.0, a(0,0));
  EXPECT_FLOAT_EQ(0.1, a(0,1));
  EXPECT_FLOAT_EQ(0.2, a(0,2));
  EXPECT_FLOAT_EQ(1.0, a(1,0));
  EXPECT_FLOAT_EQ(1.1, a(1,1));
  EXPECT_FLOAT_EQ(1.2, a(1,2));

  a = rvalue(m, index_list(index_min_max(1,2)));
  EXPECT_EQ(2, a.rows());
  EXPECT_EQ(3, a.cols());
  EXPECT_FLOAT_EQ(1.0, a(0,0));
  EXPECT_FLOAT_EQ(1.1, a(0,1));
  EXPECT_FLOAT_EQ(1.2, a(0,2));
  EXPECT_FLOAT_EQ(2.0, a(1,0));
  EXPECT_FLOAT_EQ(2.1, a(1,1));
  EXPECT_FLOAT_EQ(2.2, a(1,2));

  a = rvalue(m, index_list(index_omni()));
  EXPECT_EQ(4, a.rows());
  EXPECT_EQ(3, a.cols());
  EXPECT_FLOAT_EQ(0.0, a(0,0));
  EXPECT_FLOAT_EQ(0.1, a(0,1));
  EXPECT_FLOAT_EQ(0.2, a(0,2));
  EXPECT_FLOAT_EQ(3.0, a(3,0));
  EXPECT_FLOAT_EQ(3.1, a(3,1));
  EXPECT_FLOAT_EQ(3.2, a(3,2));

  std::vector<int> ns;
  ns.push_back(2);
  ns.push_back(3);
  ns.push_back(0);
  ns.push_back(3);
  ns.push_back(0);
  ns.push_back(3);
  ns.push_back(0);
  a = rvalue(m, index_list(index_multi(ns)));
  EXPECT_FLOAT_EQ(7, a.rows());
  EXPECT_FLOAT_EQ(3, a.cols());
  EXPECT_FLOAT_EQ(2.0, a(0,0));
  EXPECT_FLOAT_EQ(2.1, a(0,1));
  EXPECT_FLOAT_EQ(2.2, a(0,2));
  EXPECT_FLOAT_EQ(3.0, a(5,0));
  EXPECT_FLOAT_EQ(3.1, a(5,1));
  EXPECT_FLOAT_EQ(3.2, a(5,2));
  EXPECT_FLOAT_EQ(0.0, a(6,0));
  EXPECT_FLOAT_EQ(0.1, a(6,1));
  EXPECT_FLOAT_EQ(0.2, a(6,2));
}

TEST(ModelIndexing, rvalueMatrixSingleSingle) {
  Eigen::MatrixXd x(3,4);
  x << 
    0.0, 0.1, 0.2, 0.3,
    1.0, 1.1, 1.2, 1.3,
    2.0, 2.1, 2.2, 2.3;

  for (int m = 0; m < 3; ++m)
    for (int n = 0; n < 4; ++n)
      EXPECT_FLOAT_EQ(m + n / 10.0, 
                      rvalue(x, index_list(index_uni(m), index_uni(n))));
  
}
