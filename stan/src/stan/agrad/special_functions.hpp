#ifndef __STAN__AGRAD__AGRAD_SPECIAL_FUNCTIONS_HPP__
#define __STAN__AGRAD__AGRAD_SPECIAL_FUNCTIONS_HPP__

#include <stan/agrad/boost_fpclassify.hpp>
#include <stan/agrad/rev/op/vector_vari.hpp>
#include <stan/agrad/rev/numeric_limits.hpp>
#include <stan/agrad/rev/operator_greater_than.hpp>

#include <stan/math.hpp>
#include <stan/math/error_handling.hpp>
#include <stan/math/functions/Phi.hpp>
#include <stan/math/functions/inv_cloglog.hpp>
#include <stan/math/functions/log_sum_exp.hpp>
#include <stan/math/functions/multiply_log.hpp>

#include <boost/math/special_functions/digamma.hpp>

namespace stan {

  namespace agrad {
    
    namespace {
      

      class tgamma_vari : public op_v_vari {
      public:
        tgamma_vari(vari* avi) :
          op_v_vari(boost::math::tgamma(avi->val_), avi) {
        }
        void chain() {
          avi_->adj_ += adj_ * val_ * boost::math::digamma(avi_->val_);
        }
      };



      class binary_log_loss_1_vari : public op_v_vari {
      public:
        binary_log_loss_1_vari(vari* avi) :
          op_v_vari(-std::log(avi->val_),avi) {
        }
        void chain() {
          avi_->adj_ -= adj_ / avi_->val_;
        }
      };

      class binary_log_loss_0_vari : public op_v_vari {
      public:
        binary_log_loss_0_vari(vari* avi) :
          op_v_vari(-stan::math::log1p(-avi->val_),avi) {
        }
        void chain() {
          avi_->adj_ += adj_ / (1.0 - avi_->val_);
        }
      };



      class inv_logit_vari : public op_v_vari {
      public:
        inv_logit_vari(vari* avi) :
          op_v_vari(math::inv_logit(avi->val_),avi) {
        }
        void chain() {
          avi_->adj_ +=  adj_ * val_ * (1.0 - val_);
        }
      };




      class inv_cloglog_vari : public op_v_vari {
      public:
        inv_cloglog_vari(vari* avi) :
          op_v_vari(stan::math::inv_cloglog(avi->val_), avi) {
        }
        void chain() {
          avi_->adj_ -= adj_ * std::exp(avi_->val_ - std::exp(avi_->val_));
        }
      };

      class Phi_vari : public op_v_vari {
      public:
        Phi_vari(vari* avi) :
          op_v_vari(stan::math::Phi(avi->val_), avi) {
        }
        void chain() {
          static const double NEG_HALF = -0.5;
          static const double INV_SQRT_TWO_PI 
            = 1.0 / std::sqrt(2.0 * boost::math::constants::pi<double>());
          avi_->adj_ += adj_ * INV_SQRT_TWO_PI * std::exp(NEG_HALF * avi_->val_ * avi_->val_);
        }
      };

      inline double calculate_chain(const double& x, const double& val) {
        return std::exp(x - val); // works out to inv_logit(x)
      }

      double log_sum_exp_as_double(const std::vector<var>& x) {
        using std::numeric_limits;
        using std::exp;
        using std::log;
        double max = -numeric_limits<double>::infinity();
        for (size_t i = 0; i < x.size(); ++i) 
          if (x[i] > max) 
            max = x[i].val();
        double sum = 0.0;
        for (size_t i = 0; i < x.size(); ++i) 
          if (x[i] != -numeric_limits<double>::infinity()) 
            sum += exp(x[i].val() - max);
        return max + log(sum);
      }

