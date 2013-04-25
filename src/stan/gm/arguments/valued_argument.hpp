#ifndef __STAN__GM__ARGUMENTS__VALUED__ARGUMENT__BETA__
#define __STAN__GM__ARGUMENTS__VALUED__ARGUMENT__BETA__

#include <stan/gm/arguments/argument.hpp>

namespace stan {
  
  namespace gm {
    
    class valued_argument: public argument {
      
    public:
      
      virtual void print(std::ostream* s, int depth) {
        
        if(!s) return;
        
        std::string indent(indent_width * depth, ' ');
        
        *s << indent << _name << " = " << print_value();
        if(is_default())
          *s << " (Default)";
        *s << std::endl;
        
      }
      
      virtual void print_help(std::ostream* s, int depth) {
        
        if(!s) return;
        
        std::string indent(indent_width * depth, ' ');
        std::string subindent(indent_width, ' ');
        
        *s << indent << _name << std::endl;
        *s << indent << subindent << _description << std::endl;
        *s << indent << subindent << "Valid values:" << print_valid() << std::endl;
        *s << indent << subindent << "Defaults to " << _default << std::endl;
        *s << std::endl;
        
      }
      
      virtual std::string print_value() = 0;
      virtual std::string print_valid() = 0;
      virtual bool is_default() = 0;
      
    protected:
      
      std::string _default;

    };
    
  } // gm
  
} // stan

#endif

