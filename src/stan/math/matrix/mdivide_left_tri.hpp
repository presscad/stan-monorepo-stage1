#ifndef __STAN__MATH__MATRIX__MDIVIDE_LEFT_TRI_HPP__
#define __STAN__MATH__MATRIX__MDIVIDE_LEFT_TRI_HPP__

#include <stan/math/matrix.hpp>

namespace stan {
  namespace math {

    /**
     * Returns the solution of the system Ax=b when A is triangular
     * @param A Triangular matrix.  Specify upper or lower with TriView
     * being Eigen::Upper or Eigen::Lower.
     * @param b Right hand side matrix or vector.
     * @return x = A^-1 b, solution of the linear system.
     * @throws std::domain_error if A is not square or the rows of b don't
     * match the size of A.
     */
    template <int TriView, typename T1, typename T2, 
              int R1, int C1, int R2, int C2>
    inline
    Eigen::Matrix<typename boost::math::tools::promote_args<T1,T2>::type,
                  R1,C2>
    mdivide_left_tri(const Eigen::Matrix<T1,R1,C1> &A,
                     const Eigen::Matrix<T2,R2,C2> &b) {
      stan::math::validate_square(A,"mdivide_left_tri");
      stan::math::validate_multiplicable(A,b,"mdivide_left_tri");
      return promote_common<Eigen::Matrix<T1,R1,C1>,Eigen::Matrix<T2,R1,C1> >(A)
        .template triangularView<TriView>()
        .solve( promote_common<Eigen::Matrix<T1,R2,C2>,
                               Eigen::Matrix<T2,R2,C2> >(b) );
    }
    
    /**
     * Returns the solution of the system Ax=b when A is triangular and b=I.
     * @param A Triangular matrix.  Specify upper or lower with TriView
     * being Eigen::Upper or Eigen::Lower.
     * @return x = A^-1 .
     * @throws std::domain_error if A is not square
     */
    template<int TriView, typename T,int R1, int C1>
    inline 
    Eigen::Matrix<T,R1,C1> 
    mdivide_left_tri(const Eigen::Matrix<T,R1,C1> &A) {
      stan::math::validate_square(A,"mdivide_left_tri");
      int n = A.rows();
      Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> b;
      b.setIdentity(n,n);
      A.template triangularView<TriView>().solveInPlace(b);
      return b;
    }

  }
}
#endif