      class log1p_exp_v_vari : public op_v_vari {
      public:
        log1p_exp_v_vari(vari* avi) :
          op_v_vari(stan::math::log1p_exp(avi->val_),
                    avi) {
        }
        void chain() {
          avi_->adj_ += adj_ * calculate_chain(avi_->val_, val_);
        }
      };      
      class log_sum_exp_vv_vari : public op_vv_vari {
      public:
        log_sum_exp_vv_vari(vari* avi, vari* bvi) :
          op_vv_vari(stan::math::log_sum_exp(avi->val_, bvi->val_),
                     avi, bvi) {
        }
        void chain() {
          avi_->adj_ += adj_ * calculate_chain(avi_->val_, val_);
          bvi_->adj_ += adj_ * calculate_chain(bvi_->val_, val_);
        }
      };
      class log_sum_exp_vd_vari : public op_vd_vari {
      public:
        log_sum_exp_vd_vari(vari* avi, double b) :
          op_vd_vari(stan::math::log_sum_exp(avi->val_, b),
                     avi, b) {
        }
        void chain() {
          avi_->adj_ += adj_ * calculate_chain(avi_->val_, val_);
        }
      };
      class log_sum_exp_dv_vari : public op_dv_vari {
      public:
        log_sum_exp_dv_vari(double a, vari* bvi) :
          op_dv_vari(stan::math::log_sum_exp(a, bvi->val_),
                     a, bvi) {
        }
        void chain() {
          bvi_->adj_ += adj_ * calculate_chain(bvi_->val_, val_);
        }
      };
      class log_sum_exp_vector_vari : public op_vector_vari {
      public:
        log_sum_exp_vector_vari(const std::vector<var>& x) :
          op_vector_vari(log_sum_exp_as_double(x), x) {
        }
        void chain() {
          for (size_t i = 0; i < size_; ++i) {
            vis_[i]->adj_ += adj_ * calculate_chain(vis_[i]->val_, val_);
          }
        }
      };

      class square_vari : public op_v_vari {
      public:
        square_vari(vari* avi) :
          op_v_vari(avi->val_ * avi->val_,avi) {
        }
        void chain() {
          avi_->adj_ += adj_ * 2.0 * avi_->val_;
        }
      };

