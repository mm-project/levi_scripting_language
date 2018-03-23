
TEST=vmTest
TGT=../../../test/unit/tests/$(TEST)
CC=g++
CC_FLAFS=-g -static-libstdc++ -std=gnu++0x
#FIXME fullpath

INCS:=-I../../../ext/catch-2.1.2 -I ../../

SRCS:=$(wildcard *.cpp)
OBJS:=$(SRCS:.cpp=.o)

%.o : %.cpp
		$(CC) $< $(CC_FLAFS) $(INCS) -c -o $@ 

default: $(OBJS)
		$(CC) $(CC_FLAFS) $^ -o $(TGT)
		
clean:
	rm -f $(TGT)
	rm -f *.o
	rm -f *.a

	
unit_test:
	cd test; make; cd -
	
rebuild: clean install unit_test