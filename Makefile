include bsys/rules/common.rl


#all: ./lib/libLeviInterp.so ./bin/leviInterp ./bin/leviVM
	
#fimxe first target should be object file for shared library
#or give other rule for shared library	
./lib/libLeviInterp.so: $(OBJ_ROOT)/integ/lib_levi_integ.a $(OBJ_ROOT)/parser/lib_levi_parser.a 
	$(CC) $(OBJ_ROOT)/integ/levi_interp.o $^ $(LD_FLAFS) -fPIC -shared -o $@

./bin/leviInterp: $(OBJ_ROOT)/interp/lib_levi_interp.a $(OBJ_ROOT)/parser/lib_levi_parser.a 
	$(CC) $^ $(LD_FLAFS) -o $@

./bin/leviVM:  $(OBJ_ROOT)/vm/lib_levi_vm.a 
	$(CC) $^ $(LD_FLAFS) -o $@


.PHONY: init
init:
	mkdir -p $(OBJ_ROOT)
	mkdir -p $(BIN_DIR)
	mkdir -p $(LIB_DIR)

	
.PHONY: examples	
examples:
	$(MAKE) -C $(EXAMPLES_DIR)
	
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


.PHONY: rebuild
rebuild: clean init deps all unit_tests examples

#Make all the modules as static library	
MODULES:=integ parser vm interp
TESTS:=$(patsubst %,%Test,$(MODULES))
include $(patsubst %,src/%/Module.mk,$(MODULES))

#FIXME
#TOTESTS:=parser vm integ interp
#TESTS:=$(patsubst %,%Test,$(TOTESTS))
.PHONY: unit_tests
unit_tests: $(TESTS)


	