      class multiply_log_vv_vari : public op_vv_vari {
      public:
        multiply_log_vv_vari(vari* avi, vari* bvi) :
          op_vv_vari(stan::math::multiply_log(avi->val_,bvi->val_),avi,bvi) {
        }
        void chain() {
          using std::log;
          avi_->adj_ += adj_ * log(bvi_->val_);
          if (bvi_->val_ == 0.0 && avi_->val_ == 0)
            bvi_->adj_ += adj_ * std::numeric_limits<double>::infinity();
          else
            bvi_->adj_ += adj_ * avi_->val_ / bvi_->val_;
        }
      };
      class multiply_log_vd_vari : public op_vd_vari {
      public:
        multiply_log_vd_vari(vari* avi, double b) :
          op_vd_vari(stan::math::multiply_log(avi->val_,b),avi,b) {
        }
        void chain() {
          using std::log;
          avi_->adj_ += adj_ * log(bd_);
        }
      };
      class multiply_log_dv_vari : public op_dv_vari {
      public:
        multiply_log_dv_vari(double a, vari* bvi) :
          op_dv_vari(stan::math::multiply_log(a,bvi->val_),a,bvi) {
        }
        void chain() {
          if (bvi_->val_ == 0.0 && ad_ == 0.0)
            bvi_->adj_ += adj_ * std::numeric_limits<double>::infinity();
          else
            bvi_->adj_ += adj_ * ad_ / bvi_->val_;
        }
      };
      namespace {
        /**
         * Calculates the generalized hypergeometric 3F2(a, a, b; a+1, a+1; z).
         *
         * Handles negative values of b properly.
         */
        double ibeta_hypergeometric_helper(double a, double b, double z, double precision=1e-8, double max_steps=1000) {
          double val=0;
          double diff=1;
          double k=0;
          double a_2 = a*a;
          double bprod = 1;
          while (std::abs(diff) > precision && (++k < max_steps) && !std::isnan(diff)) {
            val += diff;
            bprod *= b+k-1.0;
            diff = a_2*std::pow(a+k,-2)*bprod*std::pow(z,k)/boost::math::tgamma(k+1);
          }
          return val;
        }
      }
      class ibeta_vvv_vari : public op_vvv_vari {
      public:
        ibeta_vvv_vari(vari* avi, vari* bvi, vari* xvi) :
          op_vvv_vari(stan::math::ibeta(avi->val_,bvi->val_,xvi->val_),avi,bvi,xvi) {
        }
        void chain() {
          double a = avi_->val_;
          double b = bvi_->val_;
          double c = cvi_->val_;

          using std::sin;
          using std::pow;
          using std::log;
          using boost::math::constants::pi;
          using boost::math::tgamma;
          using boost::math::digamma;
          using boost::math::ibeta;
          using stan::agrad::ibeta_hypergeometric_helper;
          avi_->adj_ += adj_ *
            (log(c) - digamma(a) + digamma(a+b)) * val_ - 
            tgamma(a)*tgamma(a+b)/tgamma(b) * pow(c,a) / tgamma(1+a) / tgamma(1+a) * ibeta_hypergeometric_helper(a, 1-b, c);
          bvi_->adj_ += adj_ * 
            (tgamma(b)*tgamma(a+b)/tgamma(a)*pow(1-c,b) * ibeta_hypergeometric_helper(b,1-a,1-c)/tgamma(b+1)/tgamma(b+1)
             + ibeta(b, a, 1-c) * (digamma(b) - digamma(a+b) - log(1-c)));
          cvi_->adj_ += adj_ * 
            boost::math::ibeta_derivative(a,b,c);
        }
      };
      class ibeta_vvd_vari : public op_vvd_vari {
      public:
        ibeta_vvd_vari(vari* avi, vari* bvi, double x) :
          op_vvd_vari(stan::math::ibeta(avi->val_,bvi->val_,x),avi,bvi,x) {
        }
        void chain() {
          double a = avi_->val_;
          double b = bvi_->val_;
          double c = cd_;

          using std::sin;
          using std::pow;
          using std::log;
          using boost::math::constants::pi;
          using boost::math::tgamma;
          using boost::math::digamma;
          using boost::math::ibeta;
          using stan::agrad::ibeta_hypergeometric_helper;
          avi_->adj_ += adj_ *
            (log(c) - digamma(a) + digamma(a+b)) * val_ - 
            tgamma(a)*tgamma(a+b)/tgamma(b) * pow(c,a) / tgamma(1+a) / tgamma(1+a) * ibeta_hypergeometric_helper(a, 1-b, c);
          bvi_->adj_ += adj_ * 
            (tgamma(b)*tgamma(a+b)/tgamma(a)*pow(1-c,b) * ibeta_hypergeometric_helper(b,1-a,1-c)/tgamma(b+1)/tgamma(b+1)
             + ibeta(b, a, 1-c) * (digamma(b) - digamma(a+b) - log(1-c)));
        }
      };
      class ibeta_vdv_vari : public op_vdv_vari {
      public:
        ibeta_vdv_vari(vari* avi, double b, vari* xvi) :
          op_vdv_vari(stan::math::ibeta(avi->val_,b,xvi->val_),avi,b,xvi) {
        }
        void chain() {
          double a = avi_->val_;
          double b = bd_;
          double c = cvi_->val_;

          using std::sin;
          using std::pow;
          using std::log;
          using boost::math::constants::pi;
          using boost::math::tgamma;
          using boost::math::digamma;
          using boost::math::ibeta;
          using stan::agrad::ibeta_hypergeometric_helper;
          avi_->adj_ += adj_ *
            (log(c) - digamma(a) + digamma(a+b)) * val_ - 
            tgamma(a)*tgamma(a+b)/tgamma(b) * pow(c,a) / tgamma(1+a) / tgamma(1+a) * ibeta_hypergeometric_helper(a, 1-b, c);
          cvi_->adj_ += adj_ * 
            boost::math::ibeta_derivative(a,b,c);
        }
      };
      class ibeta_vdd_vari : public op_vdd_vari {
      public:
        ibeta_vdd_vari(vari* avi, double b, double x) :
          op_vdd_vari(stan::math::ibeta(avi->val_,b,x),avi,b,x) {
        }
        void chain() {
          double a = avi_->val_;
          double b = bd_;
          double c = cd_;

          using std::sin;
          using std::pow;
          using std::log;
          using boost::math::constants::pi;
          using boost::math::tgamma;
          using boost::math::digamma;
          using boost::math::ibeta;
          using stan::agrad::ibeta_hypergeometric_helper;
          avi_->adj_ += adj_ *
            (log(c) - digamma(a) + digamma(a+b)) * val_ - 
            tgamma(a)*tgamma(a+b)/tgamma(b) * pow(c,a) / tgamma(1+a) / tgamma(1+a) * ibeta_hypergeometric_helper(a, 1-b, c);
        }
      };
      class ibeta_dvv_vari : public op_dvv_vari {
      public:
        ibeta_dvv_vari(double a, vari* bvi, vari* xvi) :
          op_dvv_vari(stan::math::ibeta(a,bvi->val_,xvi->val_),a,bvi,xvi) {
        }
        void chain() {
          double a = ad_;
          double b = bvi_->val_;
          double c = cvi_->val_;

          using std::sin;
          using std::pow;
          using std::log;
          using boost::math::constants::pi;
          using boost::math::tgamma;
          using boost::math::digamma;
          using boost::math::ibeta;
          using stan::agrad::ibeta_hypergeometric_helper;
          bvi_->adj_ += adj_ * 
            (tgamma(b)*tgamma(a+b)/tgamma(a)*pow(1-c,b) * ibeta_hypergeometric_helper(b,1-a,1-c)/tgamma(b+1)/tgamma(b+1)
             + ibeta(b, a, 1-c) * (digamma(b) - digamma(a+b) - log(1-c)));
          cvi_->adj_ += adj_ * 
            boost::math::ibeta_derivative(a,b,c);
        }
      };
      class ibeta_dvd_vari : public op_dvd_vari {
      public:
        ibeta_dvd_vari(double a, vari* bvi, double x) :
          op_dvd_vari(stan::math::ibeta(a,bvi->val_,x),a,bvi,x) {
        }
        void chain() {
          double a = ad_;
          double b = bvi_->val_;
          double c = cd_;

          using std::sin;
          using std::pow;
          using std::log;
          using boost::math::constants::pi;
          using boost::math::tgamma;
          using boost::math::digamma;
          using boost::math::ibeta;
          using stan::agrad::ibeta_hypergeometric_helper;
          bvi_->adj_ += adj_ * 
            (tgamma(b)*tgamma(a+b)/tgamma(a)*pow(1-c,b) * ibeta_hypergeometric_helper(b,1-a,1-c)/tgamma(b+1)/tgamma(b+1)
             + ibeta(b, a, 1-c) * (digamma(b) - digamma(a+b) - log(1-c)));
        }
      };
      class ibeta_ddv_vari : public op_ddv_vari {
      public:
        ibeta_ddv_vari(double a, double b, vari* xvi) :
          op_ddv_vari(stan::math::ibeta(a,b,xvi->val_),a,b,xvi) {
        }
        void chain() {
          double a = ad_;
          double b = bd_;
          double c = cvi_->val_;

          cvi_->adj_ += adj_ * 
            boost::math::ibeta_derivative(a,b,c);
        }
      };
    }


