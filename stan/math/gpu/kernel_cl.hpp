#ifndef STAN_MATH_GPU_CL_HPP
#define STAN_MATH_GPU_CL_HPP
#ifdef STAN_OPENCL
#include <stan/math/gpu/opencl_context.hpp>
#include <stan/math/gpu/constants.hpp>
#include <CL/cl.hpp>
#include <string>
#include <map>
#include <vector>

namespace stan {
namespace math {

class kernel_cl_base {
  friend class kernel_cl;

 private:
  const char* copy_matrix =
#include <stan/math/gpu/kernels/copy_matrix.cl>  // NOLINT
      ;                                                 // NOLINT
  const char* transpose_matrix =
#include <stan/math/gpu/kernels/transpose_matrix.cl>  // NOLINT
      ;                                                      // NOLINT
  const char* zeros_matrix =
#include <stan/math/gpu/kernels/zeros_matrix.cl>  // NOLINT
      ;                                                  // NOLINT
  const char* identity_matrix =
#include <stan/math/gpu/kernels/identity_matrix.cl>  // NOLINT
      ;                                                     // NOLINT
  const char* copy_triangular_matrix =
#include <stan/math/gpu/kernels/copy_triangular_matrix.cl>  // NOLINT
      ;                                                            // NOLINT
  const char* copy_triangular_transposed_matrix =
#include <stan/math/gpu/kernels/triangular_transpose.cl>  // NOLINT
      ;                                                          // NOLINT
  const char* copy_submatrix =
#include <stan/math/gpu/kernels/sub_block.cl>  // NOLINT
      ;                                               // NOLINT
  const char* check_nan =
#include <stan/math/gpu/kernels/check_nan.cl>  // NOLINT
      ;                                               // NOLINT
  const char* check_diagonal_zeros =
#include <stan/math/gpu/kernels/check_diagonal_zeros.cl>  // NOLINT
      ;                                                          // NOLINT
  const char* check_symmetric =
#include <stan/math/gpu/kernels/check_symmetric.cl>  // NOLINT
      ;                                                     // NOLINT
  const char* subtract_symmetric =
#include <stan/math/gpu/kernels/subtract_matrix.cl>  // NOLINT
      ;                                                     // NOLINT
  const char* add_symmetric =
#include <stan/math/gpu/kernels/add_matrix.cl>  // NOLINT
      ;                                                // NOLINT

 protected:
	const char* helpers =
#include <stan/math/gpu/kernels/helpers.cl> // NOLINT
			; // NOLINT
  // Holds Default parameter values for each Kernel.
  typedef std::map<const char*, int> map_base_opts;
  const map_base_opts base_opts = {{"LOWER", gpu::Lower},
                                   {"UPPER", gpu::Upper},
                                   {"ENTIRE", gpu::Entire},
                                   {"UPPER_TO_LOWER", gpu::UpperToLower},
                                   {"LOWER_TO_UPPER", gpu::LowerToUpper}};

  /** Holds meta information about a kernel.
   * @param exists a bool to identify whether a kernel has been compiled.
   * @param group The name of the compilation group for the kernel.
   * @param opts The compile time options for the kernel.
   * @param code The source code for the kernel.
   */
  struct kernel_meta_info {
    bool exists;
    std::vector<const char*> opts;
    const char* raw_code;
  };
  /**
   * Map of a kernel name (first) and it's meta information (second).
   */
  typedef std::map<const char*, kernel_meta_info> map_table;
  const map_table kernel_table
      = {{"dummy",
          {false, {}, "_ void dummy(__global const int* foo) { };"}},
         {"dummy2",
          {false, {}, "_ void dummy2(__global const int* foo) { };"}},
         {"copy", {false, {}, copy_matrix}},
         {"transpose", {false, {}, transpose_matrix}},
         {"zeros", {false, {"LOWER", "UPPER", "ENTIRE"}, zeros_matrix}},
         {"identity", {false, {}, identity_matrix}},
         {"copy_triangular", {false, {}, copy_triangular_matrix}},
         {"copy_triangular_transposed",
          {false,
           {"LOWER_TO_UPPER", "UPPER_TO_LOWER"},
           copy_triangular_transposed_matrix}},
         {"copy_submatrix", {false, {}, copy_submatrix}},
         {"add", {false, {}, add_symmetric}},
         {"subtract", {false, {}, subtract_symmetric}},
         {"is_nan", {false, {}, check_nan}},
         {"is_zero_on_diagonal", {false, {}, check_diagonal_zeros}},
         {"is_symmetric", {false, {}, check_symmetric}}};
  typedef std::map<const char*, cl::Kernel> map;
  map kernels;  // The compiled kernels

