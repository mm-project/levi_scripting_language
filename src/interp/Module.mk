#mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
#current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
#MODULE+=$(shell basename $(CURDIR))
#FIXME get current dir name ( where this mk file is stored )
MODULE:=interp


OBJ_ROOT1:=.tmp/objroot/$(MODULE)
CODE_DIR:=$(CODE_BASE_DIR)/$(MODULE)

CPPS:=$(wildcard src/$(MODULE)/*.cpp)
#SRCS:=$(patsubst %,src/$(MODULE)/%,$(CPPS))
OBJS1:=$(CPPS:.cpp=.o)
LOCAL_OBJS:=$(patsubst src/%,$(OBJ_ROOT)/%,$(OBJS1))
LOCAL_DEPS:=$(LOCAL_OBJS:.o=.d)
#DEP_TMP:=$(patsubst .tmp/objroot/$(MODULE)/%,%,$(LOCAL_DEPS))



OBJ:=$(LOCAL_OBJS)
SRC:=$(CPPS)
TARGET_NAME:=$(TARGET_PREFIX)$(MODULE).a
TARGET:=$(OBJ_ROOT1)/$(TARGET_NAME)


include $(RULES_DIR)/static_library.rl


#.tmp/objroot/parser/%.o : src/parser/%.cpp
#	$(CC) -c $< $(CC_FLAFS) $(INCS) -o $@ 
	
#.tmp/objroot/parser/lib$(MODULE).a : $(LOCAL_OBJS)
#	$(AR) rcs  $@  $^  


#$(OBJ_ROOT)/$(MODULE)/%.d :  src/parser/%.cpp
	#$(CC) $(CFLAGS) $(CODE_DIR)/$*.cpp -MM -MT $(@:.d=.o) > $@

	
#$(OBJ_ROOT)/$(MODULE)/%.d:
#	bsys/utils/createDependencies.sh src/$(MODULE) $(CC_FLAGS) src/$(MODULE)/$*.cpp > $@


#-include $(LOCAL_DEPS)
#include $(wildcard $(OBJ_ROOT)/$(MODULE)/*.d)


#a: $(LOCAL_OBJS)
#	@echo $(LOCAL_OBJS) $(LOCAL_DEPS)