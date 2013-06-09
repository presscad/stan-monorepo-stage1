#ifndef __STAN__GM__ARGUMENTS__NUM__WARMUP__HPP__
#define __STAN__GM__ARGUMENTS__NUM__WARMUP__HPP__

#include <stan/gm/arguments/singleton_argument.hpp>

namespace stan {
  
  namespace gm {
    
    class arg_num_warmup: public int_argument {
      
    public:
      
      arg_num_warmup(): int_argument() {
        _name = "num_warmup";
        _description = "Number of sampling iterations reserved for warmup";
        _validity = "0 < warmup";
        _default = "1000";
        _default_value = 1000;
        _value = _default_value;
      };
      
      bool is_valid(int value) { return value > 0; }
      
    };
    
  } // gm
  
} // stan

#endif

