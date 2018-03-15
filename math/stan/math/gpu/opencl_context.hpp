#ifndef STAN_MATH_GPU_OPENCL_CONTEXT_HPP
#define STAN_MATH_GPU_OPENCL_CONTEXT_HPP
#ifdef STAN_OPENCL
#define __CL_ENABLE_EXCEPTIONS

#include <stan/math/prim/arr/err/check_opencl.hpp>
#include <stan/math/prim/scal/err/system_error.hpp>
#include <CL/cl.hpp>
#include <cmath>
#include <fstream>
#include <map>
#include <vector>
#include <system_error>
#include <cerrno>

#define DEVICE_FILTER CL_DEVICE_TYPE_GPU
#ifndef OPENCL_DEVICE_ID
#define OPENCL_DEVICE_ID 0
#endif
#ifndef OPENCL_PLATFORM_ID
#define OPENCL_PLATFORM_ID 0
#endif

/**
 *  @file stan/math/gpu/opencl_context.hpp
 *  @brief Initialization for OpenCL:
 *    1. create context
 *    2. Find OpenCL platforms and devices available
 *    3. set up command queue
 *    4. initialize kernel groups
 */

namespace stan {
namespace math {

/**
 * The <code>opencl_context</code> class represents the OpenCL context.
 *
 * See the OpenCL specification glossary for a list of terms:
 * https://www.khronos.org/registry/OpenCL/specs/opencl-1.2.pdf.
 * The context includes the set of devices available on the host, command
 * queues, manages kernels.
 *
 * This is designed so there's only one instance running on the host.
 *
 * Some design decisions that may need to be addressed later:
 * - we are assuming a single OpenCL platform. We may want to run on multiple
 * platforms simulatenously
 * - we are assuming a single OpenCL device. We may want to run on multiple
 * devices simulatenously
 */
class opencl_context {
 private:
  cl::Context context_;  // Manages the the device, queue, platform, memory,etc.
  cl::CommandQueue command_queue_;       // job queue for device, one per device
  std::vector<cl::Platform> platforms_;  // Vector of available platforms
  cl::Platform platform_;                // The platform for compiling kernels
  std::string platform_name_;  // The platform such as NVIDIA OpenCL or AMD SDK
  std::vector<cl::Device> devices_;  // All available GPU devices
  cl::Device device_;                    // The selected GPU device
  std::string device_name_;              // The name of the GPU
  size_t max_workgroup_size_;  // The maximum size of a block of workers on GPU
  /** Holds meta information about a kernel
   * @param exists a bool to identify whether a kernel has been compiled
   * @param group The name of the compilation group for the kernel
   * @param code The source code for the kernel
   */
  struct kernel_meta_info {
    bool exists;
    const char* group;
    const char* raw_code;
  };
  /**
   * Map of a kernel name (first) and it's meta information (second).
   */
  typedef std::map<const char*, kernel_meta_info> map_kernel_info;
  /**
   * map holding compiled kernels.
   */
  typedef std::map<const char*, cl::Kernel> map_kernel;
  map_kernel_info kernel_info; // The meta kernel info
  map_kernel kernels; // The compiled kernels

  /**
   * Construct the opencl_context by initializing the
   * OpenCL context, devices, command queues, and kernel
   * groups.
   *
   * This constructor does the following:
   * 1. Gets the available platforms and selects the platform
   *  with id OPENCL_PLATFORM_ID
   * 2. Gets the available devices and selects the device with id
   *  OPENCL_DEVICE_ID
   * 3. Creates the OpenCL context with the device
   * 4. Creates the OpenCL command queue for the selected device
   * 5. Initializes the kernel groups by filling the <code> kernel_info </code>
   *  map.
   * @throw std::system_error if an OpenCL error occurs
   */
  opencl_context() {
    try {
      // platform
      cl::Platform::get(&platforms_);
      platform_ = platforms_[OPENCL_PLATFORM_ID];
      platform_name_ = platform_.getInfo<CL_PLATFORM_NAME>();
      platform_.getDevices(DEVICE_FILTER, &devices_);
      if (devices_.size() == 0) {
        system_error("OpenCL Initialization", "[Device]", -1,
                     "CL_DEVICE_NOT_FOUND");
      }
      device_ = devices_[OPENCL_DEVICE_ID];
      // context and queue
      context_ = cl::Context(device_);
      command_queue_ = cl::CommandQueue(context_, device_,
                                        CL_QUEUE_PROFILING_ENABLE, nullptr);
      // setup kernel groups
      init_kernel_groups();
      device_.getInfo<size_t>(CL_DEVICE_MAX_WORK_GROUP_SIZE,
                              &max_workgroup_size_);

    } catch (const cl::Error& e) {
      check_ocl_error("opencl_context", e.what(), e.err());
    }
  }
  /**
   * Initalizes the <code> kernel_info </code> where each kernel is mapped to
   * a logical flag to mark if the kernel was already compiled,
   * the name of the kernel group, and the OpenCL kernel sources.
   */
  inline void init_kernel_groups() {
    kernel_info["dummy"] = {
        false, "timing", "__kernel void dummy(__global const int* foo) { };"};
    kernel_info["dummy2"] = {
        false, "timing", "__kernel void dummy2(__global const int* foo) { };"};
  }

