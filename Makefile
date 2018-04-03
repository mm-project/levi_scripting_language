CC_FLAFS+=-g -std=gnu++0x 
INCLS:=-I ./include

include bsys/rules/common.rl

all: ./lib/libLeviInterp.so ./bin/leviInterp ./bin/leviVM
	
	
./lib/libLeviInterp.so: $(OBJ_ROOT)/parser/lib_levi_parser.a 
	$(CC) $^ -fPIC -shared -o $@

./bin/leviInterp: $(OBJ_ROOT)/interp/lib_levi_interp.a $(OBJ_ROOT)/parser/lib_levi_parser.a 
	$(CC) $^ -o $@

./bin/leviVM:  $(OBJ_ROOT)/vm/lib_levi_vm.a 
	$(CC) $^ -o $@



#.PHONY: init
#init:
#	mkdir -p $(OBJ_ROOT)
#	mkdir -p $(BIN_DIR)
#	mkdir -p $(LIB_DIR)
#	mkdir -p $(EXAMPLES_BIN_DIR)

#Make all the modules as static library	
MODULES:= interp parser vm
include $(patsubst %,src/%/Module.mk,$(MODULES))

	
PHONY: deps
deps:
	./bsys/utils/createIncludeDir.sh
	

PHONY: clean
clean:
	rm -rf $(TMP_DIR)
	rm -f $(BIN_DIR)
	rm -f $(LIB_DIR)
	rm -f $(EXAMPLES_BIN_DIR)
	rm -f $(EXAMPLES_BIN_DIR)
	rm -rf doc/examples/bin
	rm -rf lib/*
	rm -rf include
	rm -f test/unit/tests/*
	rm -f `find -name "*.o"`
	rm -f `find -name "*.a"`

PHONY: unit_tests
unit_tests:
	#mkdir -p test/unit/tests
	#make src/parser/test;
	
PHONY: examples	
#examples:
	#mkdir -p test/unit/tests
	#make src/parser/test;

rebuild: clean init deps all unit_tests examples




