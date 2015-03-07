#ifndef STAN__MATH__PRIM__MAT__FUN__EIGENVALUES_SYM_HPP
#define STAN__MATH__PRIM__MAT__FUN__EIGENVALUES_SYM_HPP

#include <stan/math/prim/scal/err/check_nonzero_size.hpp>
#include <stan/math/prim/mat/err/check_symmetric.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>

namespace stan {
  namespace math {

    /**
     * Return the eigenvalues of the specified symmetric matrix
     * in descending order of magnitude.  This function is more
     * efficient than the general eigenvalues function for symmetric
     * matrices.
     * <p>See <code>eigen_decompose()</code> for more information.
     * @param m Specified matrix.
     * @return Eigenvalues of matrix.
     */
    template <typename T>
    Eigen::Matrix<T,Eigen::Dynamic,1>
    eigenvalues_sym(const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& m) {
      stan::math::check_nonzero_size("eigenvalues_sym", "m", m);
      stan::math::check_symmetric("eigenvalues_sym", "m", m);

      Eigen::SelfAdjointEigenSolver<Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> >
        solver(m,Eigen::EigenvaluesOnly);
      return solver.eigenvalues();
    }

  }
}
#endif
