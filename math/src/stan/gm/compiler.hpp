#ifndef __STAN__GM__COMPILER_HPP__
#define __STAN__GM__COMPILER_HPP__

#include <stan/gm/ast.hpp>
#include <stan/gm/generator.hpp>
#include <stan/gm/parser.hpp>

#include <iostream>
#include <string>

namespace stan {

  namespace gm {

    /**
     * Read a Stan directed graphical model specification from the
     * specified input, parse it, and write the C++ code for it
     * to the specified output.
     *
     * @param stan_gm_in Graphical model specification
     * @param cpp_out C++ code output stream
     * @param model_name Name of model class
     * @param include_main Indicates whether to generate a 
     *    main function
     * @return <code>false</code> if code could not be generated
     *    due to syntax error in the Graphical model; 
     *    <code>true</code> otherwise.
     */
    bool compile(std::istream& stan_gm_in,
                 std::ostream& cpp_out,
                 const std::string& model_name,
                 bool include_main = true) {
      program prog;
      bool parsed_ok = parse(stan_gm_in,"input",prog);
      if (!parsed_ok) 
        return false; // syntax error in program
      generate_cpp(prog,model_name,cpp_out,include_main);
      return true;
    }
    

  }

}

#endif
