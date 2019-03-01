#ifndef STAN_MATH_PRIM_SCAL_META_IS_VAR_OR_ARITHMETIC_HPP
#define STAN_MATH_PRIM_SCAL_META_IS_VAR_OR_ARITHMETIC_HPP

#include <stan/math/prim/scal/meta/is_var.hpp>
#include <stan/math/prim/scal/meta/scalar_type.hpp>
#include <stan/math/prim/arr/meta/and.hpp>
#include <type_traits>

namespace stan {

template <typename T>
struct is_var_or_arithmetic_ {
  enum { value = (is_var<typename scalar_type<T>::type>::value || std::is_arithmetic<typename scalar_type<T>::type>::value) };
};

template<typename... T>
  using is_var_or_arithmetic =  and_<is_var_or_arithmetic_<T>...>;

}  // namespace stan
#endif
