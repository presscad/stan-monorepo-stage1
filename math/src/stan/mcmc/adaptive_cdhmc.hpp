#ifndef __STAN__MCMC__ADAPTIVE_CDHMC_H__
#define __STAN__MCMC__ADAPTIVE_CDHMC_H__

#include <ctime>
#include <cstddef>
#include <vector>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_01.hpp>

#include <stan/math/util.hpp>
#include <stan/mcmc/adaptive_sampler.hpp>
#include <stan/mcmc/dualaverage.hpp>
#include <stan/model/prob_grad.hpp>
#include <stan/mcmc/util.hpp>

namespace stan {

  namespace mcmc {

    /**
     * Adaptive "constant distance" Hamiltonian Monte Carlo 
     * (CDHMC) sampler.
     * 
     * adaptive_cdhmc requires specification of the trajectory length,
     * epsilon*L. CDHMC automatically tries to coerce the average
     * acceptance probability to some value, delta, by choosing the 
     * number of steps, L, given the step size, epsilon, to make the
     * trajectory length as close as possible to the target.
     *
     * The CDHMC sampler requires a probability model with the ability
     * to compute gradients, characterized as an instance of
     * <code>stan::model::prob_grad</code>.  
     *
     * Samples from the sampler are returned through the
     * base class <code>sampler</code>.
     */
    class adaptive_cdhmc : public adaptive_sampler {
    private:
      // Provides the target distribution we're trying to sample from
      stan::model::prob_grad& _model;
    
      // The most recent setting of the real-valued parameters
      std::vector<double> _x;
      // The most recent setting of the discrete parameters
      std::vector<int> _z;
      // The most recent gradient with respect to the real parameters
      std::vector<double> _g;
      // The most recent log-likelihood
      double _logp;

      // The step size used in the Hamiltonian simulation
      double _epsilon;
      // The number of steps used in the Hamiltonian simulation
      unsigned int _L;
      // The desired value of epsilon*L
      double _epsilonL;
      // The desired value of E[acceptance probability]
      double _delta;

      boost::mt19937 _rand_int;
      boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > _rand_unit_norm;
      boost::uniform_01<boost::mt19937&> _rand_uniform_01;

      // Class implementing Nesterov's primal-dual averaging
      DualAverage _da;
      // Gamma parameter for dual averaging.
      inline static double da_gamma() { return 0.05; }

    public:

      /**
       * Set the step size epsilon. Automatically sets the number of
       * steps L to make epsilon*L as close as possible to the target
       * epsilonL.
       *
       * @param epsilon The new step size epsilon.
       */
      void set_epsilon(double epsilon) {
        _epsilon = epsilon;
        _L = lround(_epsilonL / epsilon);
      }

      /**
       * Constructs an adaptive "constant distance" Hamiltonian Monte Carlo
       * (CDHMC) sampler for the specified model, using the specified 
       * trajectory length, epsilonL, with the specified random seed for
       * randomization.
       *
       * If the same seed is used twice, the series of samples should
       * be the same.  This property is most helpful for testing.  If no
       * random seed is specified, the <code>std::time(0)</code> function is
       * called from the <code>ctime</code> library.
       * 
       * @param model Probability model with gradients.
       * @param epsilonL Specified trajectory length, epsilon*L.
       * @param delta Target value of E[acceptance probability]. 
       * Optional; defaults to the value of 0.651, which has some 
       * theoretical justification.
       * @param epsilon Hamiltonian dynamics simulation step size. Optional;
       * if not specified or set < 0, find_reasonable_parameters() will be 
       * called to initialize epsilon.
       * @param random_seed Seed for random number generator. Optional; 
       * if not specified, generate new seen based on system time.
       */
      adaptive_cdhmc(stan::model::prob_grad& model,
                     double epsilonL, 
                     double delta = 0.651, 
                     double epsilon = -1, 
                     unsigned int random_seed = static_cast<unsigned int>(std::time(0)))
        : adaptive_sampler(epsilon < 0.0),
          _model(model),
          _x(model.num_params_r()),
          _z(model.num_params_i()),
          _g(model.num_params_r()),

          _epsilonL(epsilonL),
          _delta(delta),

          _rand_int(random_seed),
          _rand_unit_norm(_rand_int,
                          boost::normal_distribution<>()),
          _rand_uniform_01(_rand_int),

          _da(da_gamma(), std::vector<double>(1, 0)) {
        set_epsilon(_epsilon);
        model.init(_x,_z);
        _logp = model.grad_log_prob(_x,_z,_g);
        if (_epsilon <= 0)
          find_reasonable_parameters();
        _da.setx0(std::vector<double>(1, log(_epsilon)));
      }

      /**
       * Destructor. The implementation for this class is a no-op.
       */
      virtual ~adaptive_cdhmc() {
      }

      /**
       * Sets the model's real and integer parameters to the specified
       * values.  
       *
       * This method will typically be used to set the parameters
       * by the client of this class after initialization.  
       *
       * @param x Real parameters.
       * @param z Integer parameters.
       */
      virtual void set_params(const std::vector<double>& x,
                              const std::vector<int>& z) {
        assert(x.size() == _x.size());
        assert(z.size() == _z.size());
        _x = x;
        _z = z;
        _logp = _model.grad_log_prob(_x,_z,_g);
      }

