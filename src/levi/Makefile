CC=g++
CC_FLAFS=-g

#FIXME fullpath
#INCS:=../../include/
INCS:=../ ../parser

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
AR=ar

%.o : %.cpp
		$(CC) $< $(CC_FLAFS) -I $(INCS) -c -o $@ 

default: $(OBJS)
		$(AR) rcs ../../.objroot/levi/liblevi.a $^  