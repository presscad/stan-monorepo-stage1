#ifndef STAN_MATH_PRIM_MAT_FUN_MATRIX_EXP_HPP
#define STAN_MATH_PRIM_MAT_FUN_MATRIX_EXP_HPP

#include <unsupported/Eigen/MatrixFunctions>
#include <stan/math/prim/mat/fun/matrix_exp_spec.hpp>
#include <stan/math/prim/mat/fun/is_symmetric.hpp>

namespace stan {
    namespace math {
        
        /**
         * Return the matrix exponential.
         * @param A A matrix
         * @return Matrix exponential. 
         */
        
        template <typename T>
        inline
        Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
        expm(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> A) {
            
            check_nonzero_size("matrix_exp", "input matrix", A);
            check_square("matrix_exp", "input matrix", A);
            
            Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> B;
            
            if (A.cols() == 2) matrix_exp_compute_2x2(A, B);
            else if (is_symmetric(A)) matrix_exp_compute_sym(A, B);
            else if (is_nilpotent(A)) matrix_exp_compute_nil(A, B);
            else B = A.exp();
                
            return B;
        }
        
    }
}
#endif