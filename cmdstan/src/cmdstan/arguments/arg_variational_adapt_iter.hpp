#ifndef CMDSTAN_ARGUMENTS_ARG_VARIATIONAL_ADAPT_ITER_HPP
#define CMDSTAN_ARGUMENTS_ARG_VARIATIONAL_ADAPT_ITER_HPP

#include <cmdstan/arguments/singleton_argument.hpp>

namespace cmdstan {

  class arg_variational_adapt_iter: public int_argument {
  public:
    arg_variational_adapt_iter(): int_argument() {
      _name = "iter";
      _description = "Number of iterations for eta adaptation";
      _validity = "0 < iter";
      _default = "50";
      _default_value = 50;
      _constrained = true;
      _good_value = 50.0;
      _bad_value = -1.0;
      _value = _default_value;
    }

    bool is_valid(int value) {
      return value > 0;
    }
  };

}
#endif
