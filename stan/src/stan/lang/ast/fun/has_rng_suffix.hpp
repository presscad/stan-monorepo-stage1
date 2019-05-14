#ifndef STAN_LANG_AST_FUN_HAS_RNG_SUFFIX_HPP
#define STAN_LANG_AST_FUN_HAS_RNG_SUFFIX_HPP

#include <string>

namespace stan {
  namespace lang {

    /**
     * Return true if the specified string has the suffix
     * "_rng".
     *
     * @param[in] name function name
     */
    bool has_rng_suffix(const std::string& name);

  }
}
#endif
