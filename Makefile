# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: marvin <marvin@student.42.fr>                +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/21 13:09:25 by mweitenb      #+#    #+#                  #
#    Updated: 2022/09/29 19:39:19 by mweitenb      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# linux or macos
LINUX = false

# VARIABLES
NAME			:=	miniRT

ifeq ($(LINUX), true)
CFLAGS 			:= -g -Iinc -I/usr/include -Imlx_linux -O3 -Wall -Wextra -Werror
MLX				:= -g -Iinc -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
CFLAGS			:= 	-g -Iinc -Imlx -Wall -Wextra -Werror
MLX				:=	-Iinc -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

SANIT			:=	-fsanitize=address -fsanitize=undefined
CC				:=	gcc
PRINT			:=

# STATIC
RM				:=	rm
MKDIR_P			:=	mkdir -p
INC_DIR			:=	./inc
SRC_DIR			:=	./src
OBJ_DIR			:=	./obj

SRC				:=	intersection/i_.c \
					intersection/i_plane.c \
					intersection/i_sphere.c \
					parse_scene/ps_.c \
					parse_scene/ps_parse_line.c \
					parse_scene/ps_utils.c \
					utils/utils_conversion.c \
					utils/utils.c \
					utils/vector_math.c \
					main.c \
					ray_trace.c \
					lighting.c \
					interaction.c \
					pixel_put.c
#<<<<<<< HEAD
#					plane.c \
#					sphere.c
#=======
#>>>>>>> master

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
					./$(NAME) scenes/gambetta.rt

norm			:
					@norminette $(SRC_DIR) $(INC_DIR)

.PHONY			:	all bonus clean fclean re norm test