  /**
   * Compiles all the kernels in the specified. The side effect of this
   *  method places all compiled kernels for a group inside of <code> kernels
   *  </code>.
   *
   * @param kernel_name[in] The kernel name
   *
   * @throw std::system_error if there are compilation errors
   * when compiling the specified kernel group sources
   */
  inline void compile_kernel_group(const char* kernel_name) {
    char temp[100];
    int local = 32;
    int gpu_local_max = sqrt(max_workgroup_size());
    if (gpu_local_max < local)
      local = gpu_local_max;
    snprintf(temp, sizeof(temp), "-D TS=%d -D TS1=%d -D TS2=%d ", local, local,
             local);
    std::string kernel_source = "";
    const char* kernel_group = kernel_info[kernel_name].group;
    for (auto kern : kernel_info) {
      if (strcmp(kern.second.group, kernel_group) == 0) {
        kernel_source += kern.second.raw_code;
      }
    }

    try {
      cl::Program::Sources source(
          1,
          std::make_pair(kernel_source.c_str(), strlen(kernel_source.c_str())));
      cl::Program program_ = cl::Program(context_ , source);
      program_.build({device_}, temp);

      cl_int err = CL_SUCCESS;
      // Iterate over the kernel list and get all the kernels from this group
      // and mark them as compiled.
      for (auto kern : kernel_info) {
        if (strcmp(kern.second.group, kernel_group) == 0) {
          kernels[(kern.first)] = cl::Kernel(program_, kern.first, &err);
          kern.second.exists = true;
        }
      }
    } catch (const cl::Error& e) {
      check_ocl_error("Kernel Compilation", e.what(), e.err());
    }
  }

 public:

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
   * @param[in] kernel_name The kernel name
   *
   * @return a copy of the cl::Kernel object
   */
  inline cl::Kernel get_kernel(const char* kernel_name) {
    // Compile the kernel group and return the kernel
    if (!kernel_info[kernel_name].exists) {
      compile_kernel_group(kernel_name);
    }
    return kernels[kernel_name];
  }

  // FIXME:(Steve/Dan) should probably be deleted before merge
  void debug(std::ostream& s) {
    s << "inside opencl_context" << std::endl;
    s << " * platform_name_: " << platform_name_ << std::endl;
  }
  /**
   * Initializes the OpenCL context. This is made with a static local singleton
   * design so that only one context is available.
   */
  static opencl_context& getInstance() {
    static opencl_context instance;
    return instance;
  }

