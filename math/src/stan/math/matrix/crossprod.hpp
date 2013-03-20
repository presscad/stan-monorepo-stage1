#ifndef __STAN__MATH__MATRIX__CROSSPROD_HPP__
#define __STAN__MATH__MATRIX__CROSSPROD_HPP__

#include <stan/math/matrix.hpp>

namespace stan {
  namespace math {

    /**
     * Returns the result of pre-multiplying a matrix by its
     * own transpose.
     * @param M Matrix to multiply.
     * @return Transpose of M times M
     */
    inline matrix_d
    crossprod(const matrix_d& M) {
        return tcrossprod(M.transpose());
    }

  }
}
#endif
