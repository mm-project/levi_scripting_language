#MODULES := levi parser vm

YIELD_DIR=.tmp/objroot
LIBS := $(YIELD_DIR)/levi/liblevi.a $(YIELD_DIR)/parser/libparser.a $(YIELD_DIR)/vm/libvm.a  $(YIELD_DIR)/bytecode/libbytecode.a
CC=g++
CC_FLAFS+=-g -static-libstdc++ 
TGT=bin/levi

deafult: init levi

init:
	mkdir -p $(YIELD_DIR)
	mkdir -p bin

levi: $(LIBS)
	$(CC) $(CC_FLAFS) $(LIBS) -o $(TGT)


$(YIELD_DIR)/levi/liblevi.a: 
	cd src/levi; make; cd -
	
$(YIELD_DIR)/parser/libparser.a: 
	cd src/parser; make; cd -
	
$(YIELD_DIR)/vm/libvm.a: 
	cd src/vm; make; cd -

$(YIELD_DIR)/bytecode/libbytecode.a: 
	cd src/bytecode; make; cd -
	
clean:
	rm -rf $(YIELD_DIR)
	rm -f $(TGT)
	rm -f test/unit/tests/*
	rm -f `find -name "*.o"`
	rm -f `find -name "*.a"`
	
unit_test:
	mkdir -p test/unit/tests
	cd src/parser; make unit_test; cd -
	cd src/vm; make unit_test; cd -
	cd src/bytecode; make unit_test; cd -
	
rebuild: clean init levi unit_test