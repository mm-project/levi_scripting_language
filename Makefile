CFLAGS += -fprofile-arcs -ftest-coverage -g -std=gnu++0x -static-libstdc++ #-Wall

coverage:  init objroot/value.o objroot/stmt.o objroot/expr.o objroot/scanner.o objroot/parser.o objroot/interpreter.o objroot/environment.o objroot/main.o
	g++ $(CFLAGS) objroot/value.o objroot/stmt.o objroot/expr.o objroot/scanner.o objroot/parser.o objroot/interpreter.o objroot/environment.o objroot/main.o -o bin/levi 
	
default: init objroot/value.o objroot/stmt.o objroot/expr.o objroot/scanner.o objroot/parser.o objroot/interpreter.o objroot/environment.o objroot/main.o
	g++ $(CFLAGS) objroot/value.o objroot/stmt.o objroot/expr.o objroot/scanner.o objroot/parser.o objroot/interpreter.o objroot/environment.o objroot/main.o -o bin/levi 

objroot/value.o: src/value.hpp src/value.cpp
	g++ src/value.cpp -c $(CFLAGS) -o objroot/value.o

objroot/expr.o: src/expr.cpp src/expr.hpp src/interpreter.hpp src/token.hpp src/value.hpp src/visitor_interface.hpp
	g++ src/expr.cpp -c $(CFLAGS) -o objroot/expr.o

objroot/stmt.o: src/stmt.cpp src/stmt.hpp src/visitor_interface.hpp src/token.hpp
	g++ src/stmt.cpp -c $(CFLAGS) -o objroot/stmt.o

objroot/scanner.o: src/scanner.cpp src/scanner.hpp src/token.hpp
	g++ src/scanner.cpp -c $(CFLAGS) -o objroot/scanner.o

objroot/parser.o: src/parser.cpp src/parser.hpp src/value.hpp src/error.hpp src/token.hpp src/expr.hpp src/stmt.hpp
	g++ src/parser.cpp -c $(CFLAGS) -o objroot/parser.o

objroot/environment.o: src/environment.cpp src/environment.hpp src/error.hpp src/value.hpp src/token.hpp 
	g++ src/environment.cpp -c $(CFLAGS) -o objroot/environment.o

objroot/interpreter.o: src/interpreter.cpp src/interpreter.hpp src/environment.hpp src/expr.hpp src/error.hpp src/stmt.hpp src/visitor_interface.hpp src/value.hpp src/token.hpp
	g++ src/interpreter.cpp -c $(CFLAGS) -o objroot/interpreter.o

objroot/main.o: src/main.cpp src/scanner.hpp src/parser.hpp src/interpreter.hpp
	g++ src/main.cpp -c $(CFLAGS) -o objroot/main.o

clean: 
	rm -f objroot/* 
	rm -f bin/*	
	
init:
	mkdir -p objroot
	mkdir -p bin
	

	
