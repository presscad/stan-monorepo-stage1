#ifndef __STAN__AGRAD__FUNCTIONS__OP_V_VARI_HPP__
#define __STAN__AGRAD__FUNCTIONS__OP_V_VARI_HPP__

#include <stan/agrad/vari.hpp>

namespace stan {
  namespace agrad {
    
    class op_v_vari : public vari {
    protected:
      vari* avi_;
    public:
      op_v_vari(double f, vari* avi) :
        vari(f),
        avi_(avi) {
      }
    };

  }
}
#endif
