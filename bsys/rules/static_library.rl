
	
$(OBJ_ROOT1)/%.o: $(CODE_DIR)/%.cpp
	$(CC) -c $< $(CC_FLAFS) $(INCS) -o $@ 
	
$(TARGET): $(OBJ) 
	$(AR) rcs  $@  $^  


