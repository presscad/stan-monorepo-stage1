#ifndef __STAN__MATH__ERROR_HANDLING__MATRIX__CHECK_COV_MATRIX_HPP__
#define __STAN__MATH__ERROR_HANDLING__MATRIX__CHECK_COV_MATRIX_HPP__

#include <sstream>
#include <stan/math/matrix/Eigen.hpp>
#include <stan/math/error_handling/default_policy.hpp>
#include <stan/math/error_handling/raise_domain_error.hpp>
#include <stan/math/error_handling/check_positive.hpp>
#include <stan/math/error_handling/matrix/check_pos_definite.hpp>
#include <stan/math/error_handling/matrix/check_symmetric.hpp>


namespace stan {
  namespace math {

    /**
     * Return <code>true</code> if the specified matrix is a valid
     * covariance matrix.  A valid covariance matrix must be square,
     * symmetric, and positive definite.
     *
     * @param function
     * @param y Matrix to test.
     * @param name
     * @param result
     * @return <code>true</code> if the matrix is a valid covariance matrix.
     * @tparam T Type of scalar.
     */
    // FIXME: update warnings
    template <typename T_y, typename T_result, class Policy>
    inline bool check_cov_matrix(const char* function,
                 const Eigen::Matrix<T_y,Eigen::Dynamic,Eigen::Dynamic>& y,
                 const char* name,
                 T_result* result,
                 const Policy&) {
      if (!check_size_match(function, 
          y.rows(), "Rows of covariance matrix",
          y.cols(), "columns of covariance matrix",
          result, Policy())) 
        return false;
      if (!check_positive(function, y.rows(), "rows", result, Policy()))
        return false;
      if (!check_symmetric(function, y, name, result, Policy()))
        return false;
      if (!check_pos_definite(function, y, name, result, Policy()))
        return false;
      return true;
    }

    template <typename T_y, typename T_result>
    inline bool check_cov_matrix(const char* function,
                 const Eigen::Matrix<T_y,Eigen::Dynamic,Eigen::Dynamic>& y,
                 const char* name,
                 T_result* result) {
      return check_cov_matrix(function,y,name,result,default_policy());
    }


    template <typename T>
    inline bool check_cov_matrix(const char* function,
                 const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& y,
                 const char* name,
                 T* result = 0) {
      return check_cov_matrix(function,y,name,result,default_policy());
    }

  }
}
#endif
