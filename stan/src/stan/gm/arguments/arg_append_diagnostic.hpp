#ifndef __STAN__GM__ARGUMENTS__APPEND__DIAGNOSTIC__HPP__
#define __STAN__GM__ARGUMENTS__APPEND__DIAGNOSTIC__HPP__

#include <stan/gm/arguments/singleton_argument.hpp>

namespace stan {
  
  namespace gm {
    
    class arg_append_diagnostic: public bool_argument {
      
    public:
      
      arg_append_diagnostic(): bool_argument() {
        _name = "append_diagnostic";
        _description = "Append diagnostic output to existing file?";
        _validity = "[true, false]";
        _default = "false";
        _default_value = false;
        _value = _default_value;
      };
      
    };
    
  } // gm
  
} // stan

#endif

