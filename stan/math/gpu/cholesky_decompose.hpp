#ifndef STAN_MATH_GPU_CHOLESKY_DECOMPOSE_HPP
#define STAN_MATH_GPU_CHOLESKY_DECOMPOSE_HPP
#ifdef STAN_OPENCL
#include <stan/math/gpu/matrix_gpu.hpp>
#include <stan/math/gpu/kernels/cholesky_decompose.hpp>
#include <stan/math/gpu/multiply.hpp>
#include <stan/math/gpu/multiply_transpose.hpp>
#include <stan/math/gpu/lower_tri_inverse.hpp>
#include <stan/math/gpu/transpose.hpp>
#include <stan/math/gpu/subtract.hpp>
#include <stan/math/gpu/err/check_diagonal_zeros.hpp>
#include <stan/math/gpu/err/check_nan.hpp>
#include <CL/cl.hpp>
namespace stan {
namespace math {
/**
 * Return the lower-triangular Cholesky factor (i.e., matrix
 * square root) of the specified square, symmetric matrix.
 * The return value \f$L\f$ will be a lower-traingular matrix such that the
 * original matrix \f$A\f$ is given by
 * <p>\f$A = L \times L^T\f$.
 * The Cholesky decomposition is computed on the GPU. The
 * input matrix is transfered to the GPU and the resulting
 * lower-triangular matrix is then copied from the GPU.
 *
 * For a full guide to how this works
 * see the Cholesy decompostion chapter in the  reference report
 * <a href="https://github.com/SteveBronder/stancon2018/blob/master/report.pdf">
 * 
 * @param A Symmetric matrix on the GPU.
 * @param block size of the block for each cholesky decomposition step
 * @return Square root of matrix on the GPU.
 * @throw std::domain_error if m is not
 *  positive definite (if m has more than 0 elements)
 */
inline matrix_gpu cholesky_decompose(matrix_gpu& A, int block = 100, int divider = 2, int min_block = 100) {
  int offset = 0;
    
  matrix_gpu A_11(block, block);
  matrix_gpu L_11(block, block);
  // Repeats the blocked cholesky decomposition until the size of the remaining
  // submatrix is smaller or equal to the block size
  while ((offset + block) < (A.rows())) {
    matrix_gpu A_21(A.rows() - offset - block, block);
    matrix_gpu A_22(A.rows() - offset - block, A.rows() - offset - block);
    // Copies the A_11 submatrix from the input
    A_11.sub_block(A, offset, offset, 0, 0, block, block);
    // Calls the blocked cholesky for the submatrix A_11
    // or calls the kernel  directly if the size of the block is small enough
    if (block <= min_block || divider<=1) {
      L_11.zeros();
      try {
        opencl_kernels::cholesky_decompose(cl::NDRange(A_11.rows()), cl::NDRange(A_11.rows()),
                              A_11.buffer(), L_11.buffer(), A_11.rows());
      } catch (const cl::Error& e) {
        check_opencl_error("cholesky_decompose", e);
      }
    }else{
      // Recursive call
      L_11 = cholesky_decompose(A_11, block/divider);
    }
    // Copies the cholesky factor of A_11 back to the input matrix
    A.sub_block(L_11, 0, 0, offset, offset, block, block);
    // Copise the A_21 submatrix from the input matrix,
    // computes A_21*((L_11^-1)^T)
    // and copies the resulting submatrix to the input matrix
    A_21.sub_block(A, (offset + block), offset, 0, 0, (A.rows() - offset - block),
                block);    
    matrix_gpu A_11_inverse = lower_triangular_inverse(L_11);
    A_11_inverse = transpose(A_11_inverse);
    matrix_gpu L_21 =  multiply(A_21, A_11_inverse);  
    A.sub_block(L_21, 0, 0, (offset + block), offset, (A.rows() - offset - block),
                block);
    // Copies the A_22 submatrix from the input matrix,
    // computes A_22 - L_21*(L_21^T)
    // and copies the resulting submatrix back to the input matrix
    A_22.sub_block(A, (offset + block), (offset + block), 0, 0,
                       (A.rows() - offset - block),
                       (A.rows() - offset - block));
    matrix_gpu temp = multiply_transpose(L_21);
    matrix_gpu L_22 = subtract(A_22, temp);
    A.sub_block(L_22, 0, 0, (offset + block), (offset + block),
                (A.rows() - offset - block), (A.rows() - offset - block));
    offset += block;
  }
  // Computes the Cholesky factor for the remaining part of the matrix
  int remaining_rows = A.rows() - offset;
  if (remaining_rows > 0) {
    matrix_gpu A_11(remaining_rows, remaining_rows);
    matrix_gpu L_11(remaining_rows, remaining_rows);
    A_11.sub_block(A, offset, offset, 0, 0, remaining_rows, remaining_rows);
    // Calls the blocked cholesky for the submatrix A_11
    // or calls the kernel  directly if the size of the block is small enough
    if (block <= min_block || divider<=1) {
      L_11.zeros();
      try {
        opencl_kernels::cholesky_decompose(cl::NDRange(A_11.rows()), cl::NDRange(A_11.rows()),
                              A_11.buffer(), L_11.buffer(), A_11.rows());
      } catch (const cl::Error& e) {
        check_opencl_error("cholesky_decompose", e);
      }
    }else{
      L_11 = cholesky_decompose(A_11, block/divider);
    }    
    A.sub_block(L_11, 0, 0, offset, offset, remaining_rows, remaining_rows);
  }
  check_nan("cholesky_decompose_gpu", "Matrix m", A);
  check_diagonal_zeros("cholesky_decompose_gpu", "Matrix m", A);
  A.zeros<stan::math::TriangularViewGPU::Upper>();
  return A;
}
}  // namespace math
}  // namespace stan

#endif
#endif
