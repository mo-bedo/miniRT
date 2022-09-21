# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweitenb <mweitenb@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/21 13:09:25 by mweitenb      #+#    #+#                  #
#    Updated: 2022/09/21 13:10:38 by mweitenb      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# VARIABLES
NAME			:=	miniRT
CFLAGS			:= 	-Wall -Wextra -Werror -I$(INC_DIR) -Imlx
MLX				:=	-Lmlx -lmlx -framework OpenGL -framework AppKit
SANIT			:=	-fsanitize=address -fsanitize=undefined
CC				:=	gcc
PRINT			:=	@

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
					$(PRINT)$(CC) $(OBJ) $(MLX) -o $@ $(SANIT)

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c $(INC_DIR)/%.h
					$(PRINT)$(MKDIR_P) $(dir $@)
					$(PRINT)$(CC) $(CFLAGS) $(SANIT) -c $< -o $@

clean			: 
					$(PRINT)$(RM) -rf $(OBJ_DIR)

fclean			:	clean
					$(PRINT)$(RM) -f $(NAME)

re				: 	fclean all

test			:	re
					./$(NAME)

norm			:
					@norminette $(SRC_DIR) $(INC_DIR)

.PHONY			:	all bonus clean fclean re norm test

