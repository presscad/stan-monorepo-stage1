#ifndef STAN_MATH_PRIM_SCAL_META_PARTIALS_RETURN_TYPE_HPP
#define STAN_MATH_PRIM_SCAL_META_PARTIALS_RETURN_TYPE_HPP

#include <stan/math/prim/scal/meta/partials_type.hpp>
#include <stan/math/prim/scal/meta/scalar_type.hpp>
#include <boost/math/tools/promotion.hpp>

namespace stan {

  /**
   * Template metaprogram to calculate the base scalar return type for partial
   * derivatives. The metaprogram can take an arbitrary number of template
   * parameters.
   *
   * All C++ primitive types (except <code>long double</code>) are automatically
   * promoted to <code>double</code>.
   *
   * <code>partials_return_type<...></code> is a class defining a single public
   * typedef <code>type</code> that is <code>double</code> for containers
   * of base C++ types (except for <code>long double</code>) as well as
   * containers of <code>var</code> types.
   *
   * <code>partials_type<fvar<var> >::type</code> is not <code>var</code>.
   *
   * Example usage:
   *  - <code>return_type<int,double,float>::type</code> is <code>double</code>
   *  - <code>return_type<double,var>::type</code> is <code>double</code>
   *
   * @tparam T (required) A type
   * @tparam T_pack (optional) A parameter pack containing further types.
   */

template <typename T, typename... T_pack>
struct partials_return_type {
  typedef typename boost::math::tools::promote_args<double,
      typename partials_type<typename scalar_type<T>::type>::type,
      typename partials_return_type<T_pack...>::type >::type type;
};

template <typename T>
struct partials_return_type<T> {
  typedef typename boost::math::tools::promote_args<double,
      typename partials_type<typename scalar_type<T>::type>::type >::type type;
};

}  // namespace stan
#endif
