// Arguments: Doubles, Doubles, Doubles
#include <stan/math/prim/scal/prob/gumbel_cdf_log.hpp>

using std::vector;
using std::numeric_limits;
using stan::agrad::var;

class AgradCdfLogGumbel : public AgradCdfLogTest {
public:
  void valid_values(vector<vector<double> >& parameters,
        vector<double>& cdf_log) {
    vector<double> param(3);

    param[0] = 0.0;           // y
    param[1] = 0.0;           // mu
    param[2] = 1.0;           // beta
    parameters.push_back(param);
    cdf_log.push_back(std::log(0.36787944117144232159));     // expected cdf_log

    param[0] = 1.0;           // y
    param[1] = 0.0;           // mu
    param[2] = 1.0;           // beta
    parameters.push_back(param);
    cdf_log.push_back(std::log(0.6922006275553463538654219)); // expected cdf_log

    param[0] = -2.0;          // y
    param[1] = 0.0;           // mu
    param[2] = 1.0;           // beta
    parameters.push_back(param);
    cdf_log.push_back(std::log(0.000617978989331093498619521)); // expected cdf_log

    param[0] = -3.5;          // y
    param[1] = 1.9;           // mu
    param[2] = 7.2;           // beta
    parameters.push_back(param);
    cdf_log.push_back(std::log(0.1203922620798295861862650)); // expected cdf_log
  }
  
  void invalid_values(vector<size_t>& index, 
                      vector<double>& value) {
    // y
    
    // mu
    index.push_back(1U);
    value.push_back(numeric_limits<double>::infinity());

    index.push_back(1U);
    value.push_back(-numeric_limits<double>::infinity());

    // beta
    index.push_back(2U);
    value.push_back(0.0);

    index.push_back(2U);
    value.push_back(-1.0);

    index.push_back(2U);
    value.push_back(-numeric_limits<double>::infinity());
  }
  
  bool has_lower_bound() {
    return false;
  }
  
  bool has_upper_bound() {
    return false;
  }

  template <typename T_y, typename T_loc, typename T_scale,
            typename T3, typename T4, typename T5>
  typename stan::return_type<T_y, T_loc, T_scale>::type 
  cdf_log(const T_y& y, const T_loc& mu, const T_scale& beta,
          const T3&, const T4&, const T5&) {
    return stan::prob::gumbel_cdf_log(y, mu, beta);
  }


  template <typename T_y, typename T_loc, typename T_scale,
            typename T3, typename T4, typename T5>
  typename stan::return_type<T_y, T_loc, T_scale>::type 
  cdf_log_function(const T_y& y, const T_loc& mu, const T_scale& beta,
                   const T3&, const T4&, const T5&) {
    return -exp(-(y - mu) / beta);
  }
};
