#ifndef STAN_MATH_REV_MAT_FUN_ADJ_JAC_APPLY_HPP
#define STAN_MATH_REV_MAT_FUN_ADJ_JAC_APPLY_HPP

#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/math/prim/mat.hpp>
#include <stan/math/rev/core.hpp>
#include <limits>
#include <vector>

namespace stan {
namespace math {

/*
 * adj_jac_vari interfaces a user supplied functor  with the reverse mode
 * autodiff. It allows someone to implement functions with custom reverse mode
 * autodiff without having to deal with autodiff types.
 *
 * The requirements on the functor F are described in the documentation for
 * adj_jac_apply
 *
 * @tparam F class of functor
 */
template <typename F>
struct adj_jac_vari : public vari {
  F f_;
  int N_;
  vari** x_vi_;
  int M_;
  vari** y_vi_;

  /**
   * The adj_jac_vari constructor
   *  1. Initializes an instance of the user defined functor F
   *  2. Calls operator() on the F instance with the double values from the
   * input x
   *  3. Saves copies of the varis pointed to by the input vars for subsequent
   * calls to chain
   *  4. Allocates varis for the output of the functor F
   *
   * @param x Input as vars
   */
  explicit adj_jac_vari(const Eigen::Matrix<var, Eigen::Dynamic, 1>& x)
      : vari(std::numeric_limits<double>::quiet_NaN()),  // The val_ in this
                                                         // vari is unused
        N_(x.size()),
        x_vi_(build_vari_array(x)) {
    Eigen::Matrix<double, Eigen::Dynamic, 1> val_x = value_of(x);
    Eigen::Matrix<double, Eigen::Dynamic, 1> val_y = f_(val_x);

    M_ = val_y.size();
    y_vi_ = ChainableStack::instance().memalloc_.alloc_array<vari*>(M_);
    for (int m = 0; m < M_; ++m) {
      y_vi_[m] = new vari(val_y(m), false);
    }
  }

  /**
   * chain propagates the adjoints at the output varis (y_vi_) back to the input
   * varis (x_vi_) by using the multiply_adjoint_jacobian function of the user
   * defined functor
   *
   * Unlike the constructor, this operation may be called multiple times during
   * the life of the vari
   */
  void chain() {
    Eigen::Matrix<double, Eigen::Dynamic, 1> y_adj(M_);
    for (int m = 0; m < M_; ++m)
      y_adj(m) = y_vi_[m]->adj_;
    Eigen::Matrix<double, Eigen::Dynamic, 1> y_adj_jac
        = f_.multiply_adjoint_jacobian(y_adj);
    for (int n = 0; n < N_; ++n)
      x_vi_[n]->adj_ += y_adj_jac(n);
  }
};

/*
 * Return the result of applying the function defined by a nullary construction
 * of F to the specified input argument
 *
 * adj_jac_apply makes it possible to write efficient reverse-mode
 * autodiff code without ever touching Stan's autodiff internals
 *
 * Mathematically, to use a function in reverse mode autodiff, you need to be
 * able to evaluate the function (y = f(x)) and multiply the Jacobian of that
 * function (df(x)/dx) by a vector.
 *
 * As an example, pretend there exists some large, complicated function, L(x),
 * which contains our smaller function f(x). The goal of autodiff is to compute
 * dL/dx. If we break the large function into pieces:
 *
 * y = f(x)
 * L = g(y)
 *
 * If we were given dL/dy we could compute dL/dx by the product dL/dy * dy/dx
 *
 * Because y = f(x), dy/dx is just df(x)/dx, the Jacobian of the function we're
 * trying to define. In vector form,
 *
 * dL/dx = (dL/dy)' * df(x)/dx
 *
 * So implementing f(x) and the product above is all that is required
 * mathematically to implement reverse-mode autodiff for a function.
 *
 * adj_jac_apply takes as a template argument a functor F that supplies the
 * non-static member functions: (required) Eigen::VectorXd operator()(const
 * Eigen::VectorXd& x), (required) Eigen::VectorXd
 * multiply_adjoint_jacobian(const Eigen::VectorXd& adj) and, (optional) a
 * nullary constructor
 *
 * operator() is responsible for computing f(x) and multiply_adjoint_jacobian is
 * responsible for computing the adjoint transpose Jacobian product (which
 * frequently does not require the calculation of the full Jacobian).
 *
 * operator() will be called before multiply_adjoint_jacobian is called, and is
 * only called once in the lifetime of the functor multiply_adjoint_jacobian is
 * called after operator() and may be called multiple times for any single
 * functor
 *
 * The functor supplied to adj_jac_apply must be careful to allocate any
 * variables it defines in the autodiff arena because its destructor will
 * never be called and memory will leak if allocated anywhere else.
 *
 * @tparam F functor to be connected to the autodiff stack
 * @param x input to the functor
 * @return the result of the specified operation wrapped up in vars
 */
template <class F>
Eigen::Matrix<var, Eigen::Dynamic, 1> adj_jac_apply(
    const Eigen::Matrix<var, Eigen::Dynamic, 1>& x) {
  adj_jac_vari<F>* vi = new adj_jac_vari<F>(x);
  Eigen::Matrix<var, Eigen::Dynamic, 1> y(vi->M_);

  for (int m = 0; m < y.size(); ++m)
    y(m) = (vi->y_vi_)[m];
  return y;
}

}  // namespace math
}  // namespace stan
#endif
