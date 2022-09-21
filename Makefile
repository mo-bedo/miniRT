# Set print to true to print full commands
# PRINT		=	true


# VARIABLES
NAME			:=	miniRT
CFLAGS			:= 	-Wall -Wextra -Werror -I$(INC_DIR) -Imlx
MLX				:=	-Lmlx -lmlx -framework OpenGL -framework AppKit
SANIT			:=	-fsanitize=address -fsanitize=undefined
CC				:=	gcc

# STATIC
RM				:=	rm
MKDIR_P			:=	mkdir -p
INC_DIR			:=	./incs
SRC_DIR			:=	./srcs
OBJ_DIR			:=	./objs
SRC				:=	main.c

OBJ				:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

all				:	$(NAME)

$(NAME)			: 	$(OBJ)
					$(CC) $(OBJ) $(MLX) -o $@ $(SANIT)

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c $(INC_DIR)/%.h
					$(MKDIR_P) $(dir $@)
					$(CC) $(CFLAGS) $(SANIT) -c $< -o $@

clean			:
					$(RM) -rf $(OBJ_DIR)

fclean			:	clean
					$(RM) -f $(NAME)

re				: 	fclean all

test			:	re
					./$(NAME)

norm			:
					@norminette $(SRC_DIR) $(INC_DIR)

.PHONY			:	all bonus clean fclean re norm test



# Recipes





# $(NAME): $(OBJS)
#	$(CC) $(CFLAGS) $^ -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@


