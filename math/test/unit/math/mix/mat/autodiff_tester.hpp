#ifndef TEST_UNIT_MATH_MIX_MAT_AUTODIFF_TESTER_HPP
#define TEST_UNIT_MATH_MIX_MAT_AUTODIFF_TESTER_HPP

#include <stan/math/mix/mat.hpp>
#include <test/unit/math/mix/mat/seq_reader.hpp>
#include <test/unit/math/mix/mat/seq_writer.hpp>
#include <gtest/gtest.h>
#include <stdexcept>

namespace stan {
  namespace math {
    namespace test {

      template <typename T, int R, int C>
      void expect_float_eq(const Eigen::Matrix<T, R, C>& x1,
                           const Eigen::Matrix<T, R, C>& x2) {
        EXPECT_EQ(x1.rows(), x2.rows());
        EXPECT_EQ(x1.cols(), x2.cols());
        for (int i = 0; i < x1.size(); ++i)
          EXPECT_FLOAT_EQ(x1(i), x2(i));
      }

      template <typename F>
      void test_value(const F& f, const Eigen::VectorXd& x, double fx) {
        EXPECT_FLOAT_EQ(fx, f(x));
      }

      // var
      template <typename F>
      void test_gradient(const F& f, const Eigen::VectorXd& x, double fx) {
        Eigen::VectorXd grad_ad;
        double fx_ad;
        gradient(f, x, fx_ad, grad_ad);
        EXPECT_EQ(fx, fx_ad);

        Eigen::VectorXd grad_fd;
        double fx_fd;
        finite_diff_gradient(f, x, fx_fd, grad_fd);
        expect_float_eq(grad_fd, grad_ad);
      }

      // var
      template <typename F>
      void test_gradient_fvar(const F& f, const Eigen::VectorXd& x, double fx) {
        Eigen::VectorXd grad_ad;
        double fx_ad;
        gradient<double, F>(f, x, fx_ad, grad_ad);
        EXPECT_EQ(fx, fx_ad);

        Eigen::VectorXd grad_fd;
        double fx_fd;
        finite_diff_gradient(f, x, fx_fd, grad_fd);
        expect_float_eq(grad_fd, grad_ad);
      }

      // fvar<fvar<double>>
      template <typename F>
      void test_hessian_fvar(const F& f, const Eigen::VectorXd& x, double fx) {
        double fx_ad;
        Eigen::VectorXd grad_ad;
        Eigen::MatrixXd H_ad;
        hessian<double, F>(f, x, fx_ad, grad_ad, H_ad);
        EXPECT_FLOAT_EQ(fx, fx_ad);

        double fx_fd;
        Eigen::VectorXd grad_fd;
        Eigen::MatrixXd H_fd;
        finite_diff_hessian(f, x, fx_fd, grad_fd, H_fd);
        expect_float_eq(grad_fd, grad_ad);
        expect_float_eq(H_fd, H_ad);
      }

      // fvar<var>
      template <typename F>
      void test_hessian(const F& f, const Eigen::VectorXd& x, double fx) {
        double fx_ad;
        Eigen::VectorXd grad_ad;
        Eigen::MatrixXd H_ad;
        hessian(f, x, fx_ad, grad_ad, H_ad);
        EXPECT_FLOAT_EQ(fx, fx_ad);

        double fx_fd;
        Eigen::VectorXd grad_fd;
        Eigen::MatrixXd H_fd;
        finite_diff_hessian(f, x, fx_fd, grad_fd, H_fd);
        expect_float_eq(grad_fd, grad_ad);
        expect_float_eq(H_fd, H_ad);
      }

      // fvar<fvar<var>>
      template <typename F>
      void test_grad_hessian(const F& f, const Eigen::VectorXd& x, double fx) {
        double fx_ad;
        Eigen::MatrixXd H_ad;
        std::vector<Eigen::MatrixXd> grad_H_ad;
        grad_hessian(f, x, fx_ad, H_ad, grad_H_ad);
        EXPECT_FLOAT_EQ(fx, fx_ad);

        double fx_fd;
        Eigen::MatrixXd H_fd;
        std::vector<Eigen::MatrixXd> grad_H_fd;
        grad_hessian(f, x, fx_fd, H_fd, grad_H_fd);
        expect_float_eq(H_fd, H_ad);
        EXPECT_EQ(x.size(), grad_H_fd.size());
        for (size_t i = 0; i < grad_H_fd.size(); ++i)
          expect_float_eq(grad_H_fd[i], grad_H_ad[i]);
      }

