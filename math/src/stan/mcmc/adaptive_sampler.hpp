#ifndef __STAN__MCMC__ADAPTIVE_SAMPLER_HPP__
#define __STAN__MCMC__ADAPTIVE_SAMPLER_HPP__

#include <stan/mcmc/sampler.hpp>
#include <iostream>

namespace stan {

  namespace mcmc {

    /**
     * An abstract base class for adaptive samplers.
     *
     * The <code>adaptive_sampler</code> abstract base class
     * maintains the adaptation status, number of steps, as well as
     * recording function evals and the mean statistic being
     * optimized.
     */
    class adaptive_sampler {

    protected: 
      bool _adapt;
      unsigned int _n_steps;
      int _n_adapt_steps;
      unsigned int _nfevals;
      double _mean_stat;
      std::ostream* _error_msgs;
      std::ostream* _output_msgs;

    public:

      /**
       * Constructs an adaptive sampler with specified adaptation
       * status.
       *
       * @param adapt Initial adaptation status.
       * @param error_msgs Pointer to output stream for error
       * messages.
       */
      adaptive_sampler(bool adapt,
                       std::ostream* error_msgs = 0,
                       std::ostream* output_msgs = 0)
        : _adapt(adapt), 
          _n_steps(0), 
          _n_adapt_steps(0), 
          _nfevals(0),
          _mean_stat(0),
          _error_msgs(error_msgs),
          _output_msgs(output_msgs) {
      }

      /**
       * Destructor.
       */
      virtual ~adaptive_sampler() { 
      }

      /**
       * Set the stream into which errors will be written
       * as the sampler runs.  
       *
       * @param error_msgs Stream to which error messages are written.
       */
      void set_error_stream(std::ostream& error_msgs) {
        _error_msgs = &error_msgs;
      }

      /**
       * Unset the stream into which errors are written to 0 so
       * that error messages are ignored.
       */
      void unset_error_stream() {
        _error_msgs = 0;
      }


      /**
       * Set the stream into which output will be written
       * as the sampler runs.  
       *
       * @param error_msgs Stream to which output messages are written.
       */
      void set_output_stream(std::ostream& output_msgs) {
        _output_msgs = &output_msgs;
      }

      /**
       * Unset the stream into which errors are written to 0 so
       * that output messages are ignored.
       */
      void unset_output_stream() {
        _output_msgs = 0;
      }


      /**
       * Set the model real and integer parameters to the specified
       * values.
       *
       * This method will typically be used to set the parameters
       * by the client of this class after initialization.  
       *
       * @param x Real parameters.
       * @param z Integer parameters.
       */
      virtual void set_params(const std::vector<double>& x, 
                              const std::vector<int>& z) = 0;

      /**
       * Returns the next sample from this sampler.  This
       * method increments the count of steps with and without
       * adaptation and calls the virtual <code>next_impl()</code> 
       * to produce a result.
       *
       * @return Next sample.
       */
      sample next() {
        ++_n_steps;
        if (adapting())
          ++_n_adapt_steps;
        return next_impl();
      }

      /**
       * Returns the next sample from this sampler.  This pure virtual method
       * must be implemented by concrete subclasses to produce the next
       * sample.
       *
       * @return Next sample.
       */
      virtual sample next_impl() = 0;

      /**
       * Find a reasonable initial setting for the adaptable
       * parameters.  May not be applicable/implemented for all
       * samplers.
       *
       * The default implementation is a no-op.
       */
      virtual void find_reasonable_parameters() {
      };

      /**
       * Sets the specified parameter vector to the sequence of tunable
       * parameters for this sampler.
       *
       * The default implementation sets the specified vector to empty.
       *
       * @param[out] params Where to store the returned parameters.
       */
      virtual void get_parameters(std::vector<double>& params) { 
        params.resize(0);
      }

      /**
       * Returns the value of the statistic we are trying to
       * coerce.  For example, if we are trying to set the average
       * acceptance probability of HMC to 0.651 then this method will
       * return the realized acceptance probability averaged across all
       * samples so far.
       *
       * @return Mean observed target statistic for adaptation.
       */
      inline double mean_stat() { 
        return _mean_stat; 
      }
      
