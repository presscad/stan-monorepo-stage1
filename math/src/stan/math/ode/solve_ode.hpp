#ifndef STAN__MATH__ODE__SOLVE_ODE_HPP__
#define STAN__MATH__ODE__SOLVE_ODE_HPP__

#include <vector>
#include <boost/numeric/odeint.hpp>
#include <stan/math/ode/util.hpp>
#include <stan/agrad/rev/var.hpp>
#include <stan/meta/traits.hpp>
#include <stan/agrad/rev/internal/precomputed_gradients.hpp>

namespace stan {
  
  namespace math {

    template <typename F>
    struct ode_system {
      const F& f_;
      const std::vector<double>& theta_;
      const std::vector<double>& x_;
      const std::vector<int>& x_int_;
      ode_system(const F& f,
                 const std::vector<double>& theta,
                 const std::vector<double>& x,
                 const std::vector<int>& x_int)
        : f_(f), theta_(theta), x_(x), x_int_(x_int) {
      }
      void operator()(const std::vector<double>& y,
                      std::vector<double>& dy_dt,
                      const double& t) {

        dy_dt = f_(t,y,theta_,x_,x_int_);

        size_t num_eqn = dy_dt.size();

        std::vector<double> coupled_sys;

        std::vector<stan::agrad::var> theta_temp;
        std::vector<stan::agrad::var> y_temp;
        std::vector<stan::agrad::var> dy_dt_temp;
        std::vector<double> grad;
        std::vector<stan::agrad::var> vars;

        for (int i = 0; i < num_eqn; i++) {
          theta_temp.clear();
          y_temp.clear();
          dy_dt_temp.clear();
          grad.clear();
          vars.clear();

          for (int j = 0; j < num_eqn; j++) {
            y_temp.push_back(y[j]);
            vars.push_back(y_temp[j]);
          }

          for (int j = 0; j < theta_.size(); j++) {
            theta_temp.push_back(theta_[j]);
            vars.push_back(theta_temp[j]);
          }

          dy_dt_temp = f_(stan::agrad::var(t),y_temp,theta_temp,x_,x_int_);
          dy_dt_temp[i].grad(vars, grad);

          for (int j = 0; j < theta_.size(); j++) { 
            // orders derivatives by equation (i.e. if there are 2 eqns 
            // (y1, y2) and 2 parameters (a, b), dy_dt will be ordered as: 
            // dy1_dt, dy2_dt, dy1_da, dy1_db, dy2_da, dy2_db
            double temp_deriv = grad[y_temp.size()+j];
            for (int k = 0; k < num_eqn; k++)
              temp_deriv += y[num_eqn+theta_.size()*k+j] * grad[k];

            coupled_sys.push_back(temp_deriv);
          }
        }

        dy_dt.insert(dy_dt.end(), coupled_sys.begin(), coupled_sys.end());
      }
    };

    std::vector<std::vector<double> > 
    compute_results(const std::vector<std::vector<double> >& y,
                    const std::vector<double>& theta,
                    const size_t& num_eqns) {
      return y;
    }

    std::vector<std::vector<stan::agrad::var> > 
    compute_results(const std::vector<std::vector<double> >& y,
                    const std::vector<stan::agrad::var>& theta,
                    const size_t& num_eqns) {

      std::vector<stan::agrad::var> temp_vars;
      std::vector<double> temp_gradients;
      std::vector<std::vector<stan::agrad::var> > y_return(y.size());

      for (int i = 0; i < y.size(); i++) {
        temp_vars.clear();
        
        //iterate over number of equations
        for (int j = 0; j < num_eqns; j++) { 
          temp_gradients.clear();
          
          //iterate over parameters for each equation
          for (int k = 0; k < theta.size(); k++) { 
            temp_gradients.push_back(y[i][num_eqns + theta.size()*j + k]);
          }

          temp_vars.push_back(stan::agrad::precomputed_gradients(y[i][j], theta, temp_gradients));
        }

        y_return[i] = temp_vars;
      }

      return y_return;
    }
    
    template <typename F, typename T1, typename T2>
    std::vector<std::vector<typename stan::return_type<T1,T2>::type> >
    solve_ode(const F& f,
              const std::vector<T1>& y0, 
              const double& t0, // initial time
              const std::vector<double>& ts, // times at desired solutions
              const std::vector<T2>& theta, // parameters
              const std::vector<double>& x, // double data values
              const std::vector<int>& x_int) { // int data values.
      using namespace boost::numeric::odeint;  // FIXME: trim to what is used

      std::vector<double> theta_dbl;
      for (int i = 0; i < theta.size(); i++)
        theta_dbl.push_back(value_of(theta[i]));

      ode_system<F> system(f,theta_dbl,x,x_int);
      double absolute_tolerance = 1e-6;
      double relative_tolerance = 1e-6;

      std::vector<double> y0_vec((1+theta.size())*y0.size()); 
      for (size_t n = 0; n < y0.size(); n++)
        y0_vec[n] = value_of(y0[n]);
      for (size_t n = y0.size(); n < (1+theta.size()) * y0.size(); n++)
        y0_vec[n] = 0.0;

      std::vector<double> ts_vec(ts.size()+1);
      ts_vec[0] = t0;
      for (size_t n = 0; n < ts.size(); n++)
        ts_vec[n+1] = ts[n];
      
      double step_size = 0.1;
  
      std::vector<std::vector<double> > x_vec;
      std::vector<double> t_vec;
      push_back_state_and_time<double> obs(x_vec, t_vec);
      integrate_times(
         make_dense_output(absolute_tolerance,
                           relative_tolerance,
                           runge_kutta_dopri5<std::vector<double>,
                                              double,std::vector<double>,double>()),
         system,
         y0_vec,
         boost::begin(ts_vec), boost::end(ts_vec), 
         step_size,
         obs);

      std::vector<std::vector<double> > y = obs.get();

      return compute_results(y, theta, y0.size());
    }
                   
  }
}
#endif
