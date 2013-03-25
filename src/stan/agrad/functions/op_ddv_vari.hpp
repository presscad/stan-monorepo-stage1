#ifndef __STAN__AGRAD__FUNCTIONS__OP_DDV_VARI_HPP__
#define __STAN__AGRAD__FUNCTIONS__OP_DDV_VARI_HPP__

#include <stan/agrad/vari.hpp>

namespace stan {
  namespace agrad {

    class op_ddv_vari : public vari {
    protected:
      double ad_;
      double bd_;
      vari* cvi_;
    public:
      op_ddv_vari(double f, double a, double b, vari* cvi) :
        vari(f),
        ad_(a),
        bd_(b),
        cvi_(cvi) {
      }
    };

  }
}
#endif
