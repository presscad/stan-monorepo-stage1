#ifndef __STAN__PROB__DISTRIBUTIONS_HPP__
#define __STAN__PROB__DISTRIBUTIONS_HPP__

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <Eigen/Dense>
#include <Eigen/Cholesky>
#include "stan/maths/special_functions.hpp"

#include "stan/prob/transform.hpp"
#include "stan/agrad/matrix.hpp"


namespace stan {

  namespace prob {

    using Eigen::Array;
    using Eigen::Matrix;
    using Eigen::DiagonalMatrix;
    using Eigen::Dynamic;
    using namespace std;
    using namespace stan::maths;
    
    namespace {
   
      const double PI = boost::math::constants::pi<double>();

      const double LOG_ZERO = log(0.0);

      const double LOG_TWO = log(2.0);

      const double NEG_LOG_TWO = -LOG_TWO;

      const double NEG_LOG_SQRT_TWO_PI = - log(sqrt(2.0 * PI));

      const double NEG_LOG_PI = -log(PI);

      const double NEG_LOG_SQRT_PI = -log(sqrt(PI));

      const double NEG_LOG_TWO_OVER_TWO = -LOG_TWO / 2.0;
    }

    // UNIVARIATE CUMULATIVE DISTRIBUTIONS

    namespace {
      const double SQRT_2 = std::sqrt(2);
    }

    /**
     * Calculates the normal cumulative distribution function for the given
     * y, mean, and variance.
     * 
     * \f$\Phi(x) = \frac{1}{\sqrt{2 \pi}} \int_{-\inf}^x e^{-t^2/2} dt\f$.
     * 
     * @param y A scalar variable.
     * @param mean The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distriubtion
     * @return The unit normal cdf evaluated at the specified argument.
     * @throw std::domain_error if sigma is less than 0
     * @tparam T_y Type of y.
     * @tparam T_loc Type of mean parameter.
     * @tparam T_scale Type of standard deviation paramater.
     */
    template <typename T_y, typename T_loc, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y, T_loc, T_scale>::type
    normal_p(const T_y& y, const T_loc& mean, const T_scale& sigma) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return 0.5 * erfc(-(y - mean)/(sigma * SQRT_2));
    }

