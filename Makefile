# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweitenb <mweitenb@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/21 13:09:25 by mweitenb      #+#    #+#                  #
#    Updated: 2022/09/21 16:03:35 by mweitenb      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# linux or macos
LINUX = true

# VARIABLES
NAME			:=	miniRT

ifeq ($(LINUX), true)
CFLAGS 			:= -g -Iincs -I/usr/include -Imlx_linux -O3 #-Wall -Wextra -Werror
MLX				:= -g -Iincs -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
CFLAGS			:= 	-g -Iincs -Imlx #-Wall -Wextra -Werror
MLX				:=	-Iincs -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

SANIT			:=	-fsanitize=address -fsanitize=undefined
CC				:=	gcc
PRINT			:=	#@

# STATIC
RM				:=	rm
MKDIR_P			:=	mkdir -p
INC_DIR			:=	./incs
SRC_DIR			:=	./srcs
OBJ_DIR			:=	./objs
SRC				:=	camera.c \
					image_plane.c \
					intersect.c \
					main.c \
					ray_trace.c \
					shape.c \
					utils.c \
					vector_math.c

#					parse_input.c \

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

.PHONY			:	all bonus clean fclean re norm test linux_obj linux