  static kernel_cl_base& getInstance() {
    static kernel_cl_base instance_;
    return instance_;
  }
  kernel_cl_base() = default;
  kernel_cl_base(kernel_cl_base const&) = delete;
  void operator=(kernel_cl_base const&) = delete;
};

class kernel_cl {
 public:
  cl::Kernel compiled_;
  /**
   * Compiles all the kernels in the specified group. The side effect of this
   *  method places all compiled kernels for a group inside of <code> kernels
   *  </code>.
   *
   * @param kernel_name The kernel name.
   *
   * @throw std::system_error if there are compilation errors
   * when compiling the specified kernel group's source code
   * or std::domain_error if the kernel with the specified
   * name does not exist
   */
  inline void compile_group(const char* kernel_name) {
    if (this->kernel_table().count(kernel_name) == 0) {
      // throws if the kernel does not exist
      domain_error("compiling kernels", kernel_name, " kernel does not exist",
                   "");
    }
    kernel_cl_base::kernel_meta_info kernel_info
        = this->kernel_table()[kernel_name];
    std::string kernel_opts = "";
		std::string kernel_source = std::string(get_helpers());
    kernel_source += kernel_info.raw_code;
    for (auto comp_opts : kernel_info.opts) {
      if (strcmp(comp_opts, "") != 0) {
        kernel_opts += std::string(" -D") + comp_opts + "="
                       + std::to_string(this->base_options()[comp_opts]);
      }
    }
    try {
      cl::Program::Sources source(
          1,
          std::make_pair(kernel_source.c_str(), strlen(kernel_source.c_str())));
      cl::Program program_ = cl::Program(opencl_context.context(), source);
      program_.build({opencl_context.device()}, kernel_opts.c_str());

      cl_int err = CL_SUCCESS;
      // Iterate over the kernel list and get all the kernels from this group
      // and mark them as compiled.
      kernel_cl_base::getInstance().kernels[(kernel_name)]
          = cl::Kernel(program_, kernel_name, &err);
      kernel_info.exists = true;
    } catch (const cl::Error& e) {
      check_opencl_error("Kernel Compilation", e);
    }
  }
  /**
   * Returns the kernel specified in kernel_name.
   * If the kernel has not yet been compiled, the kernel group is compiled
   * first.
   *
   * @brief Passing the name of a kernel compiles all kernels in the same group
   * as the selected kernel.
   * OpenCL kernels are compiled JIT, instead of compiling each kernel
   * individually this function will compile all kernels
   * in a predefined group. Groupings are made such that kernels commonly
   * called with one another will be compiled at the same time. For example,
   * An arithmetic group of kernels compiled together could contain the kernels
   * for <code> add() </code>, <code> subtract() </code>,
   * and <code> multiply() </code>. This function will only return the kernel
   * which was called, but when a user asks for a kernel within the group those
   * kernels will already be compiled.
   *
   * @param kernel_name The kernel name.
   */
  explicit kernel_cl(const char* kernel_name) {
    // Compile the kernel group and return the kernel
    if (!this->kernel_table()[kernel_name].exists) {
      this->compile_group(kernel_name);
    }
    compiled_ = kernel_cl_base::getInstance().kernels[(kernel_name)];
  }
  /**
   * Terminating function for recursively setting arguments in an OpenCL kernel.
   *
   * @param k An OpenCL kernel.
   * @param i The <code>i</code>th argument to the kernel.
   * @note This function definition serves to end the recursive call for
   * <code>set_args()</code>
   */
  inline void recursive_args(cl::Kernel& k, int i) {}

  /**
   * Used in <code>set_args()</code> to add arguments to an OpenCL
   * kernel.
   *
   * @param kernel An OpenCL kernel.
   * @param i the position of the argument to the OpenCL kernel.
   * @param first_arg The first argument to go into the OpenCL kernel.
   * @param extra_args The remaining arguments to go into the OpenCL kernel.
   * @tparam T the type of <code>first_arg</code>.
   * @tparam Args The types of <code>extra_args</code>.
   * @note Comes from:
   * simpleopencl.blogspot.com/2013/04/calling-kernels-with-large-number-of.html
   */
  template <typename T, typename... Args>
  inline void recursive_args(cl::Kernel& kernel, int i, const T& first_arg,
                             const Args&... extra_args) {
    kernel.setArg(i, first_arg);
    this->recursive_args(kernel, i + 1, extra_args...);
  }

  /**
   * Adds arguments to an OpenCL kernel.
   *
   * @param kernel An OpenCL kernel.
   * @param args The arguments to mote to the OpenCL kernel.
   * @tparam Args The types of <code>extra_args</code>.
   * @note Comes from:
   * simpleopencl.blogspot.com/2013/04/calling-kernels-with-large-number-of.html
   */
  template <typename... Args>
  inline void set_args(cl::Kernel& kernel, const Args&... args) {
    this->recursive_args(kernel, 0, args...);
  }
  template <typename... Args>
  inline void set_args(const Args&... args) {
    this->recursive_args(this->compiled_, 0, args...);
  }
  /**
   * return information on the kernel_source
   */
  inline kernel_cl_base::map_table kernel_table() {
    return kernel_cl_base::getInstance().kernel_table;
  }

  /**
   * return all compiled kernels.
   */
  inline kernel_cl_base::map kernels() {
    return kernel_cl_base::getInstance().kernels;
  }

  /*
   * return the base kernel compiler options
   */
  inline kernel_cl_base::map_base_opts base_options() {
    return kernel_cl_base::getInstance().base_opts;
  }

	/**
	 * Returns helper macros for use in the kernels
	 *  For ease of coding, several helper macros have been placed
	 *   in stan/math/gpu/kernels/helpers.cl. This function retrieves those
	 *   macros so they can be added to the kernel string pre-compilation.
	 */
	const char* get_helpers() {
		return kernel_cl_base::getInstance().helpers;
	}
};
}  // namespace math
}  // namespace stan

#endif
#endif
