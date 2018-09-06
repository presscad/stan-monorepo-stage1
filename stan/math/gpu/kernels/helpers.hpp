#ifndef STAN_MATH_GPU_KERNELS_HELPERS_HPP
#define STAN_MATH_GPU_KERNELS_HELPERS_HPP
#ifdef STAN_OPENCL

#include <string>

namespace stan {
namespace math {
namespace opencl_kernels {

/*
 * Defines some helper macros for the kernels
 */
std::string helpers =
    R"(
    // Matrix access helpers
  #ifndef A
  #define A(i,j) A[j * rows + i]
  #endif
  #ifndef B
  #define B(i,j) B[j * rows + i]
  #endif
  #ifndef C
  #define C(i,j) C[j * rows + i]
  #endif
    // Transpose
  #ifndef BT
  #define BT(i,j) B[j * cols + i]
  #endif
  #ifndef AT
  #define AT(i,j) A[j * cols + i]
  #endif
    // Moving between two buffers
  #ifndef src
  #define src(i,j) src[j * src_rows + i]
  #endif
  #ifndef dst
  #define dst(i,j) dst[j * dst_rows + i]
  #endif
    // lower triangular inverse
  #ifndef V
  #define V(i,j) V[offset+j*(part_size_fixed+1)+i] 
  #endif    
  #ifndef temp
  #define temp(i,j) temp[(n/2)*(sizeM)*(sizeM)+j*part_size2+i]
  #endif
  #define TS2 32
  #define WPT 4
  #define RTS TS2/WPT
  // The local memory column for each thread block
  #define THREAD_BLOCK_SIZE_COL THREAD_BLOCK_SIZE/WORK_PER_THREAD

  )";
}  // namespace opencl_kernels
}  // namespace math
}  // namespace stan
#endif
#endif