      /**
       * Sets the mean statistic to the specified value.
       *
       * @param v New value of mean statistic.
       */
      inline void set_mean_stat(double v) {
        _mean_stat = v;
      }

      /**
       * Updates the mean statistic given the specified adaptation statistic
       * and weighting.  The behavior is equivalent to doing
       *
       * <code>mean_stat += avg_eta * adapt_stat + (1 - avg_eta) * mean_stat</code>.
       *
       * @param avg_eta Weight of adaptation statistic.
       * @param adapt_stat Adaptation statistic.
       */
      inline void update_mean_stat(double avg_eta, 
                                   double adapt_stat) {
        _mean_stat = avg_eta * adapt_stat + (1 - avg_eta) * _mean_stat;
      }

      /**
       * Returns the number of times that the (possibly unnormalized)
       * log probability function has been evaluated by this sampler.
       * This is a useful alternative to wall time in evaluating the
       * relative performance of different algorithms. However, it is
       * up to the sampler implementation to be sure to actually keep
       * track of this.
       *
       * @return Number of log probability function evaluations.
       */
      inline unsigned int nfevals() { 
        return _nfevals; 
      }

      /**
       * Add the specified number of evaluations to the
       * number of function evaluations.
       *
       * @param n Number of evaluations to add.
       */
      inline void nfevals_plus_eq(int n) {
        _nfevals += n;
      }

      /**
       * Return the number of iterations for this sampler.
       *
       * @return Number of iterations.
       */
      inline int n_steps() {
        return _n_steps;
      }

      /**
       * Return how many iterations parameter adaptation has happened for.
       *
       * @return How many iterations parameter adaptation has happened for.
       */
      inline int n_adapt_steps() { 
        return _n_adapt_steps; 
      }

      /**
       * Turn on parameter adaptation.
       */
      virtual void adapt_on() { 
        _adapt = true; 
      }

      /**
       * Turn off parameter adaption.
       */
      virtual void adapt_off() { 
        _adapt = false; 
      }

      /**
       * Return whether or not parameter adaptation is on.
       *
       * @return Whether or not parameter adaptation is on.
       */
      inline bool adapting() { 
        return _adapt;
      }

      /**
       * Write out any sampler-specific parameters for output.
       *
       * This method must
       * match <code>write_sampler_param_names()</code> in
       * terms of number of parameters written.
       *
       * Params should be writte starting with a comma, then
       * the first parameter, then a comma, then the second
       * parameter, ending on the final parameter.
       *
       * The base class implementation is a no-op.
       *
       * @param[out] o Output stream to which params are written.
       */
      virtual void write_sampler_params(std::ostream& o) { 
      }

      /**
       * Use this method to write the adaptation parameters into
       * the output.  
       *
       * These should be written as one or more comment lines,
       * each starting with a pound (<code>#</code>) character.
       *
       * @param o Output stream to which adaptation information is written.
       */
      virtual void write_adaptation_params(std::ostream& o) {
      }

      /**
       * Write out any sampler-specific parameter names for output.
       *
       * This method must match
       * <code>write_sampler_params()</code> in terms of
       * number of parameters written.
       *
       * Params should be writte starting with a comma, then the first
       * parameter, then a comma, then the second parameter, ending on
       * the final parameter.
       *
       * The base class implementation is a no-op.
       *
       * @param[out] o Output stream to which param names are written.
       */
      virtual void write_sampler_param_names(std::ostream& o) {
      }

      /**
       * Get any sampler-specific parameter namess.
       *
       * @param[out] names Output vector to which param names are written.
       */

      virtual void get_sampler_param_names(std::vector<std::string>& names) {
      }
                                
      /**
       * Get any sampler-specific parameters.
       *
       * @param[out] values Output vector to which params are written.
       *  All values are casted to type double.
       *  This function should match get_sampler_param_names.
       *
       */
      virtual void get_sampler_params(std::vector<double>& values) {
      }

    };

  }

}

#endif
