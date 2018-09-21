#ifndef STAN_MATH_GPU_SUBTRACT_HPP
#define STAN_MATH_GPU_SUBTRACT_HPP
#ifdef STAN_OPENCL
#include <CL/cl.hpp>
#include <stan/math/gpu/err/check_matching_dims.hpp>
#include <stan/math/gpu/kernels/subtract.hpp>
#include <stan/math/gpu/matrix_gpu.hpp>

namespace stan {
namespace math {

/**
 * Matrix subtraction on the GPU
 * Subtracts the second matrix
 * from the first matrix and stores
 * the result in the third matrix (C=A-B)
 *
 * @param A first matrix
 * @param B second matrix
 *
 * @return subtraction result matrix
 *
 * @throw <code>std::invalid_argument</code> if the
 * input matrices do not have matching dimensions.
 *
 */
inline matrix_gpu subtract(const matrix_gpu &A, const matrix_gpu &B) {
  check_matching_dims("subtract (GPU)", "A", A, "B", B);
  matrix_gpu C(A.rows(), A.cols());
  if (A.size() == 0) {
    return C;
  }
  cl::CommandQueue cmdQueue = opencl_context.queue();
  try {
    opencl_kernels::subtract(cl::NDRange(A.rows(), A.cols()), C.buffer(),
                             A.buffer(), B.buffer(), A.rows(), A.cols());
  } catch (cl::Error &e) {
    check_opencl_error("subtract", e);
  }
  return C;
}
} // namespace math
} // namespace stan

#endif
#endif
