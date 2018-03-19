#MODULES := levi parser vm
YIELD_DIR=.tmp/objroot
LIBS := $(YIELD_DIR)/interp/libinterp.a $(YIELD_DIR)/parser/libparser.a $(YIELD_DIR)/vm/libvm.a   
CC=g++
CC_FLAFS+= -g -static-libstdc++ -std=gnu++0x
TGT=bin/leviInterp
TGT2=bin/leviVM

deafult: levi integ

init:
	mkdir -p $(YIELD_DIR)
	mkdir -p bin
	mkdir -p lib

deps:
	./bsys/utils/createIncludeDir.sh

levi: $(LIBS) integ
	$(CC) $(CC_FLAFS) $(YIELD_DIR)/interp/libinterp.a $(YIELD_DIR)/parser/libparser.a  -o $(TGT)
	$(CC) $(CC_FLAFS) $(YIELD_DIR)/vm/libvm.a -o $(TGT2)
	

integ:
	#cp $(YIELD_DIR)/levi/libparser.a lib/
	cd src/integ; make; cd -
	#cp $(YIELD_DIR)/levi/liblevi.a lib/


$(YIELD_DIR)/interp/libinterp.a: 
	cd src/interp; make; cd -
	
$(YIELD_DIR)/parser/libparser.a: 
	cd src/parser; make; cd -
	cp $(YIELD_DIR)/parser/libparser.a lib/
	
$(YIELD_DIR)/vm/libvm.a: 
	cd src/vm; make; cd -

	
clean:
	rm -rf $(YIELD_DIR)
	rm -f $(TGT)
	rm -rf lib/*
	rm -rf include
	rm -f test/unit/tests/*
	rm -f `find -name "*.o"`
	rm -f `find -name "*.a"`
	
unit_tests:
	mkdir -p test/unit/tests
	cd src/parser; make unit_test; cd -
	cd src/vm; make unit_test; cd -
	cd src/integ; make unit_test; cd -
	
examples:
	cd doc/examples; make ; cd -
	
	
rebuild: clean init deps levi unit_tests examples

