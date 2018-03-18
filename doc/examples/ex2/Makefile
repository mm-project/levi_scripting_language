
MODULE=ex2
TEST=$(MODULE)
TGT=../bin/$(TEST)
CC=g++
CC_FLAFS=-g -static-libstdc++ -std=gnu++0x
#FIXME fullpath

INCS:=-I ../../../include
LIB_PATH:=../../../lib
#LIBS:=$(LIB_PATH)/liblevi_interp.so
LIBS:=-llevi_interp


SRCS:=$(wildcard *.cpp)
OBJS:=$(SRCS:.cpp=.o)

%.o : %.cpp
		$(CC) $(CC_FLAFS) $(INCS) $< -c -o $@ 

default: $(OBJS)
		$(CC) $(CC_FLAFS) $^ -L $(LIB_PATH) $(LIBS) -o $(TGT)
		
clean:
	rm -f $(TGT)
	rm -f *.o
	rm -f *.a