    // CONTINUOUS, UNIVARIATE DENSITIES
    /**
     * The log of a uniform density for the given 
     * y, lower, and upper bound. 
     *
     \f{eqnarray*}{
       y &\sim& U(\alpha, \beta) \\
       \log (p (y \,|\, \alpha, \beta)) &=& \log \left( \frac{1}{\beta-\alpha} \right) \\
         &=& \log (1) - \log (\beta - \alpha) \\
         &=& -\log (\beta - \alpha) \\
         & & \mathrm{ where } \; y \in [\alpha, \beta], \log(0) \; \mathrm{otherwise}
     \f}
     * 
     * @param y A scalar variable.
     * @param alpha Lower bound.
     * @param beta Upper bound.
     * @throw std::invalid_argument if the lower bound is greater than 
     *    or equal to the lower bound
     * @tparam T_y Type of scalar.
     * @tparam T_low Type of lower bound.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_low, typename T_high>
    inline typename boost::math::tools::promote_args<T_y,T_low,T_high>::type
    uniform_log(const T_y& y, const T_low& alpha, const T_high& beta) {
      if (alpha >= beta) {
	std::ostringstream err;
	err << "lower bound (" << alpha << ") must be less than the upper bound (" << beta <<")";
	BOOST_THROW_EXCEPTION(std::invalid_argument (err.str()));
      }
      if (y < alpha || y > beta)
	return LOG_ZERO;
      return -log(beta - alpha);
    }
    /**
     * The log of a density proportional to a uniform density for the given 
     * y, lower, and upper bound. 
     *
     * @param y A scalar variable.
     * @param alpha Lower bound.
     * @param beta Upper bound.
     * @throw std::invalid_argument if the lower bound is greater than 
     *    or equal to the lower bound
     * @tparam T_y Type of scalar.
     * @tparam T_low Type of lower bound.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_low, typename T_high>
    inline typename boost::math::tools::promote_args<T_y,T_low,T_high>::type
    uniform_propto_log(const T_y& y, const T_low& alpha, const T_high& beta) {
      if (alpha >= beta) {
	std::ostringstream err;
	err << "lower bound (" << alpha << ") must be less than the upper bound (" << beta <<")";
	BOOST_THROW_EXCEPTION(std::invalid_argument (err.str()));
      }
      return uniform_log (y, alpha, beta);
    }
    /**
     * The log of a density proportional to a uniform density for the given 
     * y, lower, and upper bound. 
     *
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param alpha Lower bound.
     * @param beta Upper bound.
     * @throw std::invalid_argument if the lower bound is greater than 
     *    or equal to the lower bound
     * @tparam T_y Type of scalar.
     * @tparam T_low Type of lower bound.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_low, typename T_high>
    inline void
    uniform_propto_log(stan::agrad::var& lp, const T_y& y, const T_low& alpha, const T_high& beta) {
      if (alpha >= beta) {
	std::ostringstream err;
	err << "lower bound (" << alpha << ") must be less than the upper bound (" << beta <<")";
	BOOST_THROW_EXCEPTION(std::invalid_argument (err.str()));
      }
      lp += uniform_propto_log (y, alpha, beta);
    }

    /**
     * The log of the normal density for the given y, mean, and
     * standard deviation.  The standard deviation must be greater
     * than 0.
     *
     * \f{eqnarray*}{
       y &\sim& N (\mu, \sigma^2) \\
       \log (p (y \,|\, \mu, \sigma) ) &=& \log \left( \frac{1}{\sqrt{2 \pi} \sigma} \exp \left( - \frac{1}{2 \sigma^2} (y - \mu)^2 \right) \right) \\
       &=& \log (1) - \frac{1}{2}\log (2 \pi) - \log (\sigma) - \frac{(y - \mu)^2}{2 \sigma^2}
     \f}
     * 
     * 
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @return The log of the normal density.
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, typename T_loc, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_scale>::type
    normal_log(const T_y& y, const T_loc& mu, const T_scale& sigma) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return NEG_LOG_SQRT_TWO_PI
	- log(sigma)
	- ((y - mu) * (y - mu)) / (2.0 * sigma * sigma);
    }

    /**
     * The log of the normal density up to a proportion for the given 
     * y, mean, and standard deviation.
     * The standard deviation must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @return The log of the normal density up to a proportion.
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     */    
    template <typename T_y, typename T_loc, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_scale>::type
    normal_propto_log(const T_y& y, const T_loc& mu, const T_scale& sigma) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return normal_log(y,mu,sigma);
    }
    
    /**
     * The log of the normal density up to a proportion for the given 
     * y, mean, and standard deviation.
     * The standard deviation must be greater than 0.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, typename T_loc, typename T_scale>
    inline void
    normal_propto_log(stan::agrad::var& lp, const T_y& y, const T_loc& mu, const T_scale& sigma) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += normal_propto_log(y,mu,sigma);
    }

    // NormalTruncatedLH(y|mu,sigma,low,high)  [sigma > 0, low < high]
    // Norm(y|mu,sigma) / (Norm_p(high|mu,sigma) - Norm_p(low|mu,sigma))
    /**
     * The log of a truncated normal density for the given 
     * y, mean, standard deviation, lower bound, and upper bound.
     * The standard deviation must be greater than 0.
     * The lower bound must be less than the upper bound.
     * 
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param low Lower bound.
     * @param high Upper bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @throw std::invalid_argument if high is not greater than low.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_low Type of lower bound.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_low, typename T_high>
    inline typename boost::math::tools::promote_args<T_y, T_loc, T_scale, T_low, T_high>::type
    normal_trunc_lh_log(const T_y& y, const T_loc& mu, const T_scale& sigma, const T_low& low, const T_high& high) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (high <= low) {
	std::ostringstream err;
	err << "lower bound (" << low << ") must be less than the upper bound (" << high <<")";
	BOOST_THROW_EXCEPTION (std::invalid_argument (err.str()));
      }

      if (y > high || y < low)
	return LOG_ZERO;
      return normal_log(y,mu,sigma) 
	- log(normal_p(high,mu,sigma) - normal_p(low,mu,sigma));
    }

    /**
     * The log of a distribution proportional to a truncated normal density for the given 
     * y, mean, standard deviation, lower bound, and upper bound.
     * The standard deviation must be greater than 0.
     * The lower bound must be less than the upper bound.
     * 
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param low Lower bound.
     * @param high Upper bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @throw std::invalid_argument if high is not greater than low.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_low Type of lower bound.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_low, typename T_high>
    inline typename boost::math::tools::promote_args<T_y, T_loc, T_scale, T_low, T_high>::type
    normal_trunc_lh_propto_log(const T_y& y, const T_loc& mu, const T_scale& sigma, const T_low& low, const T_high& high) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (high <= low) {
	std::ostringstream err;
	err << "lower bound (" << low << ") must be less than the upper bound (" << high <<")";
	BOOST_THROW_EXCEPTION (std::invalid_argument (err.str()));
      }
      return (normal_trunc_lh_log (y, mu, sigma, low, high));
    }
    /**
     * The log of a distribution proportional to a truncated normal density for the given 
     * y, mean, standard deviation, lower bound, and upper bound.
     * The standard deviation must be greater than 0.
     * The lower bound must be less than the upper bound.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param low Lower bound.
     * @param high Upper bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @throw std::invalid_argument if high is not greater than low.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_low Type of lower bound.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_low, typename T_high>
    inline void
    normal_trunc_lh_propto_log(stan::agrad::var& lp, const T_y& y, const T_loc& mu, const T_scale& sigma, const T_low& low, const T_high& high) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (high <= low) {
	std::ostringstream err;
	err << "lower bound (" << low << ") must be less than the upper bound (" << high <<")";
	BOOST_THROW_EXCEPTION (std::invalid_argument (err.str()));
      }
      lp += normal_trunc_lh_propto_log (y, mu, sigma, low, high);
    }

    // NormalTruncatedL(y|mu,sigma,low)  [sigma > 0]
    // Norm(y|mu,sigma) / (1 - Norm_p(low|mu,sigma))
    /**
     * The log of a truncated normal density for the given 
     * y, mean, standard deviation, and lower bound.
     * The standard deviation must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param low Lower bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_low Type of lower bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_low>
    inline typename boost::math::tools::promote_args<T_y, T_loc, T_scale, T_low>::type
    normal_trunc_l_log(const T_y& y, const T_loc& mu, const T_scale& sigma, const T_low& low) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < low)
	return LOG_ZERO;
      return normal_log(y,mu,sigma) 
	- log1m(normal_p(low,mu,sigma));
    }
    /**
     * The log of a truncated normal density for the given 
     * y, mean, standard deviation, and lower bound.
     * The standard deviation must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param low Lower bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_low Type of lower bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_low>
    inline typename boost::math::tools::promote_args<T_y, T_loc, T_scale, T_low>::type
    normal_trunc_l_propto_log(const T_y& y, const T_loc& mu, const T_scale& sigma, const T_low& low) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return normal_trunc_l_log (y, mu, sigma, low);
    }
    /**
     * The log of a truncated normal density for the given 
     * y, mean, standard deviation, and lower bound.
     * The standard deviation must be greater than 0.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param low Lower bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_low Type of lower bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_low>
    inline void
    normal_trunc_l_propto_log(stan::agrad::var& lp, const T_y& y, const T_loc& mu, const T_scale& sigma, const T_low& low) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += normal_trunc_l_propto_log (y, mu, sigma, low);
    }
    // NormalTruncatedH(y|mu,sigma,high)  [sigma > 0]
    // Norm(y|mu,sigma) / (Norm_p(high|mu,sigma) - 0)
    /**
     * The log of a truncated normal density for the given 
     * y, mean, standard deviation, and upper bound.
     * The standard deviation must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param high Upper bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_high>
    inline typename boost::math::tools::promote_args<T_y, T_loc, T_scale, T_high>::type
    normal_trunc_h_log(const T_y& y, const T_loc& mu, const T_scale& sigma, const T_high& high) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y > high)
	return LOG_ZERO;
      return normal_log(y,mu,sigma) 
	- log(normal_p(high,mu,sigma));
    }
    /**
     * The log of a density proportional to a truncated normal density for the given 
     * y, mean, standard deviation, and upper bound.
     * The standard deviation must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param high Upper bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_high>
    inline typename boost::math::tools::promote_args<T_y, T_loc, T_scale, T_high>::type
    normal_trunc_h_propto_log(const T_y& y, const T_loc& mu, const T_scale& sigma, const T_high& high) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return normal_trunc_h_log (y, mu, sigma, high);
    }
    /**
     * The log of a density proportional to a truncated normal density for the given 
     * y, mean, standard deviation, and upper bound.
     * The standard deviation must be greater than 0.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param mu The mean of the normal distribution.
     * @param sigma The standard deviation of the normal distribution. 
     * @param high Upper bound.
     * @throw std::domain_error if sigma is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     * @tparam T_high Type of upper bound.
     */
    template <typename T_y, typename T_loc, typename T_scale, typename T_high>
    inline void
    normal_trunc_h_propto_log(stan::agrad::var& lp, const T_y& y, const T_loc& mu, const T_scale& sigma, const T_high& high) {
      if (sigma <= 0) {
	std::ostringstream err;
	err << "sigma (" << sigma << ") must be greater than 0.";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += normal_trunc_h_propto_log (y, mu, sigma, high);
    }


    /**
     * The log of a gamma density for y with the specified
     * shape and inverse scale parameters.
     * Shape and inverse scale parameters must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     \f{eqnarray*}{
       y &\sim& \mathrm{Gamma}(\alpha, \beta) \\
       \log (p (y \,|\, \alpha, \beta) ) &=& \log \left( \frac{\beta^\alpha}{\Gamma(\alpha)} y^{\alpha - 1} \exp^{- \beta y} \right) \\
       &=& \alpha \log(\beta) - \log(\Gamma(\alpha)) + (\alpha - 1) \log(y) - \beta y\\
       & & \mathrm{where} \; y > 0
     \f}
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_shape, typename T_inv_scale>
    inline typename boost::math::tools::promote_args<T_y,T_shape,T_inv_scale>::type
    gamma_log(const T_y& y, const T_shape& alpha, const T_inv_scale& beta) {
      if (alpha <= 0) {
	std::ostringstream err;
	err << "alpha (" << alpha << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error(err.str()));
      }
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than or equal to 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return - lgamma(alpha)
	+ alpha * log(beta)
	+ (alpha - 1.0) * log(y)
	- beta * y;
    }
    /**
     * The log of a distribution proportional to a gamma density for y with the specified
     * shape and inverse scale parameters.
     * Shape and inverse scale parameters must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_shape, typename T_inv_scale>
    inline typename boost::math::tools::promote_args<T_y,T_shape,T_inv_scale>::type
    gamma_propto_log(const T_y& y, const T_shape& alpha, const T_inv_scale& beta) {
      if (alpha <= 0) {
	std::ostringstream err;
	err << "alpha (" << alpha << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error(err.str()));
      }
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than or equal to 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return gamma_log (y, alpha, beta);
    }
    /**
     * The log of a distribution proportional to a gamma density for y with the specified
     * shape and inverse scale parameters.
     * Shape and inverse scale parameters must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_shape, typename T_inv_scale>
    inline void
    gamma_propto_log(stan::agrad::var& lp, const T_y& y, const T_shape& alpha, const T_inv_scale& beta) {
      if (alpha <= 0) {
	std::ostringstream err;
	err << "alpha (" << alpha << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error(err.str()));
      }
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than or equal to 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += gamma_propto_log (y, alpha, beta);
    }

    /**
     * The log of an inverse gamma density for y with the specified
     * shape and inverse scale parameters.
     * Shape and inverse scale parameters must be greater than 0.
     * y must be greater than 0.
     * 
     \f{eqnarray*}{
       y &\sim& \mathrm{Inv-gamma}(\alpha, \beta) \\
       \log (p (y \,|\, \alpha, \beta) ) &=& \log \left( \frac{\beta^\alpha}{\Gamma(\alpha)} y^{-(\alpha + 1)} \exp^{- \beta / y} \right) \\
       &=& \alpha \log(\beta) - \log(\Gamma(\alpha)) - (\alpha + 1) \log(y) - \frac{\beta}{y} \\
       & & \mathrm{where } y > 0
     \f}
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_shape, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_shape,T_scale>::type
    inv_gamma_log(const T_y& y, const T_shape& alpha, const T_scale& beta) {
      if (alpha <= 0) {
	std::ostringstream err;
	err << "alpha (" << alpha << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error(err.str()));
      }
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return - lgamma(alpha)
	+ alpha * log(beta)
	- (alpha + 1) * log(y)
	- beta / y;
    }
    /**
     * The log of a distribution proportional to an inverse gamma density for y with the specified
     * shape and inverse scale parameters.
     * Shape and inverse scale parameters must be greater than 0.
     * y must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_shape, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_shape,T_scale>::type
    inv_gamma_propto_log(const T_y& y, const T_shape& alpha, const T_scale& beta) {
      if (alpha <= 0) {
	std::ostringstream err;
	err << "alpha (" << alpha << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error(err.str()));
      }
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return inv_gamma_log (y, alpha, beta);
    }
    /**
     * The log of a distribution proportional to an inverse gamma density for y with the specified
     * shape and inverse scale parameters.
     * Shape and inverse scale parameters must be greater than 0.
     * y must be greater than 0.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_shape, typename T_scale>
    inline void
    inv_gamma_propto_log(stan::agrad::var& lp, const T_y& y, const T_shape& alpha, const T_scale& beta) {
      if (alpha <= 0) {
	std::ostringstream err;
	err << "alpha (" << alpha << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error(err.str()));
      }
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += inv_gamma_propto_log (y, alpha, beta);
    }

    /**
     * The log of a chi-squared density for y with the specified
     * degrees of freedom parameter.
     * The degrees of freedom prarameter must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     \f{eqnarray*}{
       y &\sim& \chi^2_\nu \\
       \log (p (y \,|\, \nu)) &=& \log \left( \frac{2^{-\nu / 2}}{\Gamma (\nu / 2)} y^{\nu / 2 - 1} \exp^{- y / 2} \right) \\
       &=& - \frac{\nu}{2} \log(2) - \log (\Gamma (\nu / 2)) + (\frac{\nu}{2} - 1) \log(y) - \frac{y}{2} \\
       & & \mathrm{ where } \; y \ge 0
     \f}
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof>
    inline typename boost::math::tools::promote_args<T_y,T_dof>::type
    chi_square_log(const T_y& y, const T_dof& nu) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return - lgamma(0.5 * nu)
	+ nu * NEG_LOG_TWO_OVER_TWO
	+ (0.5 * nu - 1.0) * log(y)
	- 0.5 * y;
    }
    /**
     * The log of a distribution proportional to a chi-squared density for y with the specified
     * degrees of freedom parameter.
     * The degrees of freedom prarameter must be greater than 0.
     * y must be greater than or equal to 0.
     *
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof>
    inline typename boost::math::tools::promote_args<T_y,T_dof>::type
    chi_square_propto_log(const T_y& y, const T_dof& nu) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return chi_square_log(y, nu);
    } 
    /**
     * The log of a distribution proportional to a chi-squared density for y with the specified
     * degrees of freedom parameter.
     * The degrees of freedom prarameter must be greater than 0.
     * y must be greater than or equal to 0.
     *
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof>
    inline void
    chi_square_propto_log(stan::agrad::var& lp, const T_y& y, const T_dof& nu) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += chi_square_propto_log(y, nu);
    } 

    /**
     * The log of an inverse chi-squared density for y with the specified
     * degrees of freedom parameter.
     * The degrees of freedom prarameter must be greater than 0.
     * y must be greater than 0.
     * 
     \f{eqnarray*}{
       y &\sim& \mathrm{Inv-}\chi^2_\nu \\
       \log (p (y \,|\, \nu)) &=& \log \left( \frac{2^{-\nu / 2}}{\Gamma (\nu / 2)} y^{- (\nu / 2 + 1)} \exp^{-1 / (2y)} \right) \\
       &=& - \frac{\nu}{2} \log(2) - \log (\Gamma (\nu / 2)) - (\frac{\nu}{2} + 1) \log(y) - \frac{1}{2y} \\
       & & \mathrm{ where } \; y > 0
     \f}
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof>
    inline typename boost::math::tools::promote_args<T_y,T_dof>::type
    inv_chi_square_log(const T_y& y, const T_dof& nu) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return - lgamma(0.5 * nu)
	+ nu * NEG_LOG_TWO_OVER_TWO
	- (0.5 * nu + 1.0) * log(y)
	- 0.5 / y;
    }
    /**
     * The log of a distribution proportional to an inverse chi-squared density for y with the specified
     * degrees of freedom parameter.
     * The degrees of freedom prarameter must be greater than 0.
     * y must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof>
    inline typename boost::math::tools::promote_args<T_y,T_dof>::type
    inv_chi_square_propto_log(const T_y& y, const T_dof& nu) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return inv_chi_square_log(y, nu);
    }
    /**
     * The log of a distribution proportional to an inverse chi-squared density for y with the specified
     * degrees of freedom parameter.
     * The degrees of freedom prarameter must be greater than 0.
     * y must be greater than 0.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof>
    inline void
    inv_chi_square_propto_log(stan::agrad::var& lp, const T_y& y, const T_dof& nu) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += inv_chi_square_propto_log(y, nu);
    }


    /**
     * The log of a scaled inverse chi-squared density for y with the specified
     * degrees of freedom parameter and scale parameter.
     * The degrees of freedom prarameter must be greater than 0. The scale parameter must be greater
     * than 0.
     * y must be greater than 0.
     * 
     \f{eqnarray*}{
       y &\sim& \mathrm{Inv-}\chi^2(\nu, s^2) \\
       \log (p (y \,|\, \nu, s)) &=& \log \left( \frac{(\nu / 2)^{\nu / 2}}{\Gamma (\nu / 2)} s^\nu y^{- (\nu / 2 + 1)} \exp^{-\nu s^2 / (2y)} \right) \\
       &=& \frac{\nu}{2} \log(\frac{\nu}{2}) - \log (\Gamma (\nu / 2)) + \nu \log(s) - (\frac{\nu}{2} + 1) \log(y) - \frac{\nu s^2}{2y} \\
       & & \mathrm{ where } \; y > 0
     \f}
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @param s Scale parameter.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if s is not greater than or equal to 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof>::type
    scaled_inv_chi_square_log(const T_y& y, const T_dof& nu, const T_scale& s) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (s <= 0) {
	std::ostringstream err;
	err << "s (" << s << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }      
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      T_dof half_nu = 0.5 * nu;
      return - lgamma(half_nu)
	+ (half_nu) * log(half_nu)
	+ nu * log(s)
	- (half_nu + 1.0) * log(y)
	- half_nu * s * s / y;
    }
    /**
     * The log of a distribution proportional to a scaled inverse chi-squared density for y with the specified
     * degrees of freedom parameter and scale parameter.
     * The degrees of freedom prarameter must be greater than 0. The scale parameter must be greater
     * than 0.
     * y must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @param s Scale parameter.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if s is not greater than or equal to 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof>::type
    scaled_inv_chi_square_propto_log(const T_y& y, const T_dof& nu, const T_scale& s) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (s <= 0) {
	std::ostringstream err;
	err << "s (" << s << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }      
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return scaled_inv_chi_square_log(y, nu, s);
    }
    /**
     * The log of a distribution proportional to a scaled inverse chi-squared density for y with the specified
     * degrees of freedom parameter and scale parameter.
     * The degrees of freedom prarameter must be greater than 0. The scale parameter must be greater
     * than 0.
     * y must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @param s Scale parameter.
     * @throw std::domain_error if nu is not greater than or equal to 0
     * @throw std::domain_error if s is not greater than or equal to 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof>::type
    scaled_inv_chi_square_propto_log(stan::agrad::var& lp, const T_y& y, const T_dof& nu, const T_scale& s) {
      if (nu <= 0) {
	std::ostringstream err;
	err << "nu (" << nu << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (s <= 0) {
	std::ostringstream err;
	err << "s (" << s << " must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }      
      if (y <= 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += scaled_inv_chi_square_propto_log(y, nu, s);
    }


    /**
     * The log of an exponential density for y with the specified
     * inverse scale parameter.
     * Inverse scale parameter must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     \f{eqnarray*}{
       y &\sim& \mathrm{Expon}(\beta) \\
       \log (p (y \,|\, \beta) ) &=& \log \left( \beta \exp^{-\beta y} \right) \\
       &=& \log (\beta) - \beta y \\
       & & \mathrm{where} \; y > 0
     \f}
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_inv_scale>
    inline typename boost::math::tools::promote_args<T_y,T_inv_scale>::type
    exponential_log(const T_y& y, const T_inv_scale& beta) {
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than or equal to 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return log(beta)
	- beta * y;
    }
    /**
     * The log of a distribution proportional to an exponential density for y with the specified
     * inverse scale parameter.
     * Inverse scale parameter must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_inv_scale>
    inline typename boost::math::tools::promote_args<T_y,T_inv_scale>::type
    exponential_propto_log(const T_y& y, const T_inv_scale& beta) {
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than or equal to 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      return exponential_log (y, beta);
    }
    /**
     * The log of a distribution proportional to an exponential density for y with the specified
     * inverse scale parameter.
     * Inverse scale parameter must be greater than 0.
     * y must be greater than or equal to 0.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param alpha Shape parameter.
     * @param beta Inverse scale parameter.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_shape Type of shape.
     * @tparam T_inv_scale Type of inverse scale.
     */
    template <typename T_y, typename T_inv_scale>
    inline void
    exponential_propto_log(stan::agrad::var& lp, const T_y& y, const T_inv_scale& beta) {
      if (beta <= 0) {
	std::ostringstream err;
	err << "beta (" << beta << ") must be greater than 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      if (y < 0) {
	std::ostringstream err;
	err << "y (" << y << ") must be greater than or equal to 0";
	BOOST_THROW_EXCEPTION(std::domain_error (err.str()));
      }
      lp += exponential_propto_log (y, beta);
    }



    // StudentT(y|nu,mu,sigma)  [nu > 0;   sigma > 0]
    /**
     * The log of the Student-t density for the given y, nu, mean, and
     * scale parameter.  The scale parameter must be greater
     * than 0.
     *
     * \f{eqnarray*}{
       y &\sim& t_{\nu} (\mu, \sigma^2) \\
       \log (p (y \,|\, \nu, \mu, \sigma) ) &=& \log \left( \frac{\Gamma((\nu + 1) /2)}
           {\Gamma(\nu/2)\sqrt{\nu \pi} \sigma} \left( 1 + \frac{1}{\nu} (\frac{y - \mu}{\sigma})^2 \right)^{-(\nu + 1)/2} \right) \\
       &=& \log( \Gamma( (\nu+1)/2 )) - \log (\Gamma (\nu/2) - \frac{1}{2} \log(\nu \pi) - \log(\sigma)
           -\frac{\nu + 1}{2} \log (1 + \frac{1}{\nu} (\frac{y - \mu}{\sigma})^2)
     \f}
     * 
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @param mu The mean of the Student-t distribution.
     * @param sigma The scale parameter of the Student-t distribution.
     * @return The log of the Student-t density at y.
     * @throw std::domain_error if sigma is not greater than 0.
     * @throw std::domain_error if nu is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, 
	      typename T_dof, 
	      typename T_loc, 
	      typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof,T_loc,T_scale>::type
    student_t_log(const T_y& y, const T_dof& nu, const T_loc& mu, const T_scale& sigma) {
      // FIXME: checks on parameters
      return lgamma((nu + 1.0) / 2.0)
	- lgamma(nu / 2.0)
	- 0.5 * log(nu)
	+ NEG_LOG_SQRT_PI
	- log(sigma)
	- ((nu + 1.0) / 2.0) * log(1.0 + (((y - mu) / sigma) * ((y - mu) / sigma)) / nu);
    }
    /**
     * The log of a density proportional to the Student-t density for the given y, nu,
     * mean, and scale parameter.  The scale parameter must be greater than 0.
     * 
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @param mu The mean of the Student-t distribution.
     * @param sigma The scale parameter of the Student-t distribution.
     * @return The log of the Student-t density at y.
     * @throw std::domain_error if sigma is not greater than 0.
     * @throw std::domain_error if nu is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, 
	      typename T_dof, 
	      typename T_loc, 
	      typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof,T_loc,T_scale>::type
    student_t_propto_log(const T_y& y, const T_dof& nu, const T_loc& mu, const T_scale& sigma) {
      // FIXME: checks on parameters
      return student_t_log (y, nu, mu, sigma);
    }
    /**
     * The log of a density proportional to the Student-t density for the given y, nu,
     * mean, and scale parameter.  The scale parameter must be greater than 0.
     * 
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param nu Degrees of freedom.
     * @param mu The mean of the Student-t distribution.
     * @param sigma The scale parameter of the Student-t distribution.
     * @throw std::domain_error if sigma is not greater than 0.
     * @throw std::domain_error if nu is not greater than 0.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_loc Type of location.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, 
	      typename T_dof, 
	      typename T_loc, 
	      typename T_scale>
    inline void
    student_t_propto_log(stan::agrad::var& lp, const T_y& y, const T_dof& nu, const T_loc& mu, const T_scale& sigma) {
      // FIXME: checks on parameters
      lp += student_t_propto_log (y, nu, mu, sigma);
    }

    // Cauchy(y|mu,sigma)  [sigma > 0]
    template <typename T_y, typename T_loc, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_scale>::type
    cauchy_log(T_y y, T_loc mu, T_scale sigma) {
      return NEG_LOG_PI
	- log(sigma)
	- log(1.0 + (y - mu) * (y - mu) / (sigma * sigma));
    }

    // Beta(y|alpha,beta)  [alpha > 0;  beta > 0;  0 <= y <= 1]
    /**
     * The log of a beta density for y with the specified
     * prior sample sizes.
     * Prior sample sizes, alpha and beta, must be greater than 0.
     * y must be between 0 and 1 inclusive.
     * 
     \f{eqnarray*}{
       y &\sim& \mathrm{Beta}(\alpha, \beta) \\
       \log (p (y \,|\, \alpha, \beta) ) &=& \log \left( \frac{\Gamma(\alpha + \beta)}{\Gamma(\alpha) \Gamma(\beta)} y^{\alpha - 1} (1-y)^{\beta - 1} \right) \\
       &=& \log (\Gamma(\alpha + \beta)) - \log (\Gamma (\alpha) - \log(\Gamma(\beta)) + (\alpha-1) \log(y) + (\beta-1) \log(1 - y)
       & & \mathrm{where} \; y \in [0, 1]
     \f}
     * @param y A scalar variable.
     * @param alpha Prior sample size.
     * @param beta Prior sample size.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_alpha Type of prior sample size for alpha.
     * @tparam T_beta Type of prior sample size for beta.
     */
    template <typename T_y, typename T_alpha, typename T_beta>
    inline typename boost::math::tools::promote_args<T_y,T_alpha,T_beta>::type
    beta_log(const T_y& y, const T_alpha& alpha, const T_beta& beta) {
      return lgamma(alpha + beta)
	- lgamma(alpha)
	- lgamma(beta)
	+ (alpha - 1.0) * log(y)
	+ (beta - 1.0) * log(1.0 - y);
    }
    /**
     * The log of a distribution proportional to a beta density for y with the specified
     * prior sample sizes.
     * Prior sample sizes, alpha and beta, must be greater than 0.
     * y must be between 0 and 1 inclusive.
     *
     * @param y A scalar variable.
     * @param alpha Prior sample size.
     * @param beta Prior sample size.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_alpha Type of prior sample size for alpha.
     * @tparam T_beta Type of prior sample size for beta.
     */
    template <typename T_y, typename T_alpha, typename T_beta>
    inline typename boost::math::tools::promote_args<T_y,T_alpha,T_beta>::type
    beta_propto_log(const T_y& y, const T_alpha& alpha, const T_beta& beta) {
      return beta_log (y, alpha, beta);
    }
    /**
     * The log of a distribution proportional to a beta density for y with the specified
     * prior sample sizes.
     * Prior sample sizes, alpha and beta, must be greater than 0.
     * y must be between 0 and 1 inclusive.
     *
     * @param lp The log probability to increment.
     * @param y A scalar variable.
     * @param alpha Prior sample size.
     * @param beta Prior sample size.
     * @throw std::domain_error if alpha is not greater than 0.
     * @throw std::domain_error if beta is not greater than 0.
     * @throw std::domain_error if y is not greater than or equal to 0.
     * @tparam T_y Type of scalar.
     * @tparam T_alpha Type of prior sample size for alpha.
     * @tparam T_beta Type of prior sample size for beta.
     */
    template <typename T_y, typename T_alpha, typename T_beta>
    inline void
    beta_propto_log(stan::agrad::var& lp, const T_y& y, const T_alpha& alpha, const T_beta& beta) {
      lp += beta_propto_log (y, alpha, beta);
    }




    // Pareto(y|y_m,alpha)  [y > y_m;  y_m > 0;  alpha > 0]
    template <typename T_y, typename T_scale, typename T_shape>
    inline typename boost::math::tools::promote_args<T_y,T_scale,T_shape>::type
    pareto_log(T_y y, T_scale y_min, T_shape alpha) {
      return log(alpha)
	+ alpha * log(y_min)
	- (alpha + 1.0) * log(y);
    }

    // DoubleExponential(y|mu,sigma)  [sigma > 0]
    template <typename T_y, typename T_loc, typename T_scale> 
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_scale>::type
    double_exponential_log(T_y y, T_loc mu, T_scale sigma) {
      return NEG_LOG_TWO
	- log(sigma)
	- abs(y - mu) / sigma;
    }

    // Weibull(y|sigma,alpha)     [y >= 0;  sigma > 0;  alpha > 0]
    template <typename T_y, typename T_shape, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_shape,T_scale>::type
    weibull_log(T_y y, T_shape alpha, T_scale sigma) {
      return log(alpha)
	- log(sigma)
	+ (alpha - 1.0) * (log(y) - log(sigma))
	- pow(y / sigma, alpha);
    }

    // Logistic(y|mu,sigma)    [sigma > 0]
    template <typename T_y, typename T_loc, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_scale>::type
    logistic_log(T_y y, T_loc mu, T_scale sigma) {
      return -(y - mu)/sigma
	- log(sigma)
	- 2.0 * log(1.0 + exp(-(y - mu)/sigma));
    }

    // LogNormal(y|mu,sigma)  [y >= 0;  sigma > 0]
    template <typename T_y, typename T_loc, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_scale>::type
    lognormal_log(T_y y, T_loc mu, T_scale sigma) {
      return NEG_LOG_SQRT_TWO_PI
	- log(sigma)
	- log(y)
	- pow(log(y) - mu,2.0) / (2.0 * sigma * sigma);
    }
  

    // CONTINUOUS, MULTIIVARIATE

    // Dirichlet(theta|alpha)    [0 <= theta[n] <= 1;  SUM theta = 1;
    //                            0 < alpha[n]]
    template <typename T_prob, typename T_prior_sample_size> 
    inline typename boost::math::tools::promote_args<T_prob,T_prior_sample_size>::type
    dirichlet_log(Matrix<T_prob,Dynamic,1>& theta,
		  Matrix<T_prior_sample_size,Dynamic,1>& alpha) {
      typename boost::math::tools::promote_args<T_prob,T_prior_sample_size>::type log_p
	= lgamma(alpha.sum());
      for (int k = 0; k < alpha.rows(); ++k)
	log_p -= lgamma(alpha[k]);
      for (int k = 0; k < theta.rows(); ++k) 
	log_p += (alpha[k] - 1) * log(theta[k]);
      return log_p;
    }

    // MultiNormal(y|mu,Sigma)   [y.rows() = mu.rows() = Sigma.rows();
    //                            y.cols() = mu.cols() = 0;
    //                            Sigma symmetric, non-negative, definite]
    /**
     * The log of the multivariate normal density for the given y, mu, and
     * variance matrix. 
     * The variance matrix, Sigma, must be size d x d, symmetric,
     * and semi-positive definite. Dimension, d, is implicit.
     *
     * \f{eqnarray*}{
       y &\sim& N (\mu, \Sigma) \\
       \log (p (y \,|\, \mu, \Sigma) ) &=& \log \left( (2 \pi)^{-d/2} \left| \Sigma \right|^{-1/2} \times \exp \left(-\frac{1}{2}(y - \mu)^T \Sigma^{-1} (y - \mu) \right) \right) \\
       &=& -\frac{d}{2}\log (2 \pi) - \frac{1}{2} \log (\det(\Sigma)) - \frac{1}{2} (y - \mu)^T \Sigma^{-1} (y - \mu)
     \f}
     * 
     * 
     * @param y A scalar vector
     * @param mu The mean vector of the multivariate normal distribution.
     * @param Sigma The variance matrix of the multivariate normal distribution
     * @return The log of the multivariate normal density.
     * @throw std::domain_error if Sigma is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_covar Type of scale.
     */
    template <typename T_y, typename T_loc, typename T_covar> 
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_covar>::type
    multi_normal_log(const Matrix<T_y,Dynamic,1>& y,
		     const Matrix<T_loc,Dynamic,1>& mu,
		     const Matrix<T_covar,Dynamic,Dynamic>& Sigma) {
      if (!stan::prob::cov_matrix_validate(Sigma)) {
	std::ostringstream err;
	stan::prob::cov_matrix_validate(Sigma, err);
	BOOST_THROW_EXCEPTION (std::domain_error (err.str()));
      }
      return NEG_LOG_SQRT_TWO_PI * y.rows()
	- 0.5 * log(Sigma.determinant())
	- 0.5 * ((y - mu).transpose() * Sigma.inverse() * (y - mu))(0,0);
    }
    /**
     * The log of a density proportional to the multivariate normal density for the given y, mu, and
     * variance matrix. 
     * The variance matrix, Sigma, must be size d x d, symmetric,
     * and semi-positive definite. Dimension, d, is implicit.
     * 
     * @param y A scalar vector
     * @param mu The mean vector of the multivariate normal distribution.
     * @param Sigma The variance matrix of the multivariate normal distribution
     * @return The log of the multivariate normal density.
     * @throw std::domain_error if Sigma is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_covar Type of scale.
     */
    template <typename T_y, typename T_loc, typename T_covar> 
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_covar>::type
    multi_normal_propto_log(const Matrix<T_y,Dynamic,1>& y,
			    const Matrix<T_loc,Dynamic,1>& mu,
			    const Matrix<T_covar,Dynamic,Dynamic>& Sigma) {
      if (!stan::prob::cov_matrix_validate(Sigma)) {
	std::ostringstream err;
	stan::prob::cov_matrix_validate(Sigma, err);
	BOOST_THROW_EXCEPTION (std::domain_error (err.str()));
      }
      return multi_normal_log (y, mu, Sigma);
    }
    /**
     * The log of a density proportional to the multivariate normal density for the given y, mu, and
     * variance matrix. 
     * The variance matrix, Sigma, must be size d x d, symmetric,
     * and semi-positive definite. Dimension, d, is implicit.
     * 
     * @param lp The log probability to increment. 
     * @param y A scalar vector
     * @param mu The mean vector of the multivariate normal distribution.
     * @param Sigma The variance matrix of the multivariate normal distribution
     * @return The log of the multivariate normal density.
     * @throw std::domain_error if Sigma is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_covar Type of scale.
     */
    template <typename T_y, typename T_loc, typename T_covar> 
    inline void
    multi_normal_propto_log(stan::agrad::var &lp,
			    const Matrix<T_y,Dynamic,1>& y,
			    const Matrix<T_loc,Dynamic,1>& mu,
			    const Matrix<T_covar,Dynamic,Dynamic>& Sigma) {
      if (!stan::prob::cov_matrix_validate(Sigma)) {
	std::ostringstream err;
	stan::prob::cov_matrix_validate(Sigma, err);
	BOOST_THROW_EXCEPTION (std::domain_error (err.str()));
      }
      lp += multi_normal_propto_log (y, mu, Sigma);
    }

    // MultiNormal(y|mu,L)       [y.rows() = mu.rows() = L.rows() = L.cols();
    //                            y.cols() = mu.cols() = 0;
    //                            Sigma = LL' with L a Cholesky factor]
    /**
     * The log of the multivariate normal density for the given y, mu, and
     * L (a Cholesky factor of Sigma, a variance matrix).
     * Sigma = LL', a square, semi-positive definite matrix.
     * Dimension, d, is implicit.
     *
     * \f{eqnarray*}{
       y &\sim& N (\mu, LL') \\
       \log (p (y \,|\, \mu, L) ) &=& \log \left( (2 \pi)^{-d/2} \left| LL' \right|^{-1/2} \times \exp \left(-\frac{1}{2}(y - \mu)^T (LL')^{-1} (y - \mu) \right) \right)
     \f}
     * 
     * 
     * @param y A scalar vector
     * @param mu The mean vector of the multivariate normal distribution.
     * @param L The Cholesky decomposition of a variance matrix of the multivariate normal distribution
     * @return The log of the multivariate normal density.
     * @throw std::domain_error if LL' is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_covar Type of scale.
     */
    template <typename T_y, typename T_loc, typename T_covar> 
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_covar>::type
    multi_normal_log(const Matrix<T_y,Dynamic,1>& y,
		     const Matrix<T_loc,Dynamic,1>& mu,
		     const Eigen::TriangularView<T_covar,Eigen::Lower>& L) {
      // FIXME: checks on L
      Matrix<T_covar,Dynamic,1> half = L.solveTriangular(Matrix<T_covar,Dynamic,Dynamic>(L.rows(),L.rows()).setOnes()) * (y - mu);
      return NEG_LOG_SQRT_TWO_PI * y.rows() - log(L.diagonal().array().prod()) - 0.5 * half.dot(half);
    }
    /**
     * The log of the multivariate normal density for the given y, mu, and
     * L (a Cholesky factor of Sigma, a variance matrix).
     * Sigma = LL', a square, semi-positive definite matrix.
     * Dimension, d, is implicit.
     *
     * @param y A scalar vector
     * @param mu The mean vector of the multivariate normal distribution.
     * @param L The Cholesky decomposition of a variance matrix of the multivariate normal distribution
     * @return The log of the multivariate normal density.
     * @throw std::domain_error if LL' is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_covar Type of scale.
     */
    template <typename T_y, typename T_loc, typename T_covar> 
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_covar>::type
    multi_normal_propto_log(const Matrix<T_y,Dynamic,1>& y,
			    const Matrix<T_loc,Dynamic,1>& mu,
			    const Eigen::TriangularView<T_covar,Eigen::Lower>& L) {
      // FIXME: checks on L
      return multi_normal_log(y, mu, L);
    }
    /**
     * The log of the multivariate normal density for the given y, mu, and
     * L (a Cholesky factor of Sigma, a variance matrix).
     * Sigma = LL', a square, semi-positive definite matrix.
     * Dimension, d, is implicit.
     *
     * @param lp The log probability to increment.
     * @param y A scalar vector
     * @param mu The mean vector of the multivariate normal distribution.
     * @param L The Cholesky decomposition of a variance matrix of the multivariate normal distribution
     * @return The log of the multivariate normal density.
     * @throw std::domain_error if LL' is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_loc Type of location.
     * @tparam T_covar Type of scale.
     */
    template <typename T_y, typename T_loc, typename T_covar> 
    inline void
    multi_normal_propto_log(stan::agrad::var& lp,
			    const Matrix<T_y,Dynamic,1>& y,
			    const Matrix<T_loc,Dynamic,1>& mu,
			    const Eigen::TriangularView<T_covar,Eigen::Lower>& L) {
      // FIXME: checks on L
      lp += multi_normal_propto_log(y, mu, L);
    }
   
    namespace {
    }

    // Wishart(Sigma|n,Omega)  [Sigma, Omega symmetric, non-neg, definite; 
    //                          Sigma.dims() = Omega.dims();
    //                           n > Sigma.rows() - 1]
    /**
     * The log of the Wishart density for the given W, degrees of freedom, 
     * and scale matrix. 
     * 
     * The scale matrix, S, must be k x k, symmetric, and semi-positive definite.
     * Dimension, k, is implicit.
     * nu must be greater than k-1
     *
     * \f{eqnarray*}{
       W &\sim& \mathrm{Wishart}_{\nu} (S) \\
       \log (p (W \,|\, \nu, S) ) &=& \log \left( \left(2^{\nu k/2} \pi^{k (k-1) /4} \prod_{i=1}^k{\Gamma (\frac{\nu + 1 - i}{2})} \right)^{-1} 
                                                  \times \left| S \right|^{-\nu/2} \left| W \right|^{(\nu - k - 1) / 2}
						  \times \exp (-\frac{1}{2} \tr (S^{-1} W)) \right) \\
       &=& -\frac{\nu k}{2}\log(2) - \frac{k (k-1)}{4} \log(\pi) - \sum_{i=1}^{k}{\log (\Gamma (\frac{\nu+1-i}{2}))}
           -\frac{\nu}{2} \log(\det(S)) + \frac{\nu-k-1}{2}\log (\det(W)) - \frac{1}{2} \tr(S^{-1}W)
     \f}
     * 
     * 
     * @param W A scalar matrix
     * @param nu Degrees of freedom
     * @param S The scale matrix
     * @return The log of the Wishart density at W given nu and S.
     * @throw std::domain_error if nu is not greater than k-1
     * @throw std::domain_error if S is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof,T_scale>::type
    wishart_log(const Matrix<T_y,Dynamic,Dynamic>& W,
		const T_dof& nu,
		const Matrix<T_scale,Dynamic,Dynamic>& S) {
      // FIXME: domain checks
      unsigned int k = W.rows();
      if (nu <= k - 1) {
	std::ostringstream err;
	err << "nu (" << nu << ") must be greater than k-1 (" << k-1 << ")";
	BOOST_THROW_EXCEPTION (std::domain_error(err.str()));
      }
      if (nu == (k + 1)) {  
	// don't need W.determinant() term if n == k + 1
	return 	nu * k * NEG_LOG_TWO_OVER_TWO
	  - (0.5 * nu) * log(S.determinant())
	  - lmgamma(k, 0.5 * nu)
	  - 0.5 * abs((S.inverse() * W).trace());
      } else {
	return 0.5 * (nu - k - 1.0) * log(W.determinant())
	  + nu * k * NEG_LOG_TWO_OVER_TWO
	  - (0.5 * nu) * log(S.determinant())
	  - lmgamma(k, 0.5 * nu)
	  - 0.5 * abs((S.inverse() * W).trace());
      }
    }
    /**
     * The log of a density proportional to a Wishart density for the given W,
     * degrees of freedom, and scale matrix. 
     * The scale matrix, S, must be k x k, symmetric, and semi-positive definite.
     * Dimension, k, is implicit.
     * 
     * @param W A scalar matrix
     * @param nu Degrees of freedom
     * @param S The scale matrix
     * @return The log of the Wishart density at W given nu and S.
     * @throw std::domain_error if S is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof,T_scale>::type
    wishart_propto_log(const Matrix<T_y,Dynamic,Dynamic>& W,
		       const T_dof& nu,
		       const Matrix<T_scale,Dynamic,Dynamic>& S) {
      if (nu <= S.rows() - 1) {
	std::ostringstream err;
	err << "nu (" << nu << ") must be greater than k-1 (" << S.rows()-1 << ")";
	BOOST_THROW_EXCEPTION (std::domain_error(err.str()));
      }
      // FIXME: domain checks
      return wishart_log (W, nu, S);
    }
    /**
     * The log of a density proportional to a Wishart density for the given W,
     * degrees of freedom, and scale matrix. 
     * The scale matrix, S, must be k x k, symmetric, and semi-positive definite.
     * Dimension, k, is implicit.
     * 
     * @param lp The log probability to increment.
     * @param W A scalar matrix
     * @param nu Degrees of freedom
     * @param S The scale matrix
     * @return The log of the Wishart density at W given nu and S.
     * @throw std::domain_error if S is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline void
    wishart_propto_log(stan::agrad::var& lp, 
		       const Matrix<T_y,Dynamic,Dynamic>& W,
		       const T_dof& nu,
		       const Matrix<T_scale,Dynamic,Dynamic>& S) {
      if (nu <= S.rows() - 1) {
	std::ostringstream err;
	err << "nu (" << nu << ") must be greater than k-1 (" << S.rows()-1 << ")";
	BOOST_THROW_EXCEPTION (std::domain_error(err.str()));
      }
      // FIXME: domain checks
      lp += wishart_propto_log (W, nu, S);
    }

    // InvWishart(Sigma|n,Omega)  [W, S symmetric, non-neg, definite; 
    //                             W.dims() = S.dims();
    //                             n > S.rows() - 1]
    /**
     * The log of the Inverse-Wishart density for the given W, degrees of freedom, 
     * and scale matrix. 
     * 
     * The scale matrix, S, must be k x k, symmetric, and semi-positive definite.
     * Dimension, k, is implicit.
     * nu must be greater than k-1
     *
     * \f{eqnarray*}{
       W &\sim& \mathrm{Inv-Wishart}_{\nu} (S) \\
       \log (p (W \,|\, \nu, S) ) &=& \log \left( \left(2^{\nu k/2} \pi^{k (k-1) /4} \prod_{i=1}^k{\Gamma (\frac{\nu + 1 - i}{2})} \right)^{-1} 
                                                  \times \left| S \right|^{\nu/2} \left| W \right|^{-(\nu + k + 1) / 2}
						  \times \exp (-\frac{1}{2} \tr (S W^{-1})) \right) \\
       &=& -\frac{\nu k}{2}\log(2) - \frac{k (k-1)}{4} \log(\pi) - \sum_{i=1}^{k}{\log (\Gamma (\frac{\nu+1-i}{2}))}
           +\frac{\nu}{2} \log(\det(S)) - \frac{\nu+k+1}{2}\log (\det(W)) - \frac{1}{2} \tr(S W^{-1})
     \f}
     * 
     * 
     * @param W A scalar matrix
     * @param nu Degrees of freedom
     * @param S The scale matrix
     * @return The log of the Inverse-Wishart density at W given nu and S.
     * @throw std::domain_error if nu is not greater than k-1
     * @throw std::domain_error if S is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof,T_scale>::type
    inv_wishart_log(const Matrix<T_y,Dynamic,Dynamic>& W,
		    const T_dof& nu,
		    const Matrix<T_scale,Dynamic,Dynamic>& S) {
      unsigned int k = S.rows();
      if (nu <= k - 1) {
	std::ostringstream err;
	err << "nu (" << nu << ") must be greater than k-1 (" << k-1 << ")";
	BOOST_THROW_EXCEPTION (std::domain_error(err.str()));
      }
      return 0.5 * nu * log(S.determinant())
	- 0.5 * (nu + k + 1.0) * log(W.determinant())
	- 0.5 * (S * W.inverse()).trace()
	+  nu * k * NEG_LOG_TWO_OVER_TWO
	- lmgamma(k, 0.5 * nu);
    }
    /**
     * The log of a density proportional to the Inverse-Wishart density for 
     * the given W, degrees of freedom, and scale matrix. 
     * 
     * The scale matrix, S, must be k x k, symmetric, and semi-positive definite.
     * Dimension, k, is implicit.
     * nu must be greater than k-1
     *
     * @param W A scalar matrix
     * @param nu Degrees of freedom
     * @param S The scale matrix
     * @return The log of the Inverse-Wishart density at W given nu and S.
     * @throw std::domain_error if nu is not greater than k-1
     * @throw std::domain_error if S is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof,T_scale>::type
    inv_wishart_propto_log(const Matrix<T_y,Dynamic,Dynamic>& W,
			   const T_dof& nu,
			   const Matrix<T_scale,Dynamic,Dynamic>& S) {
      if (nu <= S.rows() - 1) {
	std::ostringstream err;
	err << "nu (" << nu << ") must be greater than k-1 (" << S.rows()-1 << ")";
	BOOST_THROW_EXCEPTION (std::domain_error(err.str()));
      }
      return inv_wishart_log (W, nu, S);
    }
    /**
     * The log of a density proportional to the Inverse-Wishart density for 
     * the given W, degrees of freedom, and scale matrix. 
     * 
     * The scale matrix, S, must be k x k, symmetric, and semi-positive definite.
     * Dimension, k, is implicit.
     * nu must be greater than k-1
     *
     * @param lp The log probability to increment.
     * @param W A scalar matrix
     * @param nu Degrees of freedom
     * @param S The scale matrix
     * @return The log of the Inverse-Wishart density at W given nu and S.
     * @throw std::domain_error if nu is not greater than k-1
     * @throw std::domain_error if S is not square, not symmetric, or not semi-positive definite.
     * @tparam T_y Type of scalar.
     * @tparam T_dof Type of degrees of freedom.
     * @tparam T_scale Type of scale.
     */
    template <typename T_y, typename T_dof, typename T_scale>
    inline typename boost::math::tools::promote_args<T_y,T_dof,T_scale>::type
    inv_wishart_propto_log(stan::agrad::var& lp,
			   const Matrix<T_y,Dynamic,Dynamic>& W,
			   const T_dof& nu,
			   const Matrix<T_scale,Dynamic,Dynamic>& S) {
      if (nu <= S.rows() - 1) {
	std::ostringstream err;
	err << "nu (" << nu << ") must be greater than k-1 (" << S.rows()-1 << ")";
	BOOST_THROW_EXCEPTION (std::domain_error(err.str()));
      }
      lp += inv_wishart_propto_log (W, nu, S);
    }
    // ?? write these in terms of cpcs rather than corr matrix
    
    // LKJ_Corr(y|eta) [ y correlation matrix (not covariance matrix)
    //                  eta > 0 ]
    template <typename T_y, typename T_shape>
    inline typename boost::math::tools::promote_args<T_y, T_shape>::type
    lkj_corr_log(Matrix<T_y,Dynamic,Dynamic> y,
		 T_shape eta) {

      // Lewandowski, Kurowicka, and Joe (2009) equations 15 and 16
      
      const unsigned int K = y.rows();
      T_shape the_sum = 0.0;
      T_shape constant = 0.0;
      T_shape beta_arg;
      
      if(eta == 1.0) {
	for(unsigned int k = 1; k < K; k++) { // yes, go from 1 to K - 1
	  beta_arg = 0.5 * (k + 1.0);
	  constant += k * beta_log(beta_arg, beta_arg);
	  the_sum += pow(static_cast<double>(k),2.0);
	}
	constant += the_sum * LOG_TWO;
	return constant;
      }

      T_shape diff;
      for(unsigned int k = 1; k < K; k++) { // yes, go from 1 to K - 1
	diff = K - k;
	beta_arg = eta + 0.5 * (diff - 1);
	constant += diff * beta_log(beta_arg, beta_arg);
	the_sum += (2.0 * eta - 2.0 + diff) * diff;
      }
      constant += the_sum * LOG_TWO;
      return (eta - 1.0) * log(y.determinant()) + constant;
    }

    // LKJ_cov(y|mu,sigma,eta) [ y covariance matrix (not correlation matrix)
    //                         mu vector, sigma > 0 vector, eta > 0 ]
    template <typename T_y, typename T_loc, typename T_scale, typename T_shape>
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_scale,T_shape>::type
    lkj_cov_log(Matrix<T_y,Dynamic,Dynamic> y,
		Matrix<T_loc,Dynamic,1> mu,
		Matrix<T_scale,Dynamic,1> sigma,
		T_shape eta) {

      const unsigned int K = y.rows();
      const Array<T_y,Dynamic,1> sds = y.diagonal().array().sqrt();
      T_shape log_prob = 0.0;
      for(unsigned int k = 0; k < K; k++) {
	log_prob += lognormal_log(log(sds(k,1)), mu(k,1), sigma(k,1));
      }
      if(eta == 1.0) {
	// no need to rescale y into a correlation matrix
	log_prob += lkj_corr_log(y,eta); 
	return log_prob;
      }
      DiagonalMatrix<double,Dynamic> D(K);
      D.diagonal() = sds.inverse();
      log_prob += lkj_corr_log(D * y * D, eta);
      return log_prob;
    }

    // LKJ_Cov(y|mu,sigma,eta) [ y covariance matrix (not correlation matrix)
    //                         mu scalar, sigma > 0 scalar, eta > 0 ]
    template <typename T_y, typename T_loc, typename T_scale, typename T_shape>
    inline typename boost::math::tools::promote_args<T_y,T_loc,T_scale,T_shape>::type
    lkj_cov_log(Matrix<T_y,Dynamic,Dynamic> y,
		T_loc mu, T_scale sigma, T_shape eta) {

      const unsigned int K = y.rows();
      const Array<T_y,Dynamic,1> sds = y.diagonal().array().sqrt();
      T_shape log_prob = 0.0;
      for(unsigned int k = 0; k < K; k++) {
	log_prob += lognormal_log(sds(k,1), mu, sigma);
      }
      if(eta == 1.0) {
	log_prob += lkj_corr_log(y,eta); // no need to rescale y into a correlation matrix
	return log_prob;
      }
      DiagonalMatrix<double,Dynamic> D(K);
      D.diagonal() = sds.inverse();
      log_prob += lkj_corr_log(D * y * D, eta);
      return log_prob;
    }

    // DISCRETE, UNIVARIATE MASS FUNCTIONS

    // Bernoulli(n|theta)   [0 <= n <= 1;   0 <= theta <= 1]
    template <typename T_prob> 
    inline typename boost::math::tools::promote_args<T_prob>::type
    bernoulli_log(unsigned int n, T_prob theta) {
      return log(n ? theta : (1.0 - theta));
    }

    // Categorical(n|theta)  [0 <= n < N;   0 <= theta[n] <= 1;  SUM theta = 1]
    template <typename T_prob>
    inline typename boost::math::tools::promote_args<T_prob>::type
    categorical_log(unsigned int n, Matrix<T_prob,Dynamic,1>& theta) {
      return log(theta(n));
    }

    // Binomial(n|N,theta)  [N >= 0;  0 <= n <= N;  0 <= theta <= 1]
    template <typename T_n, typename T_N, typename T_prob>
    inline typename boost::math::tools::promote_args<T_prob>::type
    binomial_log(T_n n, T_N N, T_prob theta) {
      return maths::binomial_coefficient_log<T_N>(N,n)
	+ n * log(theta)
	+ (N - n) * log(1.0 - theta);
    }

    // Poisson(n|lambda)  [lambda > 0;  n >= 0]
    template <typename T_rate>
    inline typename boost::math::tools::promote_args<T_rate>::type
    poisson_log(unsigned int n, T_rate lambda) {
      return - lgamma(n + 1.0)
	+ n * log(lambda)
	- lambda;
    }

    // NegBinomial(n|alpha,beta)  [alpha > 0;  beta > 0;  n >= 0]
    template <typename T_shape, typename T_inv_scale>
    inline typename boost::math::tools::promote_args<T_shape, T_inv_scale>::type
    neg_binomial_log(int n, T_shape alpha, T_inv_scale beta) {
      return maths::binomial_coefficient_log<T_shape>(n + alpha - 1.0, n)
	+ alpha * log(beta / (beta + 1.0))
	+ n * -log(beta + 1.0);
    }

    // BetaBinomial(n|alpha,beta) [alpha > 0;  beta > 0;  n >= 0]
    template <typename T_size>
    inline typename boost::math::tools::promote_args<T_size>::type
    beta_binomial_log(int n, int N, T_size alpha, T_size beta) {
      return maths::binomial_coefficient_log(N,n)
	+ maths::beta_log(n + alpha, N - n + beta)
	- maths::beta_log(alpha,beta);
    }

    // Hypergeometric(n|N,a,b)  [0 <= n <= a;  0 <= N-n <= b;  0 <= N <= a+b]
    // n: #white balls drawn;  N: #balls drawn;  a: #white balls;  b: #black balls
    double
    hypergeometric_log(unsigned int n, unsigned int N, 
		       unsigned int a, unsigned int b) {
      return maths::binomial_coefficient_log(a,n)
	+ maths::binomial_coefficient_log(b,N-n)
	- maths::binomial_coefficient_log(a+b,N);
    }

    // DISCRETE, MULTIVARIATE MASS FUNCTIONS

    // Multinomial(ns|N,theta)   [0 <= n <= N;  SUM ns = N;   
    //                            0 <= theta[n] <= 1;  SUM theta = 1]
    template <typename T_prob>
    inline typename boost::math::tools::promote_args<T_prob>::type
    multinomial_log(std::vector<int>& ns,
		    Matrix<T_prob,Dynamic,1>& theta) {
      unsigned int len = ns.size();
      double sum = 1.0;
      for (unsigned int i = 0; i < len; ++i) 
	sum += ns[i];
      typename boost::math::tools::promote_args<T_prob>::type log_p
	= lgamma(sum);
      for (unsigned int i = 0; i < len; ++i)
	log_p -= lgamma(ns[i] + 1.0);
      for (unsigned int i = 0; i < len; ++i)
	log_p += ns[i] * log(theta[i]);
      return log_p;
    }

    // LINEAR SCALE DENSITIES AND MASS FUNCTIONS
  
    double uniform(double y, double alpha, double beta) {
      return 1.0/(beta - alpha);
    }

    double normal(double y, double loc, double scale) {
      return exp(normal_log(y,loc,scale));
    }

    double gamma(double y, double alpha, double beta) {
      return exp(gamma_log(y,alpha,beta));
    }

    double chi_square(double y, double dof) {
      return exp(chi_square_log(y,dof));
    }

    double inv_chi_square(double y, double dof) {
      return exp(inv_chi_square_log(y,dof));
    }

    double scaled_inv_chi_square(double y, double nu, double s) {
      return exp(scaled_inv_chi_square_log(y,nu,s));
    }

    double exponential(double y, double beta) {
      return exp(exponential_log(y,beta));
    }

  }
}

#endif

