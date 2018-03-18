MODULE=levi_interp
ODIR=../../.tmp/objroot/$(MODULE)
#TGT=$(ODIR)/lib$(MODULE).a
TGT=lib$(MODULE).so
CC=g++
CC_FLAFS+=-g   -fPIC -static-libstdc++  -std=gnu++0x

#FIXME fullpath
#INCS:=-I ../ -I ../../ -I ../$(MODULE)
INCS:=-I ../../include 
LIB_PATH:=../../lib
LIBS:=$(LIB_PATH)/libparser.a


SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
AR=ar

%.o : %.cpp
	$(CC) $< $(CC_FLAFS) $(INCS) -c -o $(ODIR)/$@ 

default: init install 

init:
		mkdir -p $(ODIR)
		
#FIXME , will not compile if many cpp/object files		
install: $(OBJS)
		$(CC) $(CC_FLAFS) $(ODIR)/$^ $(LIBS)  -fPIC -shared -o $(LIB_PATH)/$(TGT)

		
clean:
	rm -f $(TGT)
	rm -f $(ODIR)/*.o
	rm -f $(ODIR)/*.a
	
unit_test:
	cd test; make; cd -
	
rebuild: clean install 