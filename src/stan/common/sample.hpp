#ifndef STAN__COMMON__SAMPLE_HPP
#define STAN__COMMON__SAMPLE_HPP

#include <stan/mcmc/base_mcmc.hpp>
#include <stan/io/mcmc_writer.hpp>
#include <stan/common/run_markov_chain.hpp>
#include <string>

namespace stan {
  namespace common {
    template <class Model, class RNG, class StartTransitionCallback,
              class SampleRecorder, class DiagnosticRecorder,
              class MessageRecorder>
    void sample(stan::mcmc::base_mcmc* sampler,
                int num_warmup,
                int num_samples,
                int num_thin,
                int refresh,
                bool save,
                stan::io::mcmc_writer
                <Model, SampleRecorder, DiagnosticRecorder,
                MessageRecorder>& writer,
                stan::mcmc::sample& init_s,
                Model& model,
                RNG& base_rng,
                const std::string& prefix,
                const std::string& suffix,
                std::ostream& o,
                StartTransitionCallback& callback) {
      run_markov_chain<Model, RNG, StartTransitionCallback,
                       SampleRecorder, DiagnosticRecorder, MessageRecorder>
        (sampler, num_samples, num_warmup,
         num_warmup + num_samples, num_thin,
         refresh, save, false,
         writer,
         init_s, model, base_rng,
         prefix, suffix, o,
         callback);
    }
  }
}

#endif
