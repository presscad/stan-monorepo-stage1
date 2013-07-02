#ifndef __STAN__GM__ARGUMENTS__ID__HPP__
#define __STAN__GM__ARGUMENTS__ID__HPP__

#include <stan/gm/arguments/singleton_argument.hpp>

namespace stan {
  
  namespace gm {
    
    class arg_id: public int_argument {
      
    public:
      
      arg_id(): int_argument() {
        _name = "id";
        _short_description = "Chain id";
        _description = "Unique process identifier";
        _validity = "id > 0";
        _default = "0";
        _default_value = 0;
        _value = _default_value;
      };
      
      bool is_valid(int value) { return value > 0; }
      
    };
    
  } // gm
  
} // stan

#endif

