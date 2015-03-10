#ifndef STAN__SERVICES__ARGUMENTS__SAVE__VARIATIONAL__HPP
#define STAN__SERVICES__ARGUMENTS__SAVE__VARIATIONAL__HPP

#include <stan/services/arguments/singleton_argument.hpp>

namespace stan {

  namespace services {

    class arg_save_variational: public bool_argument {

    public:

      arg_save_variational(): bool_argument() {
        _name = "save_variational";
        _description = "Stream variational inference progress to output?";
        _validity = "[0, 1]";
        _default = "0";
        _default_value = false;
        _constrained = false;
        _good_value = 1;
        _value = _default_value;
      };

    };

  } // services

} // stan

#endif
