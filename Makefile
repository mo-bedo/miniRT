# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 13:09:25 by mweitenb          #+#    #+#              #
#    Updated: 2022/09/23 17:50:03 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLES
NAME			:=	miniRT
CFLAGS			:= 	-g -Iincs -Imlx #-Wall -Wextra -Werror
MLX				:=	-Iincs -Lmlx -lmlx -framework OpenGL -framework AppKit
SANIT			:=	-fsanitize=address -fsanitize=undefined
CC				:=	gcc 
PRINT			:=	@

# STATIC
RM				:=	rm
MKDIR_P			:=	mkdir -p
INC_DIR			:=	./inc
SRC_DIR			:=	./src
OBJ_DIR			:=	./obj
SRC				:=	parse_scene/parse_scene.c \
					parse_scene/parse_scene_utils.c \
					camera.c \
					image_plane.c \
					intersect.c \
					main.c \
					ray_trace.c \
					shape.c \
					utils.c \
					vector_math.c

OBJ				:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

all				:	$(NAME)

$(NAME)			: 	$(OBJ)
					$(PRINT)$(CC) $(OBJ) $(MLX) -o $@ $(SANIT) -lm

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