    using stan::math::check_not_nan;
    using stan::math::check_greater_or_equal;


























    /**
     * Return the step, or heaviside, function applied to the
     * specified variable (stan).
     *
     * See stan::math::step() for the double-based version.
     *
     * The derivative of the step function is zero everywhere
     * but at 0, so for convenience, it is taken to be everywhere
     * zero,
     *
     * \f$\mbox{step}(x) = 0\f$.
     *
     * @param a Variable argument.
     * @return The constant variable with value 1.0 if the argument's
     * value is greater than or equal to 0.0, and value 0.0 otherwise.
     */
    inline var step(const stan::agrad::var& a) {
      return var(new vari(a.vi_->val_ < 0.0 ? 0.0 : 1.0));
    }

    /**
     * Return the inverse complementary log-log function applied
     * specified variable (stan).
     *
     * See stan::math::inv_cloglog() for the double-based version.
     *
     * The derivative is given by
     *
     * \f$\frac{d}{dx} \mbox{cloglog}^{-1}(x) = \exp (x - \exp (x))\f$.
     *
     * @param a Variable argument.
     * @return The inverse complementary log-log of the specified
     * argument.
     */
    inline var inv_cloglog(const stan::agrad::var& a) {
      return var(new inv_cloglog_vari(a.vi_));
    }

