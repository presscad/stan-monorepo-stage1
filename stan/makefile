##
# Stan
# -----------------
#
# To customize your build, set make variables in either:
#    ~/.config/stan/make.local
#    make/local
# Variables in make/local is loaded after ~/.config/stan/make.local
PROJECT_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../)

## 'help' is the default make target.
help:

-include $(HOME)/.config/stan/make.local  # user-defined variables
-include make/local                       # user-defined variables


MATH ?= $(PROJECT_DIR)/math/
ifeq ($(OS),Windows_NT)
  O_STANC ?= 3
endif
O_STANC ?= 0

-include $(MATH)make/compiler_flags
-include $(MATH)make/dependencies
-include $(MATH)make/libraries
include make/libstanc                     # bin/libstanc.a
include make/doxygen                      # doxygen
include make/cpplint                      # cpplint
include make/tests                        # tests

INC_FIRST = -I $(if $(STAN),$(STAN)/src,src)
LDLIBS_STANC ?= -Ltest -lstanc


.PHONY: help
help:
	@echo '--------------------------------------------------------------------------------'
	@echo 'Note: testing of Stan is typically done with the `runTests.py` python script.'
	@echo '  See https://github.com/stan-dev/stan/wiki/Testing-Stan-using-Gnu-Make-and-Python'
	@echo '  for more detail on testing.'
	@echo ''
	@echo 'Stan makefile:'
	@$(MAKE) print-compiler-flags
	@echo '  - O_STANC (Opt for stanc):    ' $(O_STANC)
	@echo ''
	@echo 'Common targets:'
	@echo '  Documentation:'
	@echo '  - doxygen        : Builds the API documentation. The documentation is located'
	@echo '                     doc/api/'
	@echo '                     (requires doxygen installation)'
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
	@echo '  - clean-deps    : Removes dependency files for tests. If tests stop building,'
	@echo '                    run this target.'
	@echo '  - clean-all     : Cleans up all of Stan.'
	@echo ''
	@echo '--------------------------------------------------------------------------------'

##
# Clean up.
##
MODEL_SPECS := $(shell find src/test -type f -name '*.stan')
.PHONY: clean clean-demo clean-dox clean-models clean-all clean-deps
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

clean-all: clean clean-dox clean-deps clean-libraries
	$(RM) -r test bin
	@echo '  removing .o files'
	$(shell find src -type f -name '*.o' -exec rm {} +)

##
# Debug target that allows you to print a variable
##
print-%  : ; @echo $* = $($*)
