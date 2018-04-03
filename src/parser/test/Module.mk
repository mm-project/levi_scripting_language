TEST_NAME:=$(MODULE)Test
TEST_TARGET:=$(UNITTEST_BIN_DIR)/$(TEST_NAME)
TEST_OBJ_ROOT:=$(OBJ_ROOT)/$(MODULE)/test
TEST_CODE_DIR:=$(CODE_BASE_DIR)/$(MODULE)/test
CPPS:=$(wildcard $(TEST_CODE_DIR)/*.cpp)
OBJS1:=$(CPPS:.cpp=.o)
TEST_OBJS:=$(patsubst $(TEST_CODE_DIR)/%,$(OBJ_ROOT)/$(MODULE)/test/%,$(OBJS1))
TEST_DEPS:=$(TEST_OBJS:.o=.d)

TEST_LOCAL_CC_FLAG:=$(CC_FLAFS) 
TEST_LOCAL_INCS:=-I ./src -I ./ext/catch-2.1.2
TEST_LOCAL_LIB:=$(LIBS)


$(shell mkdir -p $(OBJ_ROOT)/$(MODULE)/test)
$(shell mkdir -p $(UNITTEST_BIN_DIR))

	
$(TEST_NAME):  $(TEST_TARGET) 
	@echo $(TEST_TARGET)
	@echo $(TEST_OBJS) 
	@echo $(TEST_NAME)
	@echo TEST_TARGET $(TEST_TARGET)
	@echo TEST_OBJ_ROOT $(TEST_OBJ_ROOT)
	@echo TEST_CODE_DIR $(TEST_CODE_DIR)
	@echo CPPS $(CPPS)
	@echo OBJS1 $(OBJS1)
	@echo TEST_OBJS $(TEST_OBJS)
	@echo TEST_DEPS $(TEST_DEPS)
	
$(TEST_TARGET): $(TEST_OBJS) 
	@echo $(TEST_OBJS)
	$(CC)  $^ -o $@ 

-include $(TEST_DEPS)

$(TEST_OBJ_ROOT)/%.o: $(TEST_CODE_DIR)/%.cpp
	$(CC) -c $< $(TEST_LOCAL_CC_FLAG) $(TEST_LOCAL_INCS) -o $@ 
		
$(TEST_OBJ_ROOT)/%.d: $(TEST_CODE_DIR)/%.cpp 
	$(CC) $(LOCAL_CC_FLAG) $(LOCAL_INCS) $<  -MM -MT $(@:.d=.o) > $@