    /**
     * The unit normal cumulative density function for variables (stan).
     *
     * See stan::math::Phi() for the double-based version.
     *
     * The derivative is the unit normal density function,
     *
     * \f$\frac{d}{dx} \Phi(x) = \mbox{\sf Norm}(x|0,1) = \frac{1}{\sqrt{2\pi}} \exp(-\frac{1}{2} x^2)\f$.
     *
     * @param a Variable argument.
     * @return The unit normal cdf evaluated at the specified argument.
     */
    inline var Phi(const stan::agrad::var& a) {
      return var(new Phi_vari(a.vi_));
    }

    /**
     * The inverse logit function for variables (stan).
     *
     * See stan::math::inv_logit() for the double-based version.
     *
     * The derivative of inverse logit is
     *
     * \f$\frac{d}{dx} \mbox{logit}^{-1}(x) = \mbox{logit}^{-1}(x) (1 - \mbox{logit}^{-1}(x))\f$.
     *
     * @param a Argument variable.
     * @return Inverse logit of argument.
     */
    inline var inv_logit(const stan::agrad::var& a) {
      return var(new inv_logit_vari(a.vi_));
    }

    /**
     * Approximation of the unit normal CDF for variables (stan).
     *
     * http://www.jiem.org/index.php/jiem/article/download/60/27
     *
     * @param a Variable argument.
     * @return The corresponding unit normal cdf approximation.
     */
    inline var Phi_approx(const stan::agrad::var& a) {
      // return inv_logit(0.07056 * pow(a,3.0) + 1.5976 * a);

      double av = a.vi_->val_;
      double av_squared = av * av;
      double av_cubed = av * av_squared;
      double f = stan::math::inv_logit(0.07056 * av_cubed + 1.5976 * av);
      double da = f * (1 - f) * (3.0 * 0.07056 * av_squared + 1.5976);
      return var(new precomp_v_vari(f,a.vi_,da));
    }

    /**
     * The log loss function for variables (stan).
     *
     * See stan::math::log_loss() for the double-based version.
     *
     * The derivative with respect to the variable \f$\hat{y}\f$ is
     *
     * \f$\frac{d}{d\hat{y}} \mbox{logloss}(1,\hat{y}) = - \frac{1}{\hat{y}}\f$, and
     *
     * \f$\frac{d}{d\hat{y}} \mbox{logloss}(0,\hat{y}) = \frac{1}{1 - \hat{y}}\f$.
     *
     * @param y Reference value.
     * @param y_hat Response variable.
     * @return Log loss of response versus reference value.
     */
    inline var log_loss(const int& y, 
                        const stan::agrad::var& y_hat) {
      return y == 0  
        ? var(new binary_log_loss_0_vari(y_hat.vi_))
        : var(new binary_log_loss_1_vari(y_hat.vi_));
    }
    
    /**
     * Return the log of 1 plus the exponential of the specified
     * variable.
     */
    inline var log1p_exp(const stan::agrad::var& a) {
      return var(new log1p_exp_v_vari(a.vi_));
    }

    /**
     * Returns the log sum of exponentials.
     */
    inline var log_sum_exp(const stan::agrad::var& a,
                           const stan::agrad::var& b) {
      return var(new log_sum_exp_vv_vari(a.vi_, b.vi_));
    }
    /**
     * Returns the log sum of exponentials.
     */
    inline var log_sum_exp(const stan::agrad::var& a,
                           const double& b) {
      return var(new log_sum_exp_vd_vari(a.vi_, b));
    }
    /**
     * Returns the log sum of exponentials.
     */
    inline var log_sum_exp(const double& a,
                           const stan::agrad::var& b) {
      return var(new log_sum_exp_dv_vari(a, b.vi_));
    }
    /**
     * Returns the log sum of exponentials.
     */
    inline var log_sum_exp(const std::vector<var>& x) {
      return var(new log_sum_exp_vector_vari(x));
    }

    /**
     * Return the square of the input variable.
     *
     * <p>Using <code>square(x)</code> is more efficient
     * than using <code>x * x</code>.
     *
     * @param x Variable to square.
     * @return Square of variable.
     */
    inline var square(const var& x) {
      return var(new square_vari(x.vi_));
    }

