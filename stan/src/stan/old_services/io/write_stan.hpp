#ifndef STAN_OLD_SERVICES_IO_WRITE_STAN_HPP
#define STAN_OLD_SERVICES_IO_WRITE_STAN_HPP

#include <stan/callbacks/writer/base_writer.hpp>
#include <stan/version.hpp>
#include <string>

namespace stan {
  namespace services {
    namespace io {

      void write_stan(callbacks::writer::base_writer& writer) {
        writer("stan_version_major = " + stan::MAJOR_VERSION);
        writer("stan_version_minor = " + stan::MINOR_VERSION);
        writer("stan_version_patch = " + stan::PATCH_VERSION);
      }

    }
  }
}
#endif
