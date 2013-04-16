#ifndef __STAN__MATH__MATRIX__DOT_PRODUCT_HPP__
#define __STAN__MATH__MATRIX__DOT_PRODUCT_HPP__

#include <vector>
#include <stan/math/matrix/Eigen.hpp>
#include <stan/math/matrix/validate_vector.hpp>
#include <stan/math/matrix/validate_matching_sizes.hpp>

namespace stan {
  namespace math {
    
    /**
     * Returns the dot product of the specified vectors.
     *
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Dot product of the vectors.
     * @throw std::domain_error If the vectors are not the same
     * size or if they are both not vector dimensioned.
     */
    template<int R1,int C1,int R2, int C2>
    inline double dot_product(const Eigen::Matrix<double, R1, C1>& v1, 
                              const Eigen::Matrix<double, R2, C2>& v2) {
      validate_vector(v1,"dot_product");
      validate_vector(v2,"dot_product");
      validate_matching_sizes(v1,v2,"dot_product");
      return v1.dot(v2);
    }
    /**
     * Returns the dot product of the specified arrays of doubles.
     * @param v1 First array.
     * @param v2 Second array.
     * @param length Length of both arrays.
     */
    inline double dot_product(const double* v1, const double* v2, 
                              size_t length) {
      double result = 0;
      for (size_t i = 0; i < length; i++)
        result += v1[i] * v2[i];
      return result;
    }
    /**
     * Returns the dot product of the specified arrays of doubles.
     * @param v1 First array.
     * @param v2 Second array.
     * @throw std::domain_error if the vectors are not the same size.
     */
    inline double dot_product(const std::vector<double>& v1,
                              const std::vector<double>& v2) {
      validate_matching_sizes(v1,v2,"dot_product");
      return dot_product(&v1[0], &v2[0], v1.size());
    }
    
  }
}
#endif
