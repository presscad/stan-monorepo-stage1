#ifndef STAN_MATH_REV_MAT_FUN_CHOLESKY_DECOMPOSE_HPP
#define STAN_MATH_REV_MAT_FUN_CHOLESKY_DECOMPOSE_HPP

#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/math/prim/mat/fun/typedefs.hpp>
#include <stan/math/prim/mat/fun/cholesky_decompose.hpp>
#include <stan/math/rev/scal/fun/value_of_rec.hpp>
#include <stan/math/rev/scal/fun/value_of.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/prim/mat/fun/value_of_rec.hpp>
#include <stan/math/prim/mat/err/check_pos_definite.hpp>
#include <stan/math/prim/mat/err/check_square.hpp>
#include <stan/math/prim/mat/err/check_symmetric.hpp>

namespace stan {
  namespace math {

    class cholesky_decompose_v_vari : public vari {
    public:
      int M_;  // A.rows() = A.cols()
      int block_size_;
      typedef Eigen::Block<Eigen::MatrixXd> Block_;
      vari** variRefA_;
      vari** variRefL_;

      /* Constructor for cholesky function
       *
       * Stores varis for A
       * Instantiates and stores varis for L
       * Instantiates and stores dummy vari for
       * upper triangular part of var result returned
       * in cholesky_decompose function call
       *
       * variRefL aren't on the chainable
       * autodiff stack, only used for storage
       * and computation. Note that varis for
       * L are constructed externally in
       * cholesky_decompose.
       *
       * block_size_ determined using the same
       * calculation Eigen/LLT.h 
       *
       * @param matrix A
       * @param matrix L, cholesky factor of A
       * */
      cholesky_decompose_v_vari(const Eigen::Matrix<var, -1, -1>& A,
                                const Eigen::Matrix<double, -1, -1>& L_A)
        : vari(0.0),
          M_(A.rows()),
          variRefA_(ChainableStack::memalloc_.alloc_array<vari*>
                    (A.rows() * (A.rows() + 1) / 2)),
          variRefL_(ChainableStack::memalloc_.alloc_array<vari*>
                    (A.rows() * (A.rows() + 1) / 2)) {
            size_t pos = 0;
         block_size_ = M_/8;
         block_size_ = (block_size_/16)*16;
         block_size_ = (std::min)((std::max)(block_size_,8), 128);
        for (size_type j = 0; j < M_; ++j) {
          for (size_type i = j; i < M_; ++i) {
            variRefA_[pos] = A.coeffRef(i, j).vi_;
            variRefL_[pos] = new vari(L_A.coeffRef(i, j), false);
            ++pos;
          }
        }
      }

      inline void symbolic_rev(Block_& L,
                               Block_& Lbar,
                               int size) {

        using Eigen::Lower;
        using Eigen::Upper;
        using Eigen::StrictlyUpper;
        L.transposeInPlace();
        Lbar = (L * Lbar.triangularView<Lower>()).eval();
        Lbar.triangularView<StrictlyUpper>()
          = Lbar.adjoint().triangularView<StrictlyUpper>();
        L.triangularView<Upper>().solveInPlace(Lbar);
        L.triangularView<Upper>().solveInPlace(Lbar.transpose());
      }

      /* Reverse mode differentiation
       * algorithm refernce:
       *
       * Iain Murray: Differentiation of 
       * the Cholesky decomposition, 2016.
       *
       * */
      virtual void chain() {
        using Eigen::MatrixXd;
        using Eigen::Lower;
        using Eigen::Block;
        using Eigen::Upper;
        using Eigen::StrictlyUpper;
        MatrixXd Lbar(M_, M_);
        MatrixXd L(M_, M_);

        Lbar.setZero();
        L.setZero();
        size_t pos = 0;
        for (size_type j = 0; j < M_; ++j) {
          for (size_type i = j; i < M_; ++i) {
            Lbar.coeffRef(i, j) = variRefL_[pos]->adj_;
            L.coeffRef(i, j) = variRefL_[pos]->val_;
            ++pos;
          }
        }

        for (int k = M_; k > 0; k -= block_size_) {
          int j = std::max(0, k - block_size_);
          Block_ R = L.block(j, 0, k - j, j);
          Block_ D = L.block(j, j, k - j, k - j);
          Block_ B = L.block(k, 0, M_ - k, j);
          Block_ C = L.block(k, j, M_ - k, k - j);
          Block_ Rbar = Lbar.block(j, 0, k - j, j);
          Block_ Dbar = Lbar.block(j, j, k - j, k - j);
          Block_ Bbar = Lbar.block(k, 0, M_ - k, j);
          Block_ Cbar = Lbar.block(k, j, M_ - k, k - j);
          if (Cbar.size() > 0) {
            Cbar 
              = D.transpose().triangularView<Upper>()
              .solve(Cbar.transpose()).transpose();
            Bbar.noalias() -= Cbar * R;
            Dbar.noalias() -= Cbar.transpose() * C;
          }
          symbolic_rev(D, Dbar, D.rows());
          Rbar.noalias() -= Cbar.transpose() * B;
          Rbar.noalias() -= Dbar.selfadjointView<Lower>() * R;
          Dbar.diagonal().array() *= 0.5;
          Dbar.triangularView<StrictlyUpper>().setZero();
        }
        pos = 0;
        for (size_type j = 0; j < M_; ++j)
          for (size_type i = j; i < M_; ++i) 
            variRefA_[pos++]->adj_ += Lbar.coeffRef(i,j);
      }
    };

    /* Reverse mode specialization of
     * cholesky decomposition
     *
     * Internally calls llt rather than using
     * cholesky_decompose in order
     * to use selfadjointView<Lower> optimization.
     *
     * TODO(rtrangucci): Use Eigen 3.3 inplace Cholesky
     * when possible
     *
     * Note chainable stack varis are created
     * below in Matrix<var, -1, -1>
     *
     * @param Matrix A
     * @return L cholesky factor of A
     */
    inline Eigen::Matrix<var, -1, -1>
      cholesky_decompose(const Eigen::Matrix<var, -1, -1> &A) {
      check_square("cholesky_decompose", "A", A);
      check_symmetric("cholesky_decompose", "A", A);

      Eigen::Matrix<double, -1, -1> L_A(value_of_rec(A));
      Eigen::LLT<Eigen::MatrixXd> L_factor
        = L_A.selfadjointView<Eigen::Lower>().llt();
      check_pos_definite("cholesky_decompose", "m", L_factor);
      L_A = L_factor.matrixL();

      // Memory allocated in arena. 
      cholesky_decompose_v_vari *baseVari
        = new cholesky_decompose_v_vari(A, L_A);
      vari dummy(0.0, false);
      Eigen::Matrix<var, -1, -1> L(A.rows(), A.cols());
      size_t pos = 0;
      for (size_type j = 0; j < L.cols(); ++j) {
        for (size_type i = j; i < L.cols(); ++i) {
          L.coeffRef(i, j).vi_ = baseVari->variRefL_[pos++];
        }
        for (size_type k = 0; k < j; ++k)
          L.coeffRef(k, j).vi_ = &dummy;
      }
      return L;
    }

  }
}
#endif
