#ifndef STAN__MODEL__STANC_MODEL_HPP__
#define STAN__MODEL__STANC_MODEL_HPP__

#include <stan/model/prob_grad_ad.hpp>

namespace stan {

  namespace stanc_model {

    /**
     * The abstract base class for models generated by the Stan
     * compiler <code>stanc</code>.
     */
    class stanc_model : public prob_grad_ad {
      
      /**
       * Construct a model with the specified number of continuous
       * parameters.
       *
       * @param num_params Number of continuous parameters.
       */
      stanc_model(size_t num_params) 
        : prob_grad_ad(num_params) {
        }

    };

  }
}

#endif
