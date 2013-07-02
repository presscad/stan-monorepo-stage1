#ifndef __STAN__GM__ARGUMENTS__ARGUMENT__BETA__
#define __STAN__GM__ARGUMENTS__ARGUMENT__BETA__

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

namespace stan {
  namespace gm {
    
    class argument {
    public:
      
      argument()
        : indent_width(2),
          help_width(20) { }
      
      argument(const std::string name) 
        : _name(name),
          indent_width(2),
          help_width(20) { }

      virtual ~argument() { }

      std::string name() const { 
        return _name; 
      }
      std::string short_description() const {
        return _short_description;
      }
      
      std::string description() const { 
        return _description; 
      }

      virtual void print(std::ostream* s, const int depth, const char prefix) = 0;
      virtual void print_help(std::ostream* s, const int depth, const bool recurse) = 0;
      
      virtual bool parse_args(std::vector<std::string>& args,
                              std::ostream* out,
                              std::ostream* err,
                              bool& help_flag) { 
        return true; 
      }
      
      static void split_arg(const std::string& arg, std::string& name, std::string& value) {
        size_t pos = arg.find('=');
        
        if (pos != std::string::npos) {
          name = arg.substr(0, pos);
          value = arg.substr(pos + 1, arg.size() - pos);
        }
      }
      
      virtual argument* arg(const std::string name) { 
        return 0; 
      }
      
      int compute_indent(const int depth) { 
        return indent_width * depth + 1; 
      }
      
    protected:
      std::string _name;
      std::string _short_description;
      std::string _description;
    
      int indent_width;
      int help_width;
    };

  } // gm
} // stan
#endif

