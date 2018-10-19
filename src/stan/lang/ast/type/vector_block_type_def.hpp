#ifndef STAN_LANG_AST_VECTOR_BLOCK_TYPE_DEF_HPP
#define STAN_LANG_AST_VECTOR_BLOCK_TYPE_DEF_HPP

#include <stan/lang/ast.hpp>

namespace stan {
namespace lang {
vector_block_type::vector_block_type(const range& bounds, const locscale& ls,
                                     const expression& N)
    : bounds_(bounds), ls_(ls), N_(N) {
    if (bounds.has_low() || bounds.has_high())
      if (ls.has_loc() || ls.has_scale())
        throw std::invalid_argument("Block type cannot have both a bound and\
          a location/scale.");
  }

vector_block_type::vector_block_type(const range& bounds, const expression& N)
    : bounds_(bounds), ls_(locscale()), N_(N) {}

vector_block_type::vector_block_type(const locscale& ls, const expression& N)
    : bounds_(range()), ls_(ls), N_(N) {}

vector_block_type::vector_block_type() : vector_block_type(range(), nil()) {}

range vector_block_type::bounds() const { return bounds_; }

locscale vector_block_type::ls() const { return ls_; }

expression vector_block_type::N() const { return N_; }
}  // namespace lang
}  // namespace stan
#endif
