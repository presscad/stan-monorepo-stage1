#ifndef __STAN__PROB__DISTRIBUTIONS__MULTIVARIATE__CONTINUOUS__MULTI_NORMAL_HPP__
#define __STAN__PROB__DISTRIBUTIONS__MULTIVARIATE__CONTINUOUS__MULTI_NORMAL_HPP__

#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

#include <stan/agrad/rev.hpp>
#include <stan/agrad/rev/matrix.hpp>
#include <stan/math/error_handling.hpp>
#include <stan/math/matrix_error_handling.hpp>
#include <stan/math/matrix/log_determinant_ldlt.hpp>
#include <stan/meta/traits.hpp>
#include <stan/prob/constants.hpp>
#include <stan/prob/traits.hpp>
#include <stan/math/error_handling/matrix/check_ldlt_factor.hpp>

namespace stan {

  namespace prob {

   template <bool propto,
             typename T_y, typename T_loc, typename T_covar>
    typename boost::math::tools::promote_args<typename scalar_type<T_y>::type, typename scalar_type<T_loc>::type, T_covar>::type
    multi_normal_log(const T_y& y,
                     const T_loc& mu,
                     const Eigen::Matrix<T_covar,Eigen::Dynamic,Eigen::Dynamic>& Sigma) {
      
      static const char* function = "stan::prob::multi_normal_log(%1%)";
      typename boost::math::tools::promote_args<typename scalar_type<T_y>::type, typename scalar_type<T_loc>::type, T_covar>::type lp(0.0);
      
      using stan::math::check_not_nan;
      using stan::math::check_size_match;
      using stan::math::check_positive;
      using stan::math::check_finite;
      using stan::math::check_symmetric;
      using stan::math::check_ldlt_factor;     
             
      if (!check_size_match(function, 
                            Sigma.rows(), "Rows of covariance parameter",
                            Sigma.cols(), "columns of covariance parameter",
                            &lp))
        return lp;
      if (!check_positive(function, Sigma.rows(), "Covariance matrix rows", &lp))
        return lp;
      if (!check_symmetric(function, Sigma, "Covariance matrix", &lp))
        return lp;
      
      stan::math::LDLT_factor<T_covar,Eigen::Dynamic,Eigen::Dynamic> ldlt_Sigma(Sigma);
      if(!check_ldlt_factor(function,ldlt_Sigma,"LDLT_Factor of covariance parameter",&lp))
        return lp;
        
      using Eigen::Matrix;
      using Eigen::Dynamic;
      using std::vector;
      VectorViewMvt<const T_y> y_vec(y);
      VectorViewMvt<const T_loc> mu_vec(mu);
      size_t size = max_size_mvt(y, mu);
      
      
      //Check if every vector of the array has the same size
      int size_y = y_vec[0].size();
      if (size > 1) {
        int size_y_old = size_y;
        int size_y_new;
        for (size_t i = 1, size_ = length_mvt(y); i < size_; i++) {
          int size_y_new = y_vec[i].size();
          if (!check_size_match(function, 
                                size_y_new, "Size of one of the vectors of the response variable",
                                size_y_old, "Size of another vector of the response variable",
                                &lp))
            return lp;          
          size_y_old = size_y_new;
        }
        int size_mu_old = mu_vec[0].size();
        int size_mu_new;
        for (size_t i = 1, size_ = length_mvt(mu); i < size_; i++) {
          int size_mu_new = mu_vec[i].size();
          if (!check_size_match(function, 
                                size_mu_new, "Size of one of the vectors of the location variable",
                                size_mu_old, "Size of another vector of the location variable",
                                &lp))
            return lp;          
          size_mu_old = size_mu_new;
        }
      }
    
      if (!check_size_match(function, 
                            size_y, "Size of random variable",
                            mu_vec[0].size(), "size of location parameter",
                            &lp))
        return lp;
      if (!check_size_match(function, 
                            size_y, "Size of random variable",
                            Sigma.rows(), "rows of covariance parameter",
                            &lp))
        return lp;
      if (!check_size_match(function, 
                            size_y, "Size of random variable",
                            Sigma.cols(), "columns of covariance parameter",
                            &lp))
        return lp;
  
      for (size_t i = 0; i < size; i++) {      
        if (!check_finite(function, mu_vec[i], "Location parameter", &lp))
          return lp;
        if (!check_not_nan(function, y_vec[i], "Random variable", &lp))
          return lp;
      } 
      
      if (size_y == 0) //y_vec[0].size() == 0
        return lp;


      if (include_summand<propto, T_covar>::value)
        lp -= 0.5 * log_determinant_ldlt(ldlt_Sigma) * size;

      if (include_summand<propto>::value) 
        lp += NEG_LOG_SQRT_TWO_PI * size_y * size;
          
      for (size_t i = 0; i < size; i++) {
        if (include_summand<propto,T_y,T_loc,T_covar>::value) {
          Matrix<typename 
              boost::math::tools::promote_args<typename scalar_type<T_y>::type, typename scalar_type<T_loc>::type>::type,
              Dynamic, 1> y_minus_mu(size_y);
          for (int j = 0; j < size_y; j++)
            y_minus_mu(j) = y_vec[i](j)-mu_vec[i](j);
          lp -= 0.5 * trace_inv_quad_form_ldlt(ldlt_Sigma,y_minus_mu);
        }
      }
      return lp;
    }

    template <typename T_y, typename T_loc, typename T_covar>
    inline
    typename boost::math::tools::promote_args<typename scalar_type<T_y>::type, typename scalar_type<T_loc>::type, T_covar>::type
    multi_normal_log(const T_y& y,
                     const T_loc& mu,
                     const Eigen::Matrix<T_covar,Eigen::Dynamic,Eigen::Dynamic>& Sigma) {
      return multi_normal_log<false>(y,mu,Sigma);
    }


 

