/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by mweitenb          #+#    #+#             */
/*   Updated: 2022/09/23 18:09:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>

# include <stdio.h>
# define DEBUG_STR(X) printf(#X" = %s\n", X);
# define DEBUG_INT(X) printf(#X" = %d\n", X);
# define DEBUG_FLOAT(X) printf(#X" = %f\n", X);

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

// typedef struct s_menu
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }	t_menu;

// typedef struct s_coordinates
// {
// 	double	image_ratio;
// 	double	center_x;
// 	double	center_y;
// 	double	total_range_x;
// 	double	total_range_y;
// 	double	size_of_pixel;
// }	t_coordinates;

typedef struct s_colors
{
	int	color;
	int	opacity;
}	t_colors;

// DATA
typedef struct s_rgb
{
	int		red;
	int		green;
	int		blue;
}	t_rgb;

typedef struct s_xy {
	float	u;
	float	v;
}	t_xy;

typedef struct s_xyz
{
	float	x;
	float	y;
	float	z;
}	t_xyz;

typedef struct s_ambient_lightning
{
	float	lighting_ratio;
	t_rgb	rgb;
}	t_ambient_lightning;

typedef struct s_camera
{
	t_xyz	xyz;
	t_xyz	vector_orientation;
	int		field_of_view;
}	t_camera;

typedef struct s_light
{
	t_xyz	xyz;
	float	brightness;
}	t_light;

typedef struct s_sphere
{
	t_xyz	centre;
	float	radius;
	t_rgb	rgb;
}	t_sphere;

typedef struct s_plane
{
	t_xyz	xyz;
	t_xyz	vector_orientation;
	t_rgb	rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_xyz	xyz;
	t_xyz	vector_orientation;
	float	diameter;
	float	height;
	t_rgb	rgb;
}	t_cylinder;

typedef struct s_objects
{
	t_sphere	sp[100];
	int			sp_count;
	t_plane		pl[100];
	int			pl_count;
	t_cylinder	cy[100];
	int			cy_count;
}	t_objects;

typedef struct s_data
{
	t_camera			c;
	t_ambient_lightning	a;
	t_light				l;
	t_objects			o;
}	t_data;

// MASTER STRUCT OF STRUCTS
typedef struct s_mlx {
	void			*mlx;
	void			*window;
	// int				display_menu;
	t_data			d;
	// t_coordinates	c;
	// t_img			img;
	// t_menu			menu;
	// t_colors		colors;
}	t_mlx;

enum e_values{
	WINDOW_HEIGHT	= 480,
	WINDOW_WIDTH	= 640,
	MAX_OBJECTS		= 100
	// TOTAL_RANGE_Y	= 4,
	// MAX_COLOR		= 16777215
};



#endif				// MAIN_H
