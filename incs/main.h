/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/21 12:36:15 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef struct s_data {
	void	*img;
	char	*address;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_image {
	int	width;
	int	height;
}	t_image;

typedef struct s_camera {
	t_vec	view_point;
	t_vec	orientation_vector;
	double	fov;
}	t_camera;

typedef struct s_plane {
	t_vec	coord;
	t_vec	orientatation_vector;
	t_color	color;
}	t_plane;

#endif				// MAIN_H