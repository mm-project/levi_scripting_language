
TARGET_NAME:=$(TARGET_PREFIX_NAME)$(MODULE)$(TARGET_POSTFIX_NAME)
TARGET:=$(MODULE_OBJ_ROOT)/$(TARGET_NAME)


#default:
#		@echo $(MODULE_OBJ_ROOT)
#		@echo $(MODULE_DEPS)
#		@echo $(MODULE_OBJS) 

#.PHONY: $(MODULE)

#$(MODULE): 
#		mkdir -p $(OBJ_ROOT)/$(MODULE)
		
#FIXME		
$(shell mkdir -p $(OBJ_ROOT)/$(MODULE))

		
$(TARGET): $(MODULE_OBJS) 
	$(AR) rcs  $@  $^  

-include $(MODULE_DEPS)


$(MODULE_OBJ_ROOT)/%.o: $(MODULE_CODE_DIR)/%.cpp
	$(CC) -c $< $(LOCAL_CC_FLAG) $(LOCAL_INCS) -o $@ 
		
#FIXME		
$(MODULE_OBJ_ROOT)/%.d: $(MODULE_CODE_DIR)/%.cpp 
	$(CC) $< $(LOCAL_CC_FLAG) $(LOCAL_INCS)  -MM -MT $(@:.d=.o) > $@