      /**
       * Sets the model's real parameters to the specified values
       * and update gradients and log probability to match.
       *
       * This method will typically be used to set the parameters
       * by the client of this class after initialization.  
       *
       * @param x Real parameters.
       * @throw std::invalid_argument if the number of real parameters does
       *   not match the number of parameters defined by the model.
       */
      void set_params_r(const std::vector<double>& x) {
        if (x.size() != _model.num_params_r())
          throw std::invalid_argument("x.size() must match the number of parameters of the model.");
        _x = x;
        _logp = _model.grad_log_prob(_x,_z,_g);
      }

      /**
       * Sets the model integer parameters to the specified values
       * and update gradients and log probability to match.
       *
       * This method will typically be used to set the parameters
       * by the client of this class after initialization.  
       *
       * @param z Integer parameters.
       * @throw std::invalid_argument if the number of integer parameters does
       *   not match the number of parameters defined by the model.
       */
      void set_params_i(const std::vector<int>& z) {
        if (z.size() != _model.num_params_i())
          throw std::invalid_argument ("z.size() must match the number of parameters of the model.");
        _z = z;
        _logp = _model.grad_log_prob(_x,_z,_g);
      }

      /**
       * Searches for a roughly reasonable (within a factor of 2)
       * setting of the step size epsilon.
       */
      virtual void find_reasonable_parameters() {
        _epsilon = 1;
        std::vector<double> x = _x;
        std::vector<double> m(_model.num_params_r());
        for (size_t i = 0; i < m.size(); ++i)
          m[i] = _rand_unit_norm();
        std::vector<double> g = _g;
        double lastlogp = _logp;
        double logp = leapfrog(_model, _z, x, m, g, _epsilon);
        double H = logp - lastlogp;
        int direction = H > log(0.5) ? 1 : -1;
        // fprintf(stderr, "epsilon = %f.  initial logp = %f, lf logp = %f\n", 
        //   _epsilon, lastlogp, logp);
        while (1) {
          x = _x;
          g = _g;
          for (size_t i = 0; i < m.size(); ++i)
            m[i] = _rand_unit_norm();
          logp = leapfrog(_model, _z, x, m, g, _epsilon);
          H = logp - lastlogp;
//           fprintf(stderr, "epsilon = %f.  initial logp = %f, lf logp = %f\n", 
//                   _epsilon, lastlogp, logp);
          if ((direction == 1) && (H < log(0.5)))
            break;
          else if ((direction == -1) && (H > log(0.5)))
            break;
          else
            _epsilon = direction == 1 ? 2 * _epsilon : 0.5 * _epsilon;
        }
        set_epsilon(_epsilon);
      }

      /**
       * Returns the next sample.
       *
       * @return The next sample.
       */
      virtual sample next_impl() {
        // Gibbs for discrete
        std::vector<double> probs;
        for (size_t m = 0; m < _model.num_params_i(); ++m) {
          probs.resize(0);
          for (int k = _model.param_range_i_lower(m); 
               k < _model.param_range_i_upper(m); 
               ++k)
            probs.push_back(_model.log_prob_star(m,k,_x,_z));
          _z[m] = sample_unnorm_log(probs,_rand_uniform_01);
        }

        // HMC for continuous
        std::vector<double> m(_model.num_params_r());
        for (size_t i = 0; i < m.size(); ++i)
          m[i] = _rand_unit_norm();
        double H = -(stan::math::dot_self(m) / 2.0) + _logp; 
        
        std::vector<double> g_new(_g);
        std::vector<double> x_new(_x);
        double logp_new = -1e100;
        for (unsigned int l = 0; l < _L; ++l)
          logp_new = leapfrog(_model, _z, x_new, m, g_new, _epsilon);
        nfevals_plus_eq(_L);

        double H_new = -(stan::math::dot_self(m) / 2.0) + logp_new;
        double dH = H_new - H;
        if (_rand_uniform_01() < exp(dH)) {
          _x = x_new;
          _g = g_new;
          _logp = logp_new;
        }

        // Now we just have to update epsilon, if adaptation is on.
        double adapt_stat = stan::math::min(1, exp(dH));
        if (adapt_stat != adapt_stat)
          adapt_stat = 0;
        if (adapting()) {
          double adapt_g = adapt_stat - _delta;
          std::vector<double> gvec(1, -adapt_g);
          std::vector<double> result;
          _da.update(gvec, result);
          set_epsilon(exp(result[0]));
        }
        std::vector<double> result;
        _da.xbar(result);
//         fprintf(stderr, "xbar = %f\n", exp(result[0]));
        double avg_eta = 1.0 / n_steps();
        update_mean_stat(avg_eta,adapt_stat);

        mcmc::sample s(_x, _z, _logp);
        return s;
      }

      /**
       * Turn off parameter adaptation. Because we're using
       * primal-dual averaging, once we're done adapting we want to
       * set epsilon=the _average_ value of epsilon over each
       * adaptation step. This results in a lower-variance estimate of
       * the optimal epsilon.
       */
      virtual void adapt_off() {
        adaptive_sampler::adapt_off(); 
        std::vector<double> result;
        _da.xbar(result);
        set_epsilon(exp(result[0]));
      }

      /**
       * Returns the value of epsilon.
       *
       * @param[out] params Where to store epsilon.
       */
      virtual void get_parameters(std::vector<double>& params) {
        params.assign(1, _epsilon);
      }

    };

  }

}

#endif
