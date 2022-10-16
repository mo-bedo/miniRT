# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 13:09:25 by mweitenb          #+#    #+#              #
#    Updated: 2022/10/16 13:27:19 by jbedaux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# linux or macos
LINUX 			=	true

# VARIABLES
NAME			:=	miniRT

# -L geeft aan in welke directory hij zoekt naar lib file. -l specificeert naam van library die hij moet includen
ifeq ($(LINUX), false)
CFLAGS 			:= -g -Iinc -I/usr/include -Imlx_linux #-O3 #-Wall -Wextra -Werror
MLX				:= -g -Iinc -I/usr/include -Imlx_linux -Lmlx_linux -L/usr/lib -lmlx -lXext -lX11 -lm -lz
else
CFLAGS			:= 	-Iinc -Imlx -Wall -Wextra -Werror
MLX				:=	-Iinc -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

SANIT			:=	#-g -fsanitize=undefined -fsanitize=address 
CC				:=	gcc
PRINT			:=	

# STATIC
RM				:=	rm
MKDIR_P			:=	mkdir -p
INC_DIR			:=	./inc
SRC_DIR			:=	./src
OBJ_DIR			:=	./obj

SRC				:=	main.c \
					intersection/i_.c \
					intersection/i_cone.c \
					intersection/i_plane.c \
					intersection/i_sphere.c \
					intersection/i_cylinder.c \
					intersection/i_utils.c \
					parse_scene/ps_.c \
					parse_scene/ps_parse_line.c \
					parse_scene/ps_parse_objects.c \
					parse_scene/ps_parse_textures.c \
					parse_scene/ps_parse_textures_utils.c \
					parse_scene/ps_utils.c \
					ray_trace/rt_.c \
					ray_trace/rt_lighting.c \
					ray_trace/rt_uv_pattern.c \
					ray_trace/rt_uv_map_to_2d.c \
					ray_trace/rt_pixel_put.c \
					utils/u_.c \
					utils/u_conversion.c \
					utils/u_compare.c \
					utils/u_identify.c \
					utils/u_vector_math.c \
					utils/u_vector_operators.c \
					utils/u_rotate_vector.c \
					user_input/ui_.c \
					user_input/ui_mouse_hook.c \
					user_input/ui_adjust_object.c

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
