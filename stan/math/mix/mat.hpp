#ifndef STAN_MATH_MIX_MAT_HPP
#define STAN_MATH_MIX_MAT_HPP

#include <stan/math/mix/mat/fun/typedefs.hpp>

#include <stan/math/mix/mat/functor/derivative.hpp>
#include <stan/math/mix/mat/functor/finite_diff_grad_hessian.hpp>
#include <stan/math/mix/mat/functor/grad_hessian.hpp>
#include <stan/math/mix/mat/functor/grad_tr_mat_times_hessian.hpp>
#include <stan/math/mix/mat/functor/gradient_dot_vector.hpp>
#include <stan/math/mix/mat/functor/hessian.hpp>
#include <stan/math/mix/mat/functor/hessian_times_vector.hpp>
#include <stan/math/mix/mat/functor/partial_derivative.hpp>

#include <stan/math/rev/mat.hpp>

#include <stan/math/fwd/mat.hpp>

#include <stan/math/prim/mat.hpp>

// FIXME(carpenter): sort out ordering to include in rev, etc.
// currently have to come after scalar (fwd, rev) defs
// probably due to overincludes in some of the headers
#include <stan/math/prim/mat/fun/acosh.hpp>
#include <stan/math/prim/mat/fun/asinh.hpp>
#include <stan/math/prim/mat/fun/atanh.hpp>
#include <stan/math/prim/mat/fun/exp2.hpp>
#include <stan/math/prim/mat/fun/log1m_inv_logit.hpp>
#include <stan/math/prim/mat/fun/log2.hpp>
#include <stan/math/prim/mat/fun/log_inv_logit.hpp>
#include <stan/math/prim/mat/fun/logit.hpp>
#include <stan/math/prim/mat/fun/Phi_approx.hpp>
#include <stan/math/prim/mat/fun/trigamma.hpp>
#include <stan/math/prim/mat/fun/trunc.hpp>

#endif
