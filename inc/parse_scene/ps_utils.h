/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_utils.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:46:23 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_UTILS_H
# define PS_UTILS_H

# include "main.h"

void	error_message_and_exit(char *message);
int		parse_int(char **str, int min, int max);
float	parse_float(char **str, int min, int max);
t_xyz	parse_xyz(char **str, int min, int max);
t_xyz	parse_vector_orientation(char **str);
bool	has_valid_extension(char *filename, char *valid_ext);
char	*add_buffer_to_line(char *old, char buffer);
int		get_next_line(char **line, int fd);
int		ft_strlcpy(char *dst, char *src, int size);
int		get_length_of_file(char *path);
t_xyz	get_angle_over_the_axes(t_xyz vector1, t_xyz vector2);

enum e_xyz_range {
	MIN_COLOR			= 0,
	MAX_COLOR			= 255,
	MIN_FOV				= 0,
	MAX_FOV				= 180,
	MIN_XYZ				= -10000,
	MAX_XYZ				= 10000,
	MIN_3D				= -1,
	MAX_3D				= 1,
	MIN_BRIGHTNESS		= 0,
	MAX_BRIGHTNESS		= 1,
	MIN_DIAMETER		= 0,
	MAX_DIAMETER		= 10000,
	MIN_SPECULAR		= 0,
	MAX_SPECULAR		= 10000,
	MIN_REFLECTIVE		= 0,
	MAX_REFLECTIVE		= 1,
	MIN_CY_HEIGHT		= 0,
	MAX_CY_HEIGHT		= 600,
	MIN_PPM_SIZE		= 10,
	MAX_PPM_SIZE		= 2000
};

#endif
