# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbedaux <jbedaux@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/21 13:09:25 by mweitenb      #+#    #+#                  #
#    Updated: 2022/11/11 13:04:40 by mweitenb      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# linux or macos
LINUX 			=	false

# VARIABLES
NAME			:=	miniRT
NAME_BONUS		:=	miniRT_bonus

# -L geeft aan in welke directory hij zoekt naar lib file. -l specificeert naam van library die hij moet includen
ifeq ($(LINUX), true)
CFLAGS 			:=  -Iinc -Iinc_bonus -I/usr/include -Imlx_linux -O3 -Wall -Wextra -Werror 
MLX				:= -Iinc -Iinc_bonus -I/usr/include -Imlx_linux -Lmlx_linux -L/usr/lib -lmlx -lXext -lX11 -lm -lz 
else
CFLAGS			:= 	-Iinc -Iinc_bonus -Imlx -O3 -Wall -Wextra -Werror
MLX				:=	-Iinc -Iincbonus -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

SANIT			:=	-g -fsanitize=undefined -fsanitize=address 
CC				:=	gcc
PRINT			:=	@

# STATIC
RM				:=	rm
MKDIR_P			:=	mkdir -p
INC_DIR			:=	./inc
SRC_DIR			:=	./src
OBJ_DIR			:=	./obj

INC_DIR_BONUS	:= ./inc_bonus
SRC_DIR_BONUS	:= ./src_bonus
OBJ_DIR_BONUS	:= ./obj_bonus

SRC				:=	main.c \
					intersection/i_.c \
					intersection/i_plane.c \
					intersection/i_sphere.c \
					intersection/i_cylinder.c \
					intersection/i_utils.c \
					parse_scene/ps_.c \
					parse_scene/ps_parse_line.c \
					parse_scene/ps_parse_objects.c \
					parse_scene/ps_utils.c \
					ray_trace/rt_.c \
					ray_trace/rt_lighting.c \
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

SRC_BONUS		:=	main_bonus.c \
					intersection/i_bonus.c \
					intersection/i_cone_bonus.c \
					intersection/i_cone_utils_bonus.c \
					intersection/i_plane_bonus.c \
					intersection/i_sphere_bonus.c \
					intersection/i_cylinder_bonus.c \
					intersection/i_utils_bonus.c \
					parse_scene/ps_bonus.c \
					parse_scene/ps_parse_line_bonus.c \
					parse_scene/ps_parse_objects_bonus.c \
					parse_scene/ps_parse_textures_bonus.c \
					parse_scene/ps_parse_textures_utils_bonus.c \
					parse_scene/ps_utils_bonus.c \
					ray_trace/rt_bonus.c \
					ray_trace/rt_lighting_bonus.c \
					ray_trace/rt_uv_pattern_bonus.c \
					ray_trace/rt_uv_map_to_2d_bonus.c \
					ray_trace/rt_pixel_put_bonus.c \
					utils/u_bonus.c \
					utils/u_conversion_bonus.c \
					utils/u_compare_bonus.c \
					utils/u_identify_bonus.c \
					utils/u_vector_math_bonus.c \
					utils/u_vector_operators_bonus.c \
					utils/u_rotate_vector_bonus.c \
					user_input/ui_bonus.c \
					user_input/ui_mouse_hook_bonus.c \
					user_input/ui_adjust_object_bonus.c 

OBJ				:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS		:=	$(SRC_BONUS:%.c=$(OBJ_DIR_BONUS)/%.o)


all				:	$(NAME)

$(NAME)			: 	$(OBJ)
					$(PRINT)$(CC) $(OBJ) $(MLX) -o $@ $(SANIT) -lm

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c $(INC_DIR)/%.h
					$(PRINT)$(MKDIR_P) $(dir $@)
					$(PRINT)$(CC) $(CFLAGS) $(SANIT) -c $< -o $@ 

bonus			:	$(NAME_BONUS)

$(NAME_BONUS)	:	$(OBJ_BONUS)
					$(PRINT)$(CC) $(OBJ_BONUS) $(MLX) -o $@ $(SANIT) -lm

$(OBJ_DIR_BONUS)/%.o	:	$(SRC_DIR_BONUS)/%.c $(INC_DIR_BONUS)/%.h
					$(PRINT)$(MKDIR_P) $(dir $@)
					$(PRINT)$(CC) $(CFLAGS) $(SANIT) -c $< -o $@ 


clean			:
					$(PRINT)$(RM) -rf $(OBJ_DIR)
					$(PRINT)$(RM) -rf $(OBJ_DIR_BONUS)

fclean			:	clean
					$(PRINT)$(RM) -f $(NAME)
					$(PRINT)$(RM) -f $(NAME_BONUS)

re				: 	fclean all

norm			:
					@norminette $(SRC_DIR) $(INC_DIR) $(SRC_DIR_BONUS) $(INC_DIR_BONUS)

.PHONY			:	all bonus clean fclean re norm
