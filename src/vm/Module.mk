MODULE:=vm

MODULE_OBJ_ROOT:=$(OBJ_ROOT)/$(MODULE)
MODULE_CODE_DIR:=$(CODE_BASE_DIR)/$(MODULE)
CPPS:=$(wildcard src/$(MODULE)/*.cpp)
OBJS1:=$(CPPS:.cpp=.o)
MODULE_OBJS:=$(patsubst src/%,$(OBJ_ROOT)/%,$(OBJS1))
MODULE_DEPS:=$(MODULE_OBJS:.o=.d)

LOCAL_CC_FLAG:=$(CC_FLAFS) -lpthread
LOCAL_INCS:=$(INCLS)

include $(RULES_DIR)/static_library.rl
