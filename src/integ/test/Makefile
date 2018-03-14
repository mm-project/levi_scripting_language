
MODULE=integ
TEST=$(MODULE)Test
TGT=../../../test/unit/tests/$(TEST)
CC=g++
CC_FLAFS=-g -fPIC -static-libstdc++ -std=gnu++0x
#FIXME fullpath

INCS:=-I../../../ext/catch-2.1.2 -I ../ -I ../../
#FIXME insteaad use shared library
LIB_PATH:=../../../lib
LIBS:=$(LIB_PATH)/liblevi_interp.so
#LIBS:=-llevi_interp


SRCS:=$(wildcard *.cpp)
OBJS:=$(SRCS:.cpp=.o)

#%.o : %.cpp
		#$(CC) $(CC_FLAFS) $(INCS) $< -c -o $@ 

#default: $(OBJS)
		#$(CC) $(CC_FLAFS) $^ -L $(LIB_PATH) $(LIBS) -o $(TGT)

default: 
		$(CC) $(CC_FLAFS) $(INCS) test.cpp -L $(LIB_PATH) $(LIBS) -o $(TGT)
		
clean:
	rm -f $(TGT)
	rm -f *.o
	rm -f *.a
