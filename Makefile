CFLAGS += -g -std= gnu++0x -static-libstdc++ #-Wall

levi: value.o stmt.o expr.o scanner.o parser.o interpreter.o environment.o main.o
	g++ $(CFLAGS) value.o stmt.o expr.o scanner.o parser.o interpreter.o environment.o main.o -o levi

value.o: value.hpp value.cpp
	g++ value.cpp -c $(CFLAGS) 

expr.o: expr.cpp expr.hpp interpreter.hpp token.hpp value.hpp visitor_interface.hpp
	g++ expr.cpp -c $(CFLAGS)

stmt.o: stmt.cpp stmt.hpp visitor_interface.hpp token.hpp
	g++ stmt.cpp -c $(CFLAGS)

scanner.o: scanner.cpp scanner.hpp token.hpp
	g++ scanner.cpp -c $(CFLAGS)

parser.o: parser.cpp parser.hpp value.hpp error.hpp token.hpp expr.hpp stmt.hpp
	g++ parser.cpp -c $(CFLAGS)

environment.o: environment.cpp environment.hpp error.hpp value.hpp token.hpp 
	g++ environment.cpp -c $(CFLAGS)

interpreter.o: interpreter.cpp interpreter.hpp environment.hpp expr.hpp error.hpp stmt.hpp visitor_interface.hpp value.hpp token.hpp
	g++ interpreter.cpp -c $(CFLAGS)

main.o: main.cpp scanner.hpp parser.hpp interpreter.hpp
	g++ main.cpp -c $(CFLAGS)

clean: 
	rm -r main.o interpreter.o environment.o parser.o scanner.o stmt.o expr.o value.o levi	
