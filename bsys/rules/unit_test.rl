
TARGET_NAME:=$(TARGET_PREFIX_NAME)$(MODULE)$(TARGET_POSTFIX_NAME)
TARGET:=$(MODULE_OBJ_ROOT)/$(TARGET_NAME)


#FIXME		
$(shell mkdir -p $(OBJ_ROOT)/$(MODULE)/test)

		
$(TARGET): $(MODULE_OBJS) 
	$(CC) $@  -o $^  

-include $(MODULE_DEPS)


$(MODULE_OBJ_ROOT)/%.o: $(MODULE_CODE_DIR)/%.cpp
	$(CC) -c $< $(LOCAL_CC_FLAG) $(LOCAL_INCS) -o $@ 
		
#FIXME		
$(MODULE_OBJ_ROOT)/%.d: $(MODULE_CODE_DIR)/%.cpp 
	$(CC) $(LOCAL_CC_FLAG) $(LOCAL_INCS) $<  -MM -MT $(@:.d=.o) > $@



