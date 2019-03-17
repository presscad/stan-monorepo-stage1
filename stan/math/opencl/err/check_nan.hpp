#ifndef STAN_MATH_OPENCL_ERR_CHECK_NAN_HPP
#define STAN_MATH_OPENCL_ERR_CHECK_NAN_HPP
#ifdef STAN_OPENCL
#include <stan/math/opencl/matrix_cl.hpp>
#include <stan/math/opencl/kernels/check_nan.hpp>
#include <stan/math/opencl/copy.hpp>
#include <stan/math/prim/scal/err/domain_error.hpp>

#include <vector>

namespace stan {
namespace math {
/**
 * Check if the <code>matrix_cl</code> has NaN values
 *
 * @param function Function name (for error messages)
 * @param name Variable name (for error messages)
 * @param y <code>matrix_cl</code> to test
 *
 * @throw <code>std::domain_error</code> if
 *    any element of the matrix is <code>NaN</code>.
 */
inline void check_nan(const char* function, const char* name,
                      const matrix_cl& y) {
  if (y.size() == 0)
    return;

  cl::CommandQueue cmd_queue = opencl_context.queue();
  cl::Context& ctx = opencl_context.context();
  try {
    int nan_flag = 0;
    matrix_cl nan_chk(1,1);
    copy(nan_chk, nan_flag);
    cl::Event check_event
        = opencl_kernels::check_nan(cl::NDRange(y.rows(), y.cols()), y,
                                    nan_chk, y.rows(), y.cols());
    nan_chk.add_event(check_event);
    copy(nan_flag, nan_chk);
    //  if NaN values were found in the matrix
    if (nan_flag) {
      domain_error(function, name, "has NaN values", "");
    }
  } catch (const cl::Error& e) {
    check_opencl_error("nan_check", e);
  }
}

}  // namespace math
}  // namespace stan
#endif
#endif
