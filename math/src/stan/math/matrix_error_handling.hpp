#ifndef __STAN__MATH__MATRIX_ERROR_HANDLING_HPP__
#define __STAN__MATH__MATRIX_ERROR_HANDLING_HPP__

#include <limits>

#include <stan/math/boost_error_handling.hpp>
#include <stan/math/special_functions.hpp>
#include <stan/math/error_handling.hpp>

#include <stan/math/matrix.hpp>

#include <boost/type_traits/common_type.hpp>

namespace stan { 

  namespace math {

    /**
     * Return <code>true</code> if the specified matrix is symmetric
     * 
     * NOTE: squareness is not checked by this function
     *
     * @param y Matrix to test.
     * @return <code>true</code> if the matrix is symmetric.
     * @tparam T Type of scalar.
     */
    template <typename T>
    bool symmetry_validate(const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& y) {
      size_t k = y.rows();
      if (k == 1)
        return true;
      
      for (size_t m = 0; m < k; ++m) {
        for (size_t n = m + 1; n < k; ++n) {
          if (fabs(y(m,n) - y(n,m)) > CONSTRAINT_TOLERANCE)
            return false;
        }
      }
      return true;
    }


    /**
     * Return <code>true</code> if the specified matrix is positive definite
     *
     * NOTE: symmetry is NOT checked by this function
     * 
     * @param y Matrix to test.
     * @return <code>true</code> if the matrix is positive definite.
     * @tparam T Type of scalar.
     */
    template <typename T>
    bool pd_validate(const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& y) {
      if (y.rows() == 1)
        return y(0,0) > CONSTRAINT_TOLERANCE;
      
      Eigen::LDLT< Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> > cholesky = y.ldlt();
      if( (cholesky.vectorD().array() > CONSTRAINT_TOLERANCE).all() )
        return true;
      
      return false;
    }

    /**
     * Return <code>true</code> if the specified matrix is a valid
     * covariance matrix.  A valid covariance matrix must be square,
     * symmetric, and positive definite.
     *
     * @param y Matrix to test.
     * @return <code>true</code> if the matrix is a valid covariance matrix.
     * @tparam T Type of scalar.
     */
    template <typename T>
    bool cov_matrix_validate(const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& y) {
      if (y.rows() != y.cols() || y.rows() == 0)
        return false;

      if (!symmetry_validate(y))
        return false;

      if (!pd_validate(y))
        return false;

      return true;
    }

    /**
     * Return <code>true</code> if the specified matrix is a valid
     * covariance matrix.  A valid covariance matrix must be symmetric
     * and positive definite.
     *
     * @param y Matrix to test.
     * @param err_msg Output stream for error messages.
     * @return <code>true</code> if the matrix is a valid covariance matrix.
     * @tparam T Type of scalar.
     */
    template <typename T>
    bool cov_matrix_validate(const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& y, std::ostream& err_msg) {
      if (y.rows() != y.cols() || y.rows() == 0) {
        err_msg << "Matrix is not square: [" << y.rows() << ", " << y.cols() << "]";
        return false;
      }

      if (!symmetry_validate(y)) {
        err_msg << "Matrix is not symmetric";
        return false;
      }

      if (!pd_validate(y)) {
        err_msg << "Matrix is not positive definite";
        return false;
      }
      
      return true;
    }

    /**
     * Return <code>true</code> if the specified matrix is a valid
     * correlation matrix.  A valid correlation matrix is symmetric,
     * has a unit diagonal (all 1 values), and has all values between
     * -1 and 1 (inclussive).  
     *
     * @param y Matrix to test.
     * @return <code>true</code> if the specified matrix is a valid
     * correlation matrix.
     * @tparam T Type of scalar.
     */
    template <typename T>
    bool corr_matrix_validate(const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& y) {
      if (!cov_matrix_validate(y))
        return false;
      for (typename Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>::size_type k = 0; k < y.rows(); ++k) {
        if (fabs(y(k,k) - 1.0) > CONSTRAINT_TOLERANCE)
          return false;
      }
      return true;
    }

    /**
     * Return <code>true</code> if the specified vector is simplex.
     * To be a simplex, all values must be greater than or equal to 0
     * and the values must sum to 1.
     *
     * <p>The test that the values sum to 1 is done to within the
     * tolerance specified by <code>CONSTRAINT_TOLERANCE</code>.
     *
     * @param y Vector to test.
     * @return <code>true</code> if the vector is a simplex.
     */
    template <typename T>
    bool
    simplex_validate(const Eigen::Matrix<T,Eigen::Dynamic,1>& y) {
      if (y.size() == 0)
        return false;
      if (fabs(1.0 - y.sum()) > CONSTRAINT_TOLERANCE)
        return false;
      for (typename Eigen::Matrix<T,Eigen::Dynamic,1>::size_type i = 0; i < y.size(); ++i) {
        if (!(y[i] >= 0.0)) 
          return false;
      }
      return true;
    }

    /**
     * Return <code>true</code> if the specified vector contains
     * only non-negative values and is sorted into increasing order.
     * There may be duplicate values.
     *
     * @param y Vector to test.
     * @return <code>true</code> if the vector has positive, ordered
     * values.
     * @tparam T Type of scalar.
     */
    template <typename T>
    bool pos_ordered_validate(const Eigen::Matrix<T,Eigen::Dynamic,1>& y) {
      if (y.size() == 0) return true;
      if (!(y[0] > 0.0)) return false;
      for (typename Eigen::Matrix<T,Eigen::Dynamic,1>::size_type k = 1; k < y.size(); ++k) {
        if (!(y[k] > y[k-1]))
          return false;
      }
      return true;
    }



