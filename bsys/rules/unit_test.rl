TEST_NAME:=$(MODULE)Test
TEST_TARGET:=$(UNITTEST_BIN_DIR)/$(TEST_NAME)
TEST_OBJ_ROOT:=$(OBJ_ROOT)/$(MODULE)/test
TEST_CODE_DIR:=$(CODE_BASE_DIR)/$(MODULE)/test
CPPS:=$(wildcard $(TEST_CODE_DIR)/*.cpp)
OBJS1:=$(CPPS:.cpp=.o)
TEST_OBJS:=$(patsubst $(TEST_CODE_DIR)/%,$(OBJ_ROOT)/$(MODULE)/test/%,$(OBJS1))
TEST_DEPS:=$(TEST_OBJS:.o=.d)

TEST_LOCAL_CC_FLAG:=$(CC_FLAFS) 
TEST_LOCAL_INCS:=$(LOCAL_INCS) -I ./ext/catch-2.1.2
TEST_LOCAL_LIB:=$(LOCAL_LIBS)


$(shell mkdir -p $(OBJ_ROOT)/$(MODULE)/test)
$(shell mkdir -p $(UNITTEST_BIN_DIR))

	
$(TEST_NAME):  $(TEST_TARGET) 

	
$(TEST_TARGET): $(TEST_OBJS) 
	$(CC) $^ $(TEST_LOCAL_LIB) -o $@ 

-include $(TEST_DEPS)

$(TEST_OBJ_ROOT)/%.o: $(TEST_CODE_DIR)/%.cpp
	$(CC) -c $< $(TEST_LOCAL_CC_FLAG) $(TEST_LOCAL_INCS) -o $@ 
		
$(TEST_OBJ_ROOT)/%.d: $(TEST_CODE_DIR)/%.cpp 
	$(CC) $<  $(TEST_LOCAL_CC_FLAG) $(TEST_LOCAL_INCS)  -MM -MT $(@:.d=.o) > $@

