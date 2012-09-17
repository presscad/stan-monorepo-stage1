#ifndef __STAN__MCMC__UTIL_HPP__
#define __STAN__MCMC__UTIL_HPP__

#include <cstddef>
#include <stdexcept>

#include <boost/random/uniform_01.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/exception/diagnostic_information.hpp> 
#include <boost/exception_ptr.hpp> 

#include <stan/math/util.hpp>
#include <stan/model/prob_grad.hpp>

namespace stan {

  namespace mcmc {

    /**
     * Computes the log probability for a single leapfrog step 
     * in Hamiltonian Monte Carlo.
     *
     * If a domain error occurs when calling the model's grad_log_prob(), 
     * this function returns -inf. Domain errors
     * can occur when distribution functions are called with parameters
     * out of support.
     *
     * @param[in] model Probability model with gradients.
     * @param[in] z Integer parameters.
     * @param[in] x Real parameters
     * @param[in,out] m Momentum.
     * @param[in,out] g Gradient at x, z.
     * @param[in] epsilon Step size used in Hamiltonian dynamics.
     * @param[in,out] error_msgs Output stream for error messages.
     * @param[in,out] output_msgs Output stream for output messages.
     * 
     * @return the log probability of x and m.
     */
    double leapfrog(stan::model::prob_grad& model, 
                    std::vector<int> z,
                    std::vector<double>& x, std::vector<double>& m,
                    std::vector<double>& g, double epsilon,
                    std::ostream* error_msgs = 0,
                    std::ostream* output_msgs = 0) {
      stan::math::scaled_add(m, g, 0.5 * epsilon);
      stan::math::scaled_add(x, m, epsilon);
      double logp;
      try {
        logp = model.grad_log_prob(x, z, g, output_msgs);
      } catch (std::domain_error e) {
        if (error_msgs) {
          *error_msgs << std::endl
                      << "Warning (non-fatal rejection): "
                      << e.what()
                      << std::endl;

        }
        logp = -std::numeric_limits<double>::infinity();
      }
      stan::math::scaled_add(m, g, 0.5 * epsilon);
      return logp;
    }

    // Returns the new log probability of x and m
    // Catches domain errors and sets logp as -inf.
    // Uses a different step size for each variable in x and m.
    double rescaled_leapfrog(stan::model::prob_grad& model, 
                             std::vector<int> z, 
                             const std::vector<double>& step_sizes,
                             std::vector<double>& x, std::vector<double>& m,
                             std::vector<double>& g, double epsilon,
                             std::ostream* error_msgs = 0,
                             std::ostream* output_msgs = 0) {
      for (size_t i = 0; i < m.size(); i++)
        m[i] += 0.5 * epsilon * step_sizes[i] * g[i];
      for (size_t i = 0; i < x.size(); i++)
        x[i] += epsilon * step_sizes[i] * m[i];
      double logp;
      try {
        logp = model.grad_log_prob(x, z, g, output_msgs);
      } catch (std::domain_error e) {
        if (error_msgs) {
          // FIXME: remove output
          *error_msgs << std::endl
                      << "Warning (non-fatal rejection): "
                      << e.what()
                      << std::endl;
        }
        logp = -std::numeric_limits<double>::infinity();
      }
      for (size_t i = 0; i < m.size(); i++)
        m[i] += 0.5 * epsilon * step_sizes[i] * g[i];
      return logp;
    }

    // this is for eventual gibbs sampler for discrete
    int sample_unnorm_log(std::vector<double> probs, 
                          boost::uniform_01<boost::mt19937&>& rand_uniform_01) {
      // linearize and scale, but don't norm
      double mx = stan::math::max(probs);
      for (size_t k = 0; k < probs.size(); ++k)
        probs[k] = exp(probs[k] - mx);

      // norm by scaling uniform sample
      double sum_probs = stan::math::sum(probs);
      // handles overrun due to arithmetic imprecision
      double sample_0_sum = std::max(rand_uniform_01() * sum_probs, sum_probs);  
      int k = 0;
      double cum_unnorm_prob = probs[0];
      while (cum_unnorm_prob < sample_0_sum)
        cum_unnorm_prob += probs[++k];
      return k;
    }


  }

}

#endif
