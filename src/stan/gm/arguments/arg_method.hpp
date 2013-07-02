#ifndef __STAN__GM__ARGUMENTS__METHOD__HPP__
#define __STAN__GM__ARGUMENTS__METHOD__HPP__

#include <stan/gm/arguments/list_argument.hpp>

#include <stan/gm/arguments/arg_sample.hpp>
#include <stan/gm/arguments/arg_optimize.hpp>

namespace stan {
  
  namespace gm {
    
    class arg_method: public list_argument {
      
    public:
      
      arg_method() {
        
        _name = "method";
        _short_description = "Analysis method";
        _description = "Analysis method";
        
        _values.push_back(new arg_sample());
        _values.push_back(new arg_optimize());
        
        _default_cursor = 0;
        _cursor = _default_cursor;
        
      }
      
    };
    
  } // gm
  
} // stan

#endif

