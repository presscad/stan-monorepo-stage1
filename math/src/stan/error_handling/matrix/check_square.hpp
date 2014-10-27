#ifndef STAN__ERROR_HANDLING__MATRIX__CHECK_SQUARE_HPP
#define STAN__ERROR_HANDLING__MATRIX__CHECK_SQUARE_HPP

#include <sstream>
#include <stan/math/matrix/Eigen.hpp>
#include <stan/error_handling/matrix/check_size_match.hpp>

namespace stan {
  namespace error_handling {

    /**
     * Return <code>true</code> if the specified matrix is square.
     *
     * NOTE: this will not throw if any elements in y are nan.
     *
     * @param function
     * @param y Matrix to test.
     * @param name
     * @param result
     * @return <code>true</code> if the matrix is a square matrix.
     * @tparam T Type of scalar.
     */
    template <typename T_y, typename T_result>
    inline bool check_square(const char* function,
                 const Eigen::Matrix<T_y,Eigen::Dynamic,Eigen::Dynamic>& y,
                 const char* name,
                 T_result* result) {
      check_size_match(function, 
                       y.rows(), "Rows of matrix",
                       y.cols(), "columns of matrix",
                       result);
      return true;
    }

  }
}
#endif
