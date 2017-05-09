#ifndef STAN_MATH_REV_SCAL_META_OPERANDS_AND_PARTIALS_HPP
#define STAN_MATH_REV_SCAL_META_OPERANDS_AND_PARTIALS_HPP

#include <stan/math/rev/core/chainablestack.hpp>
#include <stan/math/rev/core/precomputed_gradients.hpp>
#include <stan/math/rev/core/var.hpp>
#include <stan/math/rev/core/vari.hpp>
#include <stan/math/prim/scal/meta/operands_and_partials.hpp>
#include <stan/math/prim/scal/meta/is_vector_like.hpp>

namespace stan {
  namespace math {
    namespace detail {
      template <>
      class ops_partials_edge<double, var>
        : public ops_partials_edge_single<double, var> {
      public:
        explicit ops_partials_edge(const var& op)
          : ops_partials_edge_single<double, var>(op) {}
        void dump_partials(double* partials) {
          *partials = this->partials_[0];
        }
        void dump_operands(vari** varis) {
          *varis = this->operand_.vi_;
        }
      };
    }  // end namespace detail

    /**
     * This class builds partial derivatives with respect to a set of
     * operands. There are two reason for the generality of this
     * class. The first is to handle vector and scalar arguments
     * without needing to write additional code. The second is to use
     * this class for writing probability distributions that handle
     * primitives, reverse mode, and forward mode variables
     * seamlessly.
     *
     * This class now supports multivariate use-cases as well by
     * exposing edge#_.partials_vec
     *
     * This is the specialization for when the return type is var,
     * which should be for all of the reverse mode cases.
     *
     * @tparam Op1 type of the first operand
     * @tparam Op2 type of the second operand
     * @tparam Op3 type of the third operand
     * @tparam Op4 type of the fourth operand
     * @tparam T_return_type return type of the expression. This defaults
     *   to a template metaprogram that calculates the scalar promotion of
     *   Op1 -- Op4
     */
    template <typename Op1, typename Op2, typename Op3, typename Op4>
    class operands_and_partials<Op1, Op2, Op3, Op4, var> {
    public:
      detail::ops_partials_edge<double, Op1> edge1_;
      detail::ops_partials_edge<double, Op2> edge2_;
      detail::ops_partials_edge<double, Op3> edge3_;
      detail::ops_partials_edge<double, Op4> edge4_;

      explicit operands_and_partials(const Op1& o1)
        : edge1_(o1) { }
      operands_and_partials(const Op1& o1, const Op2& o2)
        : edge1_(o1), edge2_(o2) { }
      operands_and_partials(const Op1& o1, const Op2& o2, const Op3& o3)
        : edge1_(o1), edge2_(o2), edge3_(o3) { }
      operands_and_partials(const Op1& o1, const Op2& o2, const Op3& o3,
                            const Op4& o4)
        : edge1_(o1), edge2_(o2), edge3_(o3), edge4_(o4) { }

      // this is what matters in terms of going on autodiff stack
      var build(double value) {
        size_t size = edge1_.size() + edge2_.size() + edge3_.size()
          + edge4_.size();
        vari** varis = ChainableStack::memalloc_.alloc_array<vari*>(size);
        double* partials = ChainableStack::memalloc_.alloc_array<double>(size);
        int idx = 0;
        edge1_.dump_operands(&varis[idx]);
        edge1_.dump_partials(&partials[idx]);
        edge2_.dump_operands(&varis[idx += edge1_.size()]);
        edge2_.dump_partials(&partials[idx]);
        edge3_.dump_operands(&varis[idx += edge2_.size()]);
        edge3_.dump_partials(&partials[idx]);
        edge4_.dump_operands(&varis[idx += edge3_.size()]);
        edge4_.dump_partials(&partials[idx]);

        return var(new
                   precomputed_gradients_vari(value, size, varis, partials));
      }
    };
  }
}
#endif
