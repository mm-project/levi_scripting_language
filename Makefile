LIBS := objroot/levi/liblevi.a objroot/parser/libparser.a objroot/vm/libvm.a


deafult: levi

levi: init $(LIBS)
	$(CC) $(LIBS) -o bin/$@ 

init:
	mkdir -p .deps/levi
	mkdir -p .deps/parser
	mkdir -p .deps/vm
	
	mkdir -p .objroot/levi
	mkdir -p .objroot/parser
	mkdir -p .objroot/vm

objroot/levi/liblevi.a: 
	cd src/levi; make; cd -
	
objroot/parser/libparser.a: 
	cd src/parser; make; cd -
	
objroot/vm/libvm.a: 
	cd src/vm; make; cd -