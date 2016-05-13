#ifndef STAN_MATH_REV_ARR_FUNCTOR_INTEGRATE_ODE_BDF_HPP
#define STAN_MATH_REV_ARR_FUNCTOR_INTEGRATE_ODE_BDF_HPP

#include <stan/math/prim/arr/err/check_nonzero_size.hpp>
#include <stan/math/prim/arr/err/check_ordered.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/err/check_less.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/invalid_argument.hpp>
#include <stan/math/prim/scal/meta/return_type.hpp>
#include <stan/math/rev/arr/functor/coupled_ode_system_cvode.hpp>
#include <ostream>
#include <vector>

namespace stan {
  namespace math {
    /**
     * Return the solutions for the specified system of ordinary
     * differential equations given the specified initial state,
     * initial times, times of desired solution, and parameters and
     * data, writing error and warning messages to the specified
     * stream.
     *
     * <b>Warning:</b> If the system of equations is stiff, roughly
     * defined by having varying time scales across dimensions, then
     * this solver is likely to be slow.
     *
     * This function is templated to allow the initial times to be
     * either data or autodiff variables and the parameters to be data
     * or autodiff variables.  The autodiff-based implementation for
     * reverse-mode are defined in namespace <code>stan::math</code>
     * and may be invoked via argument-dependent lookup by including
     * their headers.
     *
     * @tparam F type of ODE system function.
     * @tparam T1 type of scalars for initial values.
     * @tparam T2 type of scalars for parameters.
     * @param[in] f functor for the base ordinary differential equation.
     * @param[in] y0 initial state.
     * @param[in] t0 initial time.
     * @param[in] ts times of the desired solutions, in strictly
     * increasing order, all greater than the initial time.
     * @param[in] theta parameter vector for the ODE.
     * @param[in] x continuous data vector for the ODE.
     * @param[in] x_int integer data vector for the ODE.
     * @param[in, out] msgs the print stream for warning messages.
     * @param[in] relative_tolerance relative tolerance passed to CVODE.
     * @param[in] absolute_tolerance absolute tolerance passed to CVODE.
     * @param[in] max_num_steps maximum number of steps to pass to CVODE.
     * @return a vector of states, each state being a vector of the
     * same size as the state variable, corresponding to a time in ts.
     */
    template <typename F, typename T1, typename T2>
    std::vector<std::vector<typename stan::return_type<T1, T2>::type> >
    integrate_ode_bdf(const F& f,
                      const std::vector<T1> y0,
                      const double t0,
                      const std::vector<double>& ts,
                      const std::vector<T2>& theta,
                      const std::vector<double>& x,
                      const std::vector<int>& x_int,
                      std::ostream* msgs = 0,
                      double relative_tolerance = 1e-10,
                      double absolute_tolerance = 1e-10,
                      long int max_num_steps = 1e8) {  // NOLINT(runtime/int)
      stan::math::check_finite("integrate_ode_bdf",
                               "initial state", y0);
      stan::math::check_finite("integrate_ode_bdf",
                               "initial time", t0);
      stan::math::check_finite("integrate_ode_bdf",
                               "times", ts);
      stan::math::check_finite("integrate_ode_bdf",
                               "parameter vector", theta);
      stan::math::check_finite("integrate_ode_bdf",
                               "continuous data", x);

      stan::math::check_nonzero_size("integrate_ode_bdf",
                                     "times", ts);
      stan::math::check_nonzero_size("integrate_ode_bdf",
                                     "initial state", y0);
      stan::math::check_ordered("integrate_ode_bdf",
                                "times", ts);
      stan::math::check_less("integrate_ode_bdf",
                             "initial time", t0, ts[0]);

      if (relative_tolerance <= 0)
        invalid_argument("integrate_ode_bdf",
                         "relative_tolerance,", relative_tolerance,
                         "", ", must be greater than 0");
      if (absolute_tolerance <= 0)
        invalid_argument("integrate_ode_bdf",
                         "absolute_tolerance,", absolute_tolerance,
                         "", ", must be greater than 0");
      if (max_num_steps <= 0)
        invalid_argument("integrate_ode_bdf",
                         "max_num_steps,", max_num_steps,
                         "", ", must be greater than 0");
      
      coupled_ode_system_cvode<F, T1, T2>
        coupled_system(f, y0, t0, theta, x, x_int,
                       relative_tolerance, absolute_tolerance, max_num_steps,
                       msgs);

      std::vector<std::vector<double> > y_coupled(ts.size());
      for (size_t n = 0; n < ts.size(); ++n)
        y_coupled[n].resize(coupled_system.size());

      coupled_system.integrate_times(ts, y_coupled);

      return coupled_system.decouple_states(y_coupled);
    }
  }  // math
}  // stan
#endif