    template <bool propto,
              typename T_y, typename T_loc, typename T_covar>
    typename boost::math::tools::promote_args<T_y,T_loc,T_covar>::type
    multi_normal_log(const Eigen::Matrix<T_y,Eigen::Dynamic,Eigen::Dynamic>& y,
                     const Eigen::Matrix<T_loc,Eigen::Dynamic,1>& mu,
                     const Eigen::Matrix<T_covar,Eigen::Dynamic,Eigen::Dynamic>& Sigma) {
      static const char* function = "stan::prob::multi_normal_log(%1%)";
      typename boost::math::tools::promote_args<T_y,T_loc,T_covar>::type lp(0.0);
      
      using stan::math::check_size_match;
      using stan::math::check_positive;
      using stan::math::check_finite;
      using stan::math::check_symmetric;
      using stan::math::check_not_nan;
      using stan::math::check_ldlt_factor;
      
      if (!check_size_match(function, 
                            Sigma.rows(), "Rows of covariance matrix",
                            Sigma.cols(), "columns of covariance matrix",
                            &lp))
        return lp;
      if (!check_positive(function, Sigma.rows(), "Covariance matrix rows", &lp))
        return lp;
      if (!check_symmetric(function, Sigma, "Covariance matrix", &lp))
        return lp;

      stan::math::LDLT_factor<T_covar,Eigen::Dynamic,Eigen::Dynamic> ldlt_Sigma(Sigma);
      if(!check_ldlt_factor(function,ldlt_Sigma,"LDLT_Factor of Sigma",&lp))
        return lp;

      if (!check_size_match(function, 
                            y.cols(), "Columns of random variable",
                            mu.rows(), "rows of location parameter",
                            &lp))
        return lp;
      if (!check_size_match(function, 
                            y.cols(), "Columns of random variable",
                            Sigma.rows(), "rows of covariance parameter",
                            &lp))
        return lp;
      if (!check_size_match(function, 
                            y.cols(), "Columns of random variable",
                            Sigma.cols(), "columns of covariance parameter",
                            &lp))
        return lp;
      if (!check_finite(function, mu, "Location parameter", &lp))
        return lp;
      if (!check_not_nan(function, y, "Random variable", &lp))
        return lp;
      
      if (y.cols() == 0)
        return lp;
      
      if (include_summand<propto>::value) 
        lp += NEG_LOG_SQRT_TWO_PI * y.cols() * y.rows();
      
      if (include_summand<propto,T_covar>::value) {
        lp -= 0.5 * log_determinant_ldlt(ldlt_Sigma) * y.rows();
      }
      
      if (include_summand<propto,T_y,T_loc,T_covar>::value) {
        Eigen::Matrix<T_loc, Eigen::Dynamic, Eigen::Dynamic> MU(y.rows(),y.cols());
        for(typename Eigen::Matrix<T_loc, Eigen::Dynamic, Eigen::Dynamic>::size_type i = 0; 
            i < y.rows(); 
            i++)
          MU.row(i) = mu;
        
        Eigen::Matrix<typename
            boost::math::tools::promote_args<T_loc,T_y>::type,
            Eigen::Dynamic,Eigen::Dynamic> y_minus_MU(y.rows(), y.cols());

        for (int i = 0; i < y.size(); i++)
          y_minus_MU(i) = y(i)-MU(i);
        
        Eigen::Matrix<typename 
            boost::math::tools::promote_args<T_loc,T_y>::type,
            Eigen::Dynamic,Eigen::Dynamic> z(y_minus_MU.transpose()); // was = 
        
        // Eigen::Matrix<typename 
        //               boost::math::tools::promote_args<T_loc,T_y>::type,
        //               Eigen::Dynamic,Eigen::Dynamic> 
        //   z(subtract(y,MU).transpose()); // was = 
        
        lp -= 0.5 * trace_inv_quad_form_ldlt(ldlt_Sigma,z);
      }
      return lp;      
    }

    template <typename T_y, typename T_loc, typename T_covar>
    inline
    typename boost::math::tools::promote_args<T_y,T_loc,T_covar>::type
    multi_normal_log(const Eigen::Matrix<T_y,Eigen::Dynamic,Eigen::Dynamic>& y,
                     const Eigen::Matrix<T_loc,Eigen::Dynamic,1>& mu,
                     const Eigen::Matrix<T_covar,Eigen::Dynamic,Eigen::Dynamic>& Sigma) {
      return multi_normal_log<false>(y,mu,Sigma);
    }
    
 
    template <class RNG>
    inline Eigen::VectorXd
    multi_normal_rng(const Eigen::Matrix<double,Eigen::Dynamic,1>& mu,
                     const Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& S,
                     RNG& rng) {
      using boost::variate_generator;
      using boost::normal_distribution;

      static const char* function = "stan::prob::multi_normal_rng(%1%)";

      using stan::math::check_positive;
      using stan::math::check_finite;
      using stan::math::check_symmetric;
 
      check_positive(function, S.rows(), "Covariance matrix rows");
      check_symmetric(function, S, "Covariance matrix");
      check_finite(function, mu, "Location parameter");

      variate_generator<RNG&, normal_distribution<> >
        std_normal_rng(rng, normal_distribution<>(0,1));

      Eigen::VectorXd z(S.cols());
      for(int i = 0; i < S.cols(); i++)
        z(i) = std_normal_rng();

      return mu + S.llt().matrixL() * z;
    }
  }
}

#endif

