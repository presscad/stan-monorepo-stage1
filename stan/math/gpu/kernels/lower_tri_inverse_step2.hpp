#ifndef STAN_MATH_GPU_KERNELS_LOWER_TRI_INVERSE_HPP
#define STAN_MATH_GPU_KERNELS_LOWER_TRI_INVERSE_HPP
#ifdef STAN_OPENCL

#include <stan/math/gpu/kernel_cl.hpp>

namespace stan {
namespace math {
namespace opencl_kernels {
// \cond
const char* lower_tri_inverse_step2_kernel_code = STRINGIFY(
    // \endcond
    /**
     * Calculates 
     *
     * @param[in,out] A The identity matrix output.
     * @param rows The number of rows for A.
     * @param cols The number of cols for A.
     * @note Code is a <code>const char*</code> held in
     * <code>identity_kernel_code.</code>
     *  Used in math/gpu/identity_opencl.hpp.
     *  This kernel uses the helper macros available in helpers.cl.
     */
    __kernel void lower_tri_inverse_step2(
        __global double* A,
        __global int* sizes,
        __global double* temp,
        int repeat,
        int remainder,
        int part_size_fixed,
        int rows) {
int n = get_global_id(2)*2;
 double sum = 0;
 int part_size1 = 0;
 int part_size2 = 0;
 int offset_i = 0;
 int offset_j = 0;
 for (int r = n*repeat; r < (n+1)*repeat; r++)
  part_size1 += sizes[r];
 for (int r = (n+1)*repeat; r < (n+2)*repeat; r++)
  part_size2 += sizes[r];
 int sizeM = repeat*(part_size_fixed+1);
 offset_i = (n+1)*repeat*part_size_fixed;
 offset_j = n*repeat*part_size_fixed;
 if ( ((n+1)*repeat) <= remainder )
  offset_i += (n+1)*repeat;
 else
  offset_i += remainder;
 if ( (n*repeat) <= remainder )
  offset_j += n*repeat;
 else
  offset_j += remainder;
 const int row = get_local_id(0);
 const int col = get_local_id(1);
  const int i = TS2*get_group_id(0) + row;
  const int j = TS2*get_group_id(1) + col;
  __local double Asub[TS2][TS2];
  __local double Bsub[TS2][TS2];
  double acc[WPT];
  for (int w = 0; w < WPT; w++) {
      acc[w] = 0.0;
  }

 const int numTiles = (part_size2+TS2-1)/TS2;
 sum = 0;
 for (int t = 0; t < numTiles; t++) {
  for (int w = 0; w < WPT; w++) {
   const int tiledRow = TS2*t + row;
   const int tiledCol = TS2*t + col;

   if ( i < part_size2 && (tiledCol+w*RTS) < part_size1 &&
    (tiledCol+offset_j+part_size1+w*RTS) < rows  &&
    (i+offset_i) < rows ) {
  Asub[col+w*RTS][row] =
    A((i+offset_i),(tiledCol+offset_j+part_size1+w*RTS));
  } else {
  Asub[col+w*RTS][row] = 0.0;
   }

   if ( (j+w*RTS) < part_size1 && tiledRow < part_size2 &&
    (tiledRow+offset_i) < rows && (j+offset_j+w*RTS) < rows ) {
  Bsub[col+w*RTS][row] = A((tiledRow+offset_i),(j+offset_j+w*RTS));
   } else {
  Bsub[col+w*RTS][row] = 0.0;
  }
  }

  barrier(CLK_LOCAL_MEM_FENCE);

  for (int k = 0; k < TS2; k++) {
   for (int w = 0; w < WPT; w++) {
  acc[w] += Asub[k][row]*Bsub[col+w*RTS][k];
   }
  }
  barrier(CLK_LOCAL_MEM_FENCE);
 }

 for (int w = 0; w < WPT; w++) {
  if ( i < part_size2 && (j+w*RTS) < part_size1 &&
     i < sizeM && (j+w*RTS) < sizeM ) {
   temp(i,(j+w*RTS)) = acc[w];
  }
 }
}
    // \cond
);
// \endcond

/**
 * See the docs for \link kernels/matrix_multiply.hpp add() \endlink
 */
const local_range_kernel<cl::Buffer, cl::Buffer, cl::Buffer, int, int, int, int>
    lower_tri_inverse_step2("lower_tri_inverse_step2", lower_tri_inverse_step2_kernel_code);

}  // namespace opencl_kernels
}  // namespace math
}  // namespace stan
#endif
#endif
