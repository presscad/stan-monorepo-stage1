#ifndef __STAN__AGRAD__REV__MATRIX__LDLT_FACTOR_HPP__
#define __STAN__AGRAD__REV__MATRIX__LDLT_FACTOR_HPP__

#include <stan/agrad/rev/var.hpp>
#include <stan/math/matrix/validate_square.hpp>
#include <stan/agrad/rev/matrix/LDLT_alloc.hpp>
#include <stan/math/matrix/LDLT_factor.hpp>

namespace stan {
  namespace math {
    /**
     * A template specialization of src/stan/math/matrix/LDLT_factor.hpp for
     * stan::agrad::var which can be used with all the *_ldlt functions.
     *
     * The usage pattern is:
     *
     * ~~~
     * Eigen::Matrix<T,R,C> A1, A2;
     *
     * LDLT_factor<T,R,C> ldlt_A1(A1);
     * LDLT_factor<T,R,C> ldlt_A2;
     * ldlt_A2.compute(A2);
     * ~~~
     *
     * Now, the caller should check that ldlt_A1.success() and ldlt_A2.success()
     * are true or abort accordingly.  Alternatively, call check_ldlt_factor().
     * The behaviour of using an LDLT_factor without checking success() is
     * undefined.
     *
     * Note that ldlt_A1 and ldlt_A2 are completely equivalent.  They simply 
     * demonstrate two different ways to construct the factorization.
     *
     * Now, the caller can use the LDLT_factor objects as needed.  For instance
     *
     * ~~~
     * x1 = mdivide_left_ldlt(ldlt_A1,b1);
     * x2 = mdivide_right_ldlt(b2,ldlt_A2);
     *
     * d1 = log_determinant_ldlt(ldlt_A1);
     * d2 = log_determinant_ldlt(ldlt_A2);
     * ~~~
     * 
     **/
    template<int R, int C>
    class LDLT_factor<stan::agrad::var,R,C> {
    public:
      /**
       * Default constructor.  The caller *MUST* call compute() after this.  Any
       * calls which use the LDLT_factor without calling compute() run the risk
       * of crashing Stan from within Eigen.
       **/
      LDLT_factor() : _alloc(new stan::agrad::LDLT_alloc<R,C>()) {}

      LDLT_factor(const Eigen::Matrix<stan::agrad::var,R,C> &A)
      : _alloc(new stan::agrad::LDLT_alloc<R,C>()) {
        compute(A);
      }
     
      /**
       * Use the LDLT_factor object to factorize a new matrix.  After calling
       * this function, the user should call success() to check that the
       * factorization was successful.
       *
       * @param A A symmetric positive definite matrix to factorize
       **/
      inline void compute(const Eigen::Matrix<stan::agrad::var,R,C> &A) {
        stan::math::validate_square(A,"LDLT_factor<var>::compute");
        _alloc->compute(A);
      }
      
      /**
       * Compute the actual numerical result of inv(A)*b.  Note that this isn't
       * meant to handle any of the autodiff.  This is a convenience function
       * for the actual implementations in mdivide_left_ldlt.
       *
       * @param b The right handside.  Note that this is templated such that
       * Eigen's expression-templating magic can work properly here.
       **/
      template<typename Rhs>
      inline const Eigen::internal::solve_retval<Eigen::LDLT< Eigen::Matrix<double,R,C> >, Rhs>
      solve(const Eigen::MatrixBase<Rhs>& b) const {
        return _alloc->_ldlt.solve(b);
      }
      
      /**
       * Determine whether the most recent factorization succeeded.  This should
       * always be called after the object is constructed (with a matrix) or
       * after compute() is called.
       **/
      inline bool success() const {
        bool ret;
        ret = _alloc->N_ != 0;
        ret = ret && _alloc->_ldlt.info() == Eigen::Success;
        ret = ret && _alloc->_ldlt.isPositive();
        ret = ret && (_alloc->_ldlt.vectorD().array() > 0).all();
        return ret;
      }

      /**
       * The entries of the diagonal matrix D.  They should be strictly positive
       * for a positive definite matrix.
       **/
      inline Eigen::VectorXd vectorD() const {
        return _alloc->_ldlt.vectorD();
      }

      inline size_t rows() const { return _alloc->N_; }
      inline size_t cols() const { return _alloc->N_; }
      
      typedef size_t size_type;

      /**
       * The LDLT_alloc object actually contains the factorization but is
       * derived from the chainable_alloc class so that it is allocated on the
       * vari stack.  This ensures that it's lifespan is longer than the
       * LDLT_factor object which created it.  This is needed because the
       * factorization is required during the chain() calls which happen
       * after an LDLT_factor object will most likely have been destroyed.
       **/
      stan::agrad::LDLT_alloc<R,C> *_alloc;
    };
  }
}
#endif
