AR=ar
CC=g++
RULES_DIR:=./bsys/rules

TMP_DIR:=.tmp
OBJ_ROOT:=$(TMP_DIR)/objroot
CODE_BASE_DIR:=src
TARGET_PREFIX:=lib_levi_
INCLS:=-I ./include
CC_FLAFS+=-g -fPIC -std=gnu++0x -static-libstdc++ $(INCLS)

#include $(RULES_DIR)/common.rl

#deps:
	#./bsys/utils/createIncludeDir.sh
	
default: init ./lib/libLeviInterp.so ./bin/leviInterp ./bin/leviVM

#MOVE to module.mk
init:
	mkdir -p $(OBJ_ROOT)
	mkdir -p bin
	mkdir -p lib

./lib/libLeviInterp.so: $(OBJ_ROOT)/parser/lib_levi_parser.a 
	$(CC) $^ -fPIC -shared -o $@

./bin/leviInterp: $(OBJ_ROOT)/interp/lib_levi_interp.a $(OBJ_ROOT)/parser/lib_levi_parser.a 
	$(CC) $^ -o $@

./bin/leviVM:  $(OBJ_ROOT)/vm/lib_levi_vm.a 
	$(CC) $^ -o $@
	

#Make all the modules as static library
MODULES:=parser interp vm
include $(patsubst %,src/%/Module.mk,$(MODULES))




