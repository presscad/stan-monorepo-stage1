#ifdef STAN_OPENCL
#include <stan/math/prim/mat.hpp>
#include <gtest/gtest.h>
#include <CL/cl.hpp>

TEST(MathMatrix, kernel_initialize) {
  EXPECT_NO_THROW(cl::Kernel kernel_transpose
                  = stan::math::opencl_context.get_kernel("transpose"));
  EXPECT_NO_THROW(cl::Kernel kernel_copy = stan::math::opencl_context.get_kernel("copy"));
  EXPECT_NO_THROW(cl::Kernel kernel_zeros = stan::math::opencl_context.get_kernel("zeros"));
  EXPECT_NO_THROW(cl::Kernel kernel_identity
                  = stan::math::opencl_context.get_kernel("identity"));
  EXPECT_NO_THROW(cl::Kernel kernel_copy_triangular
                  = stan::math::opencl_context.get_kernel("copy_triangular"));
  EXPECT_NO_THROW(cl::Kernel kernel_scalar_copy_triangular_transposed
                  = stan::math::opencl_context.get_kernel("copy_triangular_transposed"));
  EXPECT_NO_THROW(cl::Kernel kernel_add = stan::math::opencl_context.get_kernel("add"));
  EXPECT_NO_THROW(cl::Kernel kernel_subtract
                  = stan::math::opencl_context.get_kernel("subtract"));
  EXPECT_NO_THROW(cl::Kernel kernel_copy_submatrix
                  = stan::math::opencl_context.get_kernel("copy_submatrix"));
  EXPECT_NO_THROW(cl::Kernel kernel_scalar_mul_diagonal
                  = stan::math::opencl_context.get_kernel("scalar_mul_diagonal"));
  EXPECT_NO_THROW(cl::Kernel kernel_scalar_mul
                  = stan::math::opencl_context.get_kernel("scalar_mul"));
  EXPECT_NO_THROW(cl::Kernel kernel_basic_multiply
                  = stan::math::opencl_context.get_kernel("basic_multiply"));
  EXPECT_NO_THROW(cl::Kernel kernel_multiply_self_transposed
                  = stan::math::opencl_context.get_kernel("multiply_self_transposed"));
  EXPECT_NO_THROW(cl::Kernel kernel_lower_tri_inv_step1
                  = stan::math::opencl_context.get_kernel("lower_tri_inv_step1"));
  EXPECT_NO_THROW(cl::Kernel kernel_lower_tri_inv_step2
                  = stan::math::opencl_context.get_kernel("lower_tri_inv_step2"));
  EXPECT_NO_THROW(cl::Kernel kernel_lower_tri_inv_step3
                  = stan::math::opencl_context.get_kernel("lower_tri_inv_step3"));
  EXPECT_NO_THROW(cl::Kernel kernel_chol_block
                  = stan::math::opencl_context.get_kernel("cholesky_block"));
  EXPECT_NO_THROW(cl::Kernel kernel_check_nan
                  = stan::math::opencl_context.get_kernel("check_nan"));
  EXPECT_NO_THROW(cl::Kernel kernel_check_diagonal_zeros
                  = stan::math::opencl_context.get_kernel("check_diagonal_zeros"));
  EXPECT_NO_THROW(cl::Kernel kernel_check_symmetric
                  = stan::math::opencl_context.get_kernel("check_symmetric"));
}

#else

#include <gtest/gtest.h>
TEST(MathMatrix, kernel_initializeDummy) { EXPECT_NO_THROW(); }
#endif
