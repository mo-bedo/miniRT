# Set print to true to print full commands
PRINT		=	false
# Source files directory
SRC_DIR		= 	srcs/
# Object files directory
OBJ_DIR		= 	objs/
# Include files directory
INC_DIR		= 	incs/
# Program name
NAME		= 	minirt
# Source files
SRCS		=	main.c
# Compiler
CC			= 	gcc
# Compiler flags
CFLAGS		+= 	-fsanitize=undefined -fsanitize=address -Wall -Wextra -Werror
CFLAGS		+= 	-I$(INC_DIR) -Imlx

# Generate source files with directory and object files
SRCS		:=	$(foreach file,$(SRCS),$(SRC_DIR)$(file))
OBJS		=	$(SRCS:$(SRC_DIR)%=$(OBJ_DIR)%.o)
RM			=	/bin/rm -rf

# Recipes
all: $(NAME)

$(OBJ_DIR):
	@mkdir $@

$(OBJS): | $(OBJ_DIR)

$(OBJS): $(OBJ_DIR)%.o: $(SRC_DIR)%
ifeq ($(PRINT), true)
	$(CC) $(CFLAGS) -c $< -o $@
else
	@echo "Compiling $^: "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "✓"
endif

$(NAME): $(OBJS)
ifeq ($(PRINT), true)
	$(CC) $(CFLAGS) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@
else
	@echo "Assembling $(NAME)"
	@$(CC) $(CFLAGS) $^ -o $@
endif

clean:
ifeq ($(PRINT), true)
	$(RM) $(OBJ_DIR)
else
	@echo "Clean called"
	@$(RM) $(OBJ_DIR)
endif

fclean: clean
ifeq ($(PRINT), true)
	$(RM) $(NAME)
else
	@echo "Fclean called!"
	@$(RM) $(NAME)
endif

re: fclean all

test: re
	./$(NAME)

.PHONY: all clean fclean re test
