##
# Stan
# -----------------
#
# To customize your build, set make variables in either:
#    ~/.config/stan/make.local
#    make/local
# Variables in make/local is loaded after ~/.config/stan/make.local


## 'help' is the default make target.
help:

-include $(HOME)/.config/stan/make.local  # user-defined variables
-include make/local                       # user-defined variables

MATH ?= lib/stan_math/
ifeq ($(OS),Windows_NT)
  O_STANC ?= 3
endif
O_STANC ?= 0

-include $(MATH)make/compiler_flags
-include $(MATH)make/dependencies
-include $(MATH)make/libraries
include make/libstanc                     # bin/libstanc.a
include make/doxygen                      # doxygen
include make/manual                       # manual: manual, doc/stan-reference.pdf
include make/cpplint                      # cpplint
include make/tests                        # tests

INC_FIRST = -I $(if $(STAN),$(STAN)/src,src)
LDLIBS_STANC ?= -Ltest -lstanc


.PHONY: help
help:
	@echo '--------------------------------------------------------------------------------'
	@echo 'Stan makefile:'
	@echo '  Current configuration:'
	@echo '  - OS_TYPE (Operating System): ' $(OS)
	@echo '  - CXX (Compiler):             ' $(CXX)
	@echo '  - CXX_TYPE                    ' $(CXX_TYPE)
	@echo '  - Compiler version:           ' $(CXX_MAJOR).$(CXX_MINOR)
	@echo '  - O (Optimization Level):     ' $(O)
	@echo '  - O_STANC (Opt for stanc):    ' $(O_STANC)
	@echo '  - MATH                        ' $(MATH)
	@echo '  - STAN                        ' $(STAN)
	@echo '  Library configuration:'
	@echo '  - EIGEN                       ' $(EIGEN)
	@echo '  - BOOST                       ' $(BOOST)
	@echo '  - SUNDIALS                    ' $(SUNDIALS)
	@echo '  - GTEST                       ' $(GTEST)
	@echo '  - STAN_OPENCL                 ' $(STAN_OPENCL)
	@echo '  - STAN_MPI                    ' $(STAN_MPI)
	@echo '  Compiler flags (each can be overriden separately):'
	@echo '  - CXXFLAGS_LANG               ' $(CXXFLAGS_LANG)
	@echo '  - CXXFLAGS_WARNINGS           ' $(CXXFLAGS_WARNINGS)
	@echo '  - CXXFLAGS_BOOST              ' $(CXXFLAGS_BOOST)
	@echo '  - CXXFLAGS_EIGEN              ' $(CXXFLAGS_EIGEN)
	@echo '  - CXXFLAGS_OS                 ' $(CXXFLAGS_OS)
	@echo '  - CXXFLAGS_GTEST              ' $(CXXFLAGS_GTEST)
	@echo '  - CXXFLAGS_OPENCL             ' $(CXXFLAGS_OPENCL)
	@echo '  - CXXFLAGS_MPI                ' $(CXXFLAGS_MPI)
	@echo '  - CFLAGS_SUNDIALS             ' $(CFLAGS_SUNDIALS)
	@echo '  LDLIBS:'
	@echo '    $(LDLIBS)'
	@echo '  LDFLAGS:'
	@echo '    $(LDFLAGS)'
	@echo ''
	@echo 'Common targets:'
	@echo '  Documentation:'
	@echo '  - doc            : Builds the documention and copies to doc/'
	@echo '                     (requires LaTeX and bookdown installation)'
	@echo '  - doxygen        : Builds the API documentation. The documentation is located'
	@echo '                     doc/api/'
	@echo '                     (requires doxygen installation)'
	@echo '  Submodule:'
	@echo '  - math-revert    : Resets the Stan Math Library git submodule to the tagged'
	@echo '                     version'
	@echo '  - math-update    : Updates the Stan Math Library git submodule to the latest'
	@echo '                     development version'
	@echo '  - math-update/<branch-name> : Updates the Stan Math Library git submodule to'
	@echo '                     the branch specified'
	@echo ''
	@echo 'Tests:'
	@echo ''
	@echo '  Unit tests are built through make by specifying the executable as the target'
	@echo '  to make. For a test in src/test/*_test.cpp, the executable is test/*$(EXE).'
	@echo ''
	@echo '  Header tests'
	@echo '  - test-headers  : tests all source headers to ensure they are compilable and'
	@echo '                     include enough header files.'
	@echo ''
	@echo '  To run a single header test, add "-test" to the end of the file name.'
	@echo '  Example: make src/stan/math/constants.hpp-test'
	@echo ''
	@echo '  Cpplint'
	@echo '  - cpplint       : runs cpplint.py on source files. requires python 2.7.'
	@echo '                    cpplint is called using the CPPLINT variable:'
	@echo '                      CPPLINT = $(CPPLINT)'
	@echo '                    To set the version of python 2, set the PYTHON2 variable:'
	@echo '                      PYTHON2 = $(PYTHON2)'
	@echo ''
	@echo 'Clean:'
	@echo '  - clean         : Basic clean. Leaves doc and compiled libraries intact.'
	@echo '  - clean-manual  : Cleans temporary files from building the manual.'
	@echo '  - clean-deps    : Removes dependency files for tests. If tests stop building,'
	@echo '                    run this target.'
	@echo '  - clean-all     : Cleans up all of Stan.'
	@echo ''
	@echo 'Higher level targets:'
	@echo '  - docs          : Builds all docs.'
	@echo ''
	@echo '--------------------------------------------------------------------------------'


##
# Documentation
##

.PHONY: docs
docs: doc doxygen

##
# Clean up.
##
MODEL_SPECS := $(shell find src/test -type f -name '*.stan')
.PHONY: clean clean-demo clean-dox clean-manual clean-models clean-all clean-deps
clean:
	$(RM) $(shell find src -type f -name '*.dSYM') $(shell find src -type f -name '*.d.*')
	$(RM) $(wildcard $(MODEL_SPECS:%.stan=%.hpp))
	$(RM) $(wildcard $(MODEL_SPECS:%.stan=%$(EXE)))
	$(RM) $(wildcard $(MODEL_SPECS:%.stan=%.o))
	$(RM) $(wildcard $(MODEL_SPECS:%.stan=%.d))

clean-dox:
	$(RM) -r doc/api

clean-deps:
	@echo '  removing dependency files'
	$(shell find . -type f -name '*.d' -exec rm {} +)

clean-all: clean clean-docs clean-deps clean-libraries
	$(RM) -r test bin
	@echo '  removing .o files'
	$(shell find src -type f -name '*.o' -exec rm {} +)


##
# Submodule related tasks
##
.PHONY: math-revert
math-revert:
	git submodule update --init --recursive

.PHONY: math-update
math-update:
	git submodule init
	git submodule update --recursive

math-update/%: math-update
	cd $(MATH) && git fetch --all && git checkout $* && git pull

##
# Debug target that allows you to print a variable
##
print-%  : ; @echo $* = $($*)