  /**
   * Returns the description of the OpenCL platform and device that is used.
   * Devices will be a GPU and Platforms are a specific OpenCL implimenation
   * such as AMD SDK's or Nvidia's OpenCL implimentation.
   */
  inline std::string description() const {
    std::ostringstream msg;
    msg << "Platform ID: " << OPENCL_DEVICE_ID << "\n";
    msg << "Platform Name: " << platform_.getInfo<CL_PLATFORM_NAME>() << "\n";
    msg << "Platform Vendor: " << platform_.getInfo<CL_PLATFORM_VENDOR>()
        << "\n";
    msg << "\tDevice " << OPENCL_DEVICE_ID << ": "
        << "\n";
    msg << "\t\tDevice Name: " << device_.getInfo<CL_DEVICE_NAME>() << "\n";
    msg << "\t\tDevice Type: " << device_.getInfo<CL_DEVICE_TYPE>() << "\n";
    msg << "\t\tDevice Vendor: " << device_.getInfo<CL_DEVICE_VENDOR>() << "\n";
    msg << "\t\tDevice Max Compute Units: "
        << device_.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << "\n";
    msg << "\t\tDevice Global Memory: "
        << device_.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() << "\n";
    msg << "\t\tDevice Max Clock Frequency: "
        << device_.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << "\n";
    msg << "\t\tDevice Max Allocateable Memory: "
        << device_.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>() << "\n";
    msg << "\t\tDevice Local Memory: "
        << device_.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>() << "\n";
    msg << "\t\tDevice Available: " << device_.getInfo<CL_DEVICE_AVAILABLE>()
        << "\n";
    return msg.str();
  }

  /**
   * Returns the description of the OpenCL platforms and devices that
   * are available. Devices will be a GPU and Platforms are a specific OpenCL
   * implimenation such as AMD SDK's or Nvidia's OpenCL implimentation.
   */
  inline std::string capabilities() const {
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    std::ostringstream msg;
    int platform_id = 0;
    int device_id = 0;

    msg << "Number of Platforms: " << all_platforms.size() << "\n";
    for (auto plat_iter : all_platforms) {
      cl::Platform platform(plat_iter);

      msg << "Platform ID: " << platform_id++ << "\n";
      msg << "Platform Name: " << platform.getInfo<CL_PLATFORM_NAME>() << "\n";
      msg << "Platform Vendor: " << platform.getInfo<CL_PLATFORM_VENDOR>()
          << "\n";

      std::vector<cl::Device> all_devices;
      platform.getDevices(CL_DEVICE_TYPE_GPU, &all_devices);

      for (auto device_iter : all_devices) {
        cl::Device device(device_iter);

        msg << "\tDevice " << device_id++ << ": "
            << "\n";
        msg << "\t\tDevice Name: " << device.getInfo<CL_DEVICE_NAME>() << "\n";
        msg << "\t\tDevice Type: " << device.getInfo<CL_DEVICE_TYPE>() << "\n";
        msg << "\t\tDevice Vendor: " << device.getInfo<CL_DEVICE_VENDOR>()
            << "\n";
        msg << "\t\tDevice Max Compute Units: "
            << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << "\n";
        msg << "\t\tDevice Global Memory: "
            << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() << "\n";
        msg << "\t\tDevice Max Clock Frequency: "
            << device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << "\n";
        msg << "\t\tDevice Max Allocateable Memory: "
            << device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>() << "\n";
        msg << "\t\tDevice Local Memory: "
            << device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>() << "\n";
        msg << "\t\tDevice Available: " << device.getInfo<CL_DEVICE_AVAILABLE>()
            << "\n";
      }
    }
    return msg.str();
  }

  /**
   * Returns the reference to the OpenCL context. The OpenCL context manages
   * objects such as the device, memory, command queue, program, and kernel
   * objects. For stan, there should only be one context, queue, device, and
   * program with multiple kernels.
   */
  inline cl::Context& context() { return context_; }
  /**
   * Returns the reference to the active OpenCL command queue for the device.
   * One command queue will exist per device where
   * kernels are placed on the command queue and by default executed in order.
   */
  inline cl::CommandQueue& queue() { return command_queue_; }
  /**
   * Returns the maximum workgroup size defined by CL_DEVICE_MAX_WORK_GROUP_SIZE
   * for the device in the context. This is the maximum product of work group
   * dimensions for a particular device. IE a max workgoup of 256 would allow
   * work groups of sizes (16,16), (128,2), (8, 32), etc.
   */
  inline int max_workgroup_size() { return max_workgroup_size_; }

  /**
   * Returns a vector containing the OpenCL device used to create the context
   */
  inline std::vector<cl::Device> device() { return {device_}; }

  /**
   * Returns a vector containing the OpenCL platform used to create the context
   */
  inline std::vector<cl::Platform> platform() { return {platform_}; }
};

static opencl_context opencl_context
    = stan::math::opencl_context::getInstance();

}  // namespace math
}  // namespace stan

#endif
#endif