      template <typename F>
      void test_functor(const F& f, const Eigen::VectorXd& x, double fx) {
        // test_value(f, x, fx);
        test_gradient(f, x, fx);
        // test_gradient_fvar(f, x, fx);
        // test_hessian(f, x, fx);
        // test_hessian_fvar(f, x, fx);
        // test_grad_hessian(f, x, fx);
      }

      template <typename F>
      struct ad_tester {
        const F& f_;
        std::vector<Eigen::VectorXd> xs_;
        std::vector<double> fxs_;
        std::vector<Eigen::VectorXd> xs_bad_;
        std::vector<std::string> msgs_bad_;
        ad_tester(const F& f) : f_(f) { }
        void good(const Eigen::VectorXd x, double fx) {
          xs_.push_back(x);
          fxs_.push_back(fx);
        }
        void bad(const Eigen::VectorXd& x, const std::string& msg = "") {
          xs_bad_.push_back(x);
          msgs_bad_.push_back(msg);
        }
        void test() {
          for (size_t i = 0; i < xs_.size(); ++i)
            test_functor(f_, xs_[i], fxs_[i]);
          for (size_t i = 0; i < xs_bad_.size(); ++i) {
            try {
              f_(xs_bad_[i]);
            } catch (const std::exception& e) {
              std::cout << "msg = " << e.what() << std::endl;
              EXPECT_TRUE(std::string(e.what()).find(msgs_bad_[i])
                          != std::string::npos);
              continue;
            }
            FAIL() << "expected throw, didn't get it";
          }
        }
      };

      struct multiply_fun {
        template <typename T1, typename T2>
        static typename boost::math::tools::promote_args<T1,T2>::type
        apply(const Eigen::Matrix<T1, 1, -1>& x1,
              const Eigen::Matrix<T2, -1, 1>& x2) {
          return multiply(x1, x2);
        }
      };

      // any two args, real return
      template <typename F, typename T1, typename T2>
      struct binder_binary {
        T1 x1_;
        T2 x2_;
        bool fixed1_;
        bool fixed2_;
        binder_binary(const T1& x1, const T2& x2)
          : x1_(x1), x2_(x2), fixed1_(false), fixed2_(false) { }
        template <typename T>
        T operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
          if (fixed1_ && !fixed2_) {
            seq_reader<T> r(theta);
            return F::apply(x1_, r.read(x2_));
          }

          if (!fixed1_ && fixed2_) {
            seq_reader<T> r(theta);
            return F::apply(r.read(x1_), x2_);
          }

          if (!fixed1_ && !fixed2_) {
            seq_reader<T> r(theta);
            return F::apply(r.read(x1_), r.read(x2_));
          }

          throw std::logic_error("fixed1_ = true and fixed2_ = true illegal");
          return T();
        }
      };

      template <typename F, typename T1, typename T2>
      struct ad_tester_binary {
        std::vector<T1> x1s_;
        std::vector<T2> x2s_;
        std::vector<double> fxs_;

        void good(const T1& x1, const T2& x2, double fx) {
          x1s_.push_back(x1);
          x2s_.push_back(x2);
          fxs_.push_back(fx);
        }

        void test(const T1& x1, const T2& x2, double fx) {
          binder_binary<F, T1, T2> f(x1, x2);

          f.fixed1_ = true;
          f.fixed2_ = false;
          seq_writer<double> a;
          a.write(x2);
          test_functor(f, a.vector(), fx);

          f.fixed1_ = false;
          f.fixed2_ = true;
          seq_writer<double> b;
          b.write(x1);
          test_functor(f, b.vector(), fx);

          f.fixed1_ = false;
          f.fixed2_ = false;
          seq_writer<double> c;
          c.write(x1);
          c.write(x2);
          test_functor(f, c.vector(), fx);
        }

        void run_tests() {
          for (size_t i = 0; i < x1s_.size(); ++i)
            test(x1s_[i], x2s_[i], fxs_[i]);
        }

      };


    }
  }
}

#endif
