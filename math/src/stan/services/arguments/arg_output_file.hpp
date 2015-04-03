#ifndef STAN_SERVICES_ARGUMENTS_ARG_OUTPUT_FILE_HPP
#define STAN_SERVICES_ARGUMENTS_ARG_OUTPUT_FILE_HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {
  
  namespace services {
    
    class arg_output_file: public string_argument {
      
    public:
      
      arg_output_file(): string_argument() {
        _name = "file";
        _description = "Output file";
        _validity = "Path to existing file";
        _default = "output.csv";
        _default_value = "output.csv";
        _constrained = false;
        _good_value = "good";
        _value = _default_value;
      };
      
    };
    
  } // services
  
} // stan

#endif
