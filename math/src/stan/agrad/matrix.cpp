#ifndef __STAN__AGRAD__MATRIX_CPP__
#define __STAN__AGRAD__MATRIX_CPP__

#include "stan/agrad/matrix.hpp"

namespace stan {

  namespace agrad {


    // vector_v eigenvalues_sym(const matrix_v& m) {
    //   stan::math::validate_nonzero_size(m,"eigenvalues_sym");
    //   stan::math::validate_square(m,"eigenvalues_sym");
    //   Eigen::SelfAdjointEigenSolver<matrix_v> solver(m,Eigen::EigenvaluesOnly);
    //   return solver.eigenvalues();
    // }

    // matrix_v eigenvectors_sym(const matrix_v& m) {
    //   stan::math::validate_nonzero_size(m,"eigenvectors_sym");
    //   stan::math::validate_square(m,"eigenvectors_sym");
    //   Eigen::SelfAdjointEigenSolver<matrix_v> solver(m);
    //   return solver.eigenvectors();
    // }

    // void eigen_decompose_sym(const matrix_v& m,
    //                          vector_v& eigenvalues,
    //                          matrix_v& eigenvectors) {
    //   Eigen::SelfAdjointEigenSolver<matrix_v> solver(m);
    //   eigenvalues = solver.eigenvalues();
    //   eigenvectors = solver.eigenvectors();
    // }

    matrix_v cholesky_decompose(const matrix_v& m) {
      stan::math::validate_square(m,"cholesky decomposition");
      Eigen::LLT<matrix_v> llt(m.rows());
      llt.compute(m);
      return llt.matrixL();
    }

    vector_v singular_values(const matrix_v& m) {
      Eigen::JacobiSVD<matrix_v> svd(m); // no U or V
      return svd.singularValues();
    }      

    void svd(const matrix_v& m,
             matrix_v& u,
             matrix_v& v,
             vector_v& s) {
      static const unsigned int THIN_SVD_OPTIONS
        = Eigen::ComputeThinU | Eigen::ComputeThinV;
      Eigen::JacobiSVD<matrix_v> svd(m, THIN_SVD_OPTIONS);
      u = svd.matrixU();
      v = svd.matrixV();
      s = svd.singularValues();
    }

    void stan_print(std::ostream* o, const var& x) {
      *o << x.val();
    }


  }

}

#endif
