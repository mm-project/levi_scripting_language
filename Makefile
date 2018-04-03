CC_FLAFS+=-g -std=gnu++0x 
INCLS:=-I $(INC_DIR)

include bsys/rules/common.rl

#all: ./lib/libLeviInterp.so ./bin/leviInterp ./bin/leviVM
	
	
#./lib/libLeviInterp.so: $(OBJ_ROOT)/parser/lib_levi_parser.a 
#	$(CC) $^ -fPIC -shared -o $@

#./bin/leviInterp: $(OBJ_ROOT)/interp/lib_levi_interp.a $(OBJ_ROOT)/parser/lib_levi_parser.a 
#	$(CC) $^ -o $@

#./bin/leviVM:  $(OBJ_ROOT)/vm/lib_levi_vm.a 
#	$(CC) $^ -o $@



#.PHONY: init
#init:
#	mkdir -p $(OBJ_ROOT)
#	mkdir -p $(BIN_DIR)
#	mkdir -p $(LIB_DIR)
#	mkdir -p $(EXAMPLES_BIN_DIR)


#.PHONY: examples	
#examples:
	#mkdir -p test/unit/tests
	#make src/parser/test;

	
.PHONY: deps
deps:
	./bsys/utils/createIncludeDir.sh
	

.PHONY: clean
clean:
	rm -rf $(TMP_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(LIB_DIR)
	rm -rf $(INC_DIR)
	rm -rf $(EXAMPLES_BIN_DIR)
	rm -rf $(UNITTEST_BIN_DIR)
	rm -f `find -name "*.o"`
	rm -f `find -name "*.a"`


#.PHONY: rebuild
#rebuild: clean init deps all unit_tests examples

#Make all the modules as static library	
MODULES:=parser
TESTS:=$(patsubst %,%Test,$(MODULES))
include $(patsubst %,src/%/Module.mk,$(MODULES))
#include $(patsubst %,src/%/test/Module.mk,$(MODULES))

.PHONY: unit_tests
unit_tests: $(TESTS)
	#@echo $(TESTS)
	#@echo $(patsubst %,src/%/test/Module.mk,$(MODULES))

	




