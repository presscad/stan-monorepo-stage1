#ifndef STAN_MATH_GPU_KERNELS_COPY_HPP
#define STAN_MATH_GPU_KERNELS_COPY_HPP

#ifndef STRINGIFY
#define STRINGIFY(src) #src
#endif

#include <stan/math/gpu/kernel_cl.hpp>

namespace stan {
namespace math {
namespace opencl_kernels {
// \cond
const char *copy_kernel_code = STRINGIFY(
    // \endcond
    /**
     * Copy one matrix to another
     * @param[in] A The matrix to copy.
     * @param[out] B The matrix to copy A to.
     * @param rows The number of rows in A.
     * @param cols The number of cols in A.
     * @note Code is a <code>const char*</code> held in
     * <code>copy_kernel_code.</code>
     * Kernel used in math/gpu/matrix_gpu.hpp.
     *  This kernel uses the helper macros available in helpers.cl.
     */
    __kernel void copy(
        __global read_only double *A, __global write_only double *B,
        read_only unsigned int rows, read_only unsigned int cols) {
      int i = get_global_id(0);
      int j = get_global_id(1);
      if (i < rows && j < cols) {
        B(i, j) = A(i, j);
      }
    }
    // \cond
);
// \endcond

/**
 * See the docs for \link kernels/copy.hpp copy() \endlink
 */
const global_range_kernel<cl::Buffer, cl::Buffer, int, int> copy(
    "copy", copy_kernel_code);

}  // namespace opencl_kernels
}  // namespace math
}  // namespace stan
#endif
