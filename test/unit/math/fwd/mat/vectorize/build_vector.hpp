#ifndef TEST_UNIT_MATH_FWD_MAT_TECTORIZE_BUILD_TECTOR_HPP
#define TEST_UNIT_MATH_FWD_MAT_TECTORIZE_BUILD_TECTOR_HPP

#include <stan/math/fwd/core/fvar.hpp>
#include <vector>

template <typename F>
static inline std::vector<double>
build_vector(std::vector<double> double_vector,
                          int seed_index = -1) { 
  return F::valid_inputs();
}

template <typename F, typename T>
static inline std::vector<stan::math::fvar<T> >
build_vector(std::vector<stan::math::fvar<T> > fvar_vector,
                        int seed_index = -1) { 
  using std::vector;
  using stan::math::fvar;

  vector<T> template_vector
    = build_vector<F>(vector<T>(), seed_index);

  for (size_t i = 0; i < template_vector.size(); ++i) {
  
    // For fvar<fvar<double> >, this will fill in 
    // all four components
    if (seed_index == static_cast<int>(i))
      fvar_vector
        .push_back(fvar<T>(template_vector[i], template_vector[i]));
    else
      fvar_vector.push_back(fvar<T>(template_vector[i]));
  }
  return fvar_vector;
}

#endif