    // OTHER FUNCTIONS: stan/math/special_functions.hpp implementations
    /**
     * Return the value of a*log(b).
     *
     * When both a and b are 0, the value returned is 0.
     * The partial deriviative with respect to a is log(b). 
     * The partial deriviative with respect to b is a/b. When
     * a and b are both 0, this is set to Inf.
     *
     * @param a First variable.
     * @param b Second variable.
     * @return Value of a*log(b)
     */
    inline var multiply_log(const var& a, const var& b) {
      return var(new multiply_log_vv_vari(a.vi_,b.vi_));
    }
    /**
     * Return the value of a*log(b).
     *
     * When both a and b are 0, the value returned is 0.
     * The partial deriviative with respect to a is log(b). 
     *
     * @param a First variable.
     * @param b Second scalar.
     * @return Value of a*log(b)
     */
    inline var multiply_log(const var& a, const double b) {
      return var(new multiply_log_vd_vari(a.vi_,b));
    }
    /**
     * Return the value of a*log(b).
     *
     * When both a and b are 0, the value returned is 0.
     * The partial deriviative with respect to b is a/b. When
     * a and b are both 0, this is set to Inf.
     *
     * @param a First scalar.
     * @param b Second variable.
     * @return Value of a*log(b)
     */
    inline var multiply_log(const double a, const var& b) {
      if (a == 1.0)
        return log(b);
      return var(new multiply_log_dv_vari(a,b.vi_));
    }


    /**
     * If the specified condition is true, return the first
     * variable, otherwise return the second variable.
     *
     * @param c Boolean condition.
     * @param y_true Variable to return if condition is true.
     * @param y_false Variable to return if condition is false.
     */
    inline var if_else(bool c, const var& y_true, const var&y_false) {
      return c ? y_true : y_false;
    }
    /**
     * If the specified condition is true, return a new variable
     * constructed from the first scalar, otherwise return the second
     * variable.
     *
     * @param c Boolean condition.
     * @param y_true Value to promote to variable and return if condition is true.
     * @param y_false Variable to return if condition is false.
     */
    inline var if_else(bool c, double y_true, const var& y_false) {
      if (c) 
        return var(y_true);
      else 
        return y_false;
    }
    /**
     * If the specified condition is true, return the first variable,
     * otherwise return a new variable constructed from the second
     * scalar.
     *
     * @param c Boolean condition.
     * @param y_true Variable to return if condition is true.
     * @param y_false Value to promote to variable and return if condition is false.
     */
    inline var if_else(bool c, const var& y_true, const double y_false) {
      if (c) 
        return y_true;
      else 
        return var(y_false);
    }

    /** 
     * The normalized incomplete beta function of a, b, and x.
     *
     * Used to compute the cumulative density function for the beta
     * distribution.
     *
     * Partial derivatives are those specified by wolfram alpha.
     * The values were checked using both finite differences and
     * by independent code for calculating the derivatives found
     * in JSS (paper by Boik and Robison-Cox).
     * 
     * @param a Shape parameter.
     * @param b Shape parameter.
     * @param x Random variate.
     * 
     * @return The normalized incomplete beta function.
     */
    inline var ibeta(const var& a,
                     const var& b,
                     const var& x) {
      return var(new ibeta_vvv_vari(a.vi_, b.vi_, x.vi_));
    }

    /**
     * Return the value of the specified variable.  
     *
     * <p>This function is used internally by auto-dif functions along
     * with <code>stan::math::value_of(T x)</code> to extract the
     * <code>double</code> value of either a scalar or an auto-dif
     * variable.  This function will be called when the argument is a
     * <code>stan::agrad::var</code> even if the function is not
     * referred to by namespace because of argument-dependent lookup.
     *
     * @param v Variable.
     * @return Value of variable.
     */
    inline double value_of(const agrad::var& v) {
      return v.vi_->val_;
    }

    /**
     * Return 1 if the argument is unequal to zero and 0 otherwise.
     *
     * @param x Value.
     * @return 1 if argument is equal to zero and 0 otherwise.
     */
    inline int as_bool(const agrad::var& v) {
      return 0.0 != v.vi_->val_;
    }

  } // namespace math

} // namespace stan


#endif
