MODULE=vm
ODIR=../../.tmp/objroot/$(MODULE)
#TGT=$(ODIR)/lib$(MODULE).a
TGT=lib$(MODULE).a
CC=g++
CC_FLAFS+=-g -static-libstdc++ -std=gnu++0x

#FIXME fullpath
INCS:=-I ../ -I ../$(MODULE)

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
AR=ar

%.o : %.cpp
	$(CC) $< $(CC_FLAFS) $(INCS) -c -o $(ODIR)/$@ 

default: init install 

init:
		mkdir -p $(ODIR)
		
install: $(OBJS)
		cd $(ODIR); $(AR) rcs $(TGT) $^  

		
clean:
	rm -f $(TGT)
	rm -f $(ODIR)/*.o
	rm -f $(ODIR)/*.a
	
	

unit_test:
	cd test; make; cd -
	
rebuild: clean install unit_test