# VARIABLES
CC						=	@gcc -lm -DUNITY_INCLUDE_DOUBLE -DUNITY_DOUBLE_PRECISION=0.001f
CFLAGS					:= 	-Iinc -I../inc -Imlx -Wall -Wextra -Werror
MLX						:=	#-Iinc -Lmlx -lmlx -framework OpenGL -framework AppKit
SANIT					:=	-fsanitize=address -fsanitize=undefined
PRINT					:=	@

# STATIC
TEST_FILES 				=	unity/src/unity.c \
							unity/extras/fixture/src/unity_fixture.c \
							$(shell find ./test -name *.c)
TESTEXE					=	test_exec
UNITY_CONFIG_DEFINES	= 	-D UNITY_OUTPUT_COLOR \
							-D UNITY_FIXTURE_NO_EXTRAS
UNITY_INCL 				=	-I./unity/src/ \
							-I./unity/extras/fixture/src \
							-I../inc/
TEST_OBJ_DIR 			=	test_obj
TEST_OBJ_FILES			=	$(TEST_FILES:%.c=$(TEST_OBJ_DIR)/%.o)
SRC_DIR					=	../src
SRC_FILES				:=	$(shell find $(SRC_DIR) -name *.c)
SRC_FILES 				:=	$(filter-out $(SRC_DIR)/main.c, $(SRC_FILES))
OBJ						=	$(SRC_FILES:%=$(TEST_OBJ_DIR)/%.o)

$(TESTEXE)				:	$(TEST_OBJ_FILES) $(OBJ)
							$(CC) $(CFLAGS) $^ -o $@ -lm
$(TEST_OBJ_DIR)			:
							$(PRINT)mkdir -p $@
$(OBJ)					:	$(TEST_OBJ_DIR)/%.c.o : %.c
							$(PRINT)mkdir -p $(@D)
							$(CC) $(CFLAGS) -c $< -o $@ 
$(TEST_OBJ_FILES)		:	$(TEST_OBJ_DIR)/%.o : %.c
							$(PRINT)mkdir -p $(@D)
							$(CC) $(CFLAGS) $(UNITY_CONFIG_DEFINES) $(UNITY_INCL) -c $< -o $@ 

.PHONY					=	test clean fclean re
test					:	$(TEST_OBJ_DIR) $(TESTEXE)
test_run				:	test
							$(PRINT)./$(TESTEXE) -v
clean					:
							$(PRINT)rm -rf $(TEST_OBJ_DIR)
							$(PRINT)rm -rf src
fclean					: 	clean
							$(PRINT)touch a b c exp_1.txt exp_3.txt exp_2.txt our_1.txt our_3.txt our_2.txt
							$(PRINT)@rm a b c exp_*.txt our_*.txt
							$(PRINT)@rm -f $(TESTEXE)
re						:	fclean test_run