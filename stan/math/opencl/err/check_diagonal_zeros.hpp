#ifndef STAN_MATH_OPENCL_ERR_CHECK_DIAGONAL_ZEROS_HPP
#define STAN_MATH_OPENCL_ERR_CHECK_DIAGONAL_ZEROS_HPP
#ifdef STAN_OPENCL
#include <stan/math/opencl/matrix_cl.hpp>
#include <stan/math/opencl/kernels/check_diagonal_zeros.hpp>
#include <stan/math/opencl/copy.hpp>
#include <stan/math/prim/scal/err/domain_error.hpp>
#include <vector>

namespace stan {
namespace math {
/**
 * Check if the <code>matrix_cl</code> has zeros on the diagonal
 *
 * @param function Function name (for error messages)
 * @param name Variable name (for error messages)
 * @param y <code>matrix_cl</code> to test
 *
 * @throw <code>std::domain_error</code> if
 *    any diagonal element of the matrix is zero.
 */
inline void check_diagonal_zeros(const char* function, const char* name,
                                 const matrix_cl& y) {
  if (y.size() == 0)
    return;
  cl::CommandQueue cmd_queue = opencl_context.queue();
  cl::Context ctx = opencl_context.context();
  try {
    int zero_on_diagonal_flag = 0;
    matrix_cl zeros_flag(1,1);
    copy(zeros_flag, zero_on_diagonal_flag);
    cl::Event check_event = opencl_kernels::check_diagonal_zeros(
        cl::NDRange(y.rows(), y.cols()), y, zeros_flag, y.rows(), y.cols());
    zeros_flag.add_event(check_event);
    copy(zero_on_diagonal_flag, zeros_flag);
    //  if zeros were found on the diagonal
    if (zero_on_diagonal_flag) {
      domain_error(function, name, "has zeros on the diagonal.", "");
    }
  } catch (const cl::Error& e) {
    check_opencl_error("diag_zeros_check", e);
  }
}

}  // namespace math
}  // namespace stan
#endif
#endif
