AR=ar
CC=g++

RULES_DIR:=./bsys/rules



ROOT_DIR:=.
TMP_DIR:=$(ROOT_DIR)/.tmp
OBJ_ROOT:=$(TMP_DIR)/objroot
BIN_DIR:=$(ROOT_DIR)/bin
LIB_DIR:=$(ROOT_DIR)/lib
EXAMPLES_DIR:=$(ROOT_DIR)/doc/examples
EXAMPLES_BIN_DIR:=$(EXAMPLES_DIR)/bin
EXAMPLES_LIB_DIR:=$(EXAMPLES_DIR)/lib
UNITTEST_BIN_DIR:=$(ROOT_DIR)/test/unit/tests

INC_DIR:=$(ROOT_DIR)/include

CODE_BASE_DIR:=$(ROOT_DIR)/src
TARGET_PREFIX_NAME:=lib_levi_
TARGET_POSTFIX_NAME:=.a

#FIXME!!!
$(shell mkdir -p $(OBJ_ROOT))
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(LIB_DIR))
$(shell mkdir -p $(EXAMPLES_BIN_DIR))


INCLS:=-I $(INC_DIR)
CC_FLAFS+=-g -std=gnu++0x 
#CC_FLAFS+=-g -fPIC -std=gnu++0x 
LD_FLAFS+=-static-libstdc++