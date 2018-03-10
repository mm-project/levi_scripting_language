
CC=g++
CC_FLAFS=-g
#FIXME fullpath
INCS:=../../../ext/catch-2.1.2
SRCS:=$(wildcard *.cpp)
OBJS:=$(SRCS:.cpp=.o)

%.o : %.cpp
		$(CC) $< $(CC_FLAFS) -I $(INCS) -c -o $@ 

default: $(OBJS)
		$(CC) $(CC_FLAFS) $^ -o hopar.exe