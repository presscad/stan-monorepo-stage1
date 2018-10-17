#ifndef STAN_LANG_AST_DOUBLE_BLOCK_TYPE_HPP
#define STAN_LANG_AST_DOUBLE_BLOCK_TYPE_HPP

#include <stan/lang/ast/node/range.hpp>
#include <stan/lang/ast/node/locscale.hpp>

namespace stan {
namespace lang {

/**
 * Double block var type.
 */
struct double_block_type {
  /**
   * Bounds constraints
   */
  range bounds_;

  /**
   * Location and scale
   */
  locscale ls_;

  /**
   * Construct a block var type with default values.
   */
  double_block_type();

  /**
   * Construct a block var type with specified values.
   *
   * @param bounds variable upper and/or lower bounds
   * @param ls variable location and scale
   */
  explicit double_block_type(const range& bounds, const locscale& ls);

  /**
   * Construct a block var type with specified values.
   *
   * @param bounds variable upper and/or lower bounds
   */
  explicit double_block_type(const range& bounds);

  /**
   * Get bounds constraints.
   */
  range bounds() const;

  /**
   * Get location and scale.
   */
  locscale ls() const;
};

}  // namespace lang
}  // namespace stan
#endif