    template <typename T_y, typename T_result, class Policy>
    inline bool check_not_nan(const char* function,
                              const Eigen::Matrix<T_y,Eigen::Dynamic,1>& y,
                              const char* name,
                              T_result* result,
                              const Policy& /*pol*/) {
      using stan::math::policies::raise_domain_error;
      for (int i = 0; i < y.rows(); i++) {
        if (boost::math::isnan(y[i])) {
          std::ostringstream message;
          message << name << "[" << i << "] is %1%, but must not be nan!";
          *result = raise_domain_error<T_result,T_y>(function,
                                                     message.str().c_str(),
                                                     y[i],
                                                     Policy());
          return false;
        }
      }
      return true;
    }


    template <typename T_y, typename T_result, class Policy>
    inline bool check_not_nan(const char* function,
                              const Eigen::Matrix<T_y,Eigen::Dynamic,Eigen::Dynamic>& y,
                              const char* name,
                              T_result* result,
                              const Policy& /*pol*/) {
      for (int i = 0; i < y.rows(); i++) {
        for (int j = 0; j < y.cols(); j++) {
          if (boost::math::isnan(y(i,j))) {
            std::ostringstream message;
            message << name << "[" << i << "," << j << "] is %1%, but must not be nan!";
            *result = policies::raise_domain_error<T_y>(function,
                                              message.str().c_str(),
                                              y(i,j), Policy());
            return false;
          }
        }
      }
      return true;
    }


    template <typename T_y, typename T_result, class Policy>
    inline bool check_finite(const char* function,
                             const Eigen::Matrix<T_y,Eigen::Dynamic,1>& y,
                             const char* name,
                             T_result* result,
                             const Policy& /*pol*/) {
      using stan::math::policies::raise_domain_error;
      for (int i = 0; i < y.rows(); i++) {
        if (!boost::math::isfinite(y[i])) {
          std::ostringstream message;
          message << name << "[" << i << "] is %1%, but must be finite!";
          *result = raise_domain_error<T_result,T_y>(function,
                                                     message.str().c_str(),
                                                     y[i],
                                                     Policy());
          return false;
        }
      }
      return true;
    }

    template <typename T_covar, typename T_result, class Policy>
    inline bool check_cov_matrix(const char* function,
                                 const Eigen::Matrix<T_covar,Eigen::Dynamic,Eigen::Dynamic>& Sigma,
                                 T_result* result,
                                 const Policy& /*pol*/) {
      if (!cov_matrix_validate(Sigma)) {
        std::ostringstream stream;
        stream << "Sigma is not a valid covariance matrix. "
               << "Sigma must be symmetric and positive semi-definite. Sigma: \n" 
               << Sigma
               << "\nSigma(0,0): %1%";
        *result = boost::math::policies::raise_domain_error<T_covar>(function,
                                                                     stream.str().c_str(), 
                                                                     Sigma(0,0),
                                                                     Policy());
        return false;
      }
      return true;
    }

    template <typename T_covar, typename T_result, class Policy>
    inline bool check_corr_matrix(const char* function,
                                 const Eigen::Matrix<T_covar,Eigen::Dynamic,Eigen::Dynamic>& Sigma,
                                 T_result* result,
                                 const Policy& /*pol*/) {
      if (!corr_matrix_validate(Sigma)) {
        std::ostringstream stream;
        stream << "Sigma is not a valid correlation matrix."
               << "Sigma must be symmetric and positive semi-definite with ones on its diagonal. Sigma: \n" 
               << Sigma
               << "\nSigma(0,0): %1%";
        *result = policies::raise_domain_error<T_covar>(function,
                                              stream.str().c_str(), 
                                              Sigma(0,0),
                                              Policy());
        return false;
      }
      return true;
    }

    template <typename T_result, typename T_size1, typename T_size2, class Policy>
    inline bool check_size_match(const char* function,
                                 T_size1 i,
                                 T_size2 j,
                                 T_result* result,
                                 const Policy& /*pol*/) {
      using stan::math::policies::raise_domain_error;
      typedef typename boost::common_type<T_size1,T_size2>::type common_type;
      if (static_cast<common_type>(i) != static_cast<common_type>(j)) {
        std::ostringstream msg;
        msg << "i and j must be same.  Found i=%1%, j=" << j;
        *result = raise_domain_error<T_result,T_size1>(function,
                                                       msg.str().c_str(),
                                                       i,
                                                       Policy());
        return false;
      }
      return true;
    }


    template <typename T_prob, typename T_result, class Policy>
    inline bool check_simplex(const char* function,
                              const Eigen::Matrix<T_prob,Eigen::Dynamic,1>& theta,
                              const char* name,
                              T_result* result,
                              const Policy& /*pol*/) {
      using stan::math::policies::raise_domain_error;
      if (!simplex_validate(theta)) {
        std::ostringstream stream;
        stream << name
               << "is not a valid simplex. The first element of the simplex is: %1%.";
        *result = raise_domain_error<T_result,T_prob>(function,
                                                      stream.str().c_str(), 
                                                      theta(0),
                                                      Policy());
        return false;
      }
      return true;
    }



  }
}

#endif
