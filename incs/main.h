/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/21 18:45:30 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# define DEBUG_STR(X) printf(#X" = %s\n", X);
# define DEBUG_INT(X) printf(#X" = %d\n", X);

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_menu
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_menu;

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

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_vec2 {
	double	u;
	double	v;
}	t_vec2;

typedef struct s_xyz
{
	float	x;
	float	y;
	float	z;
}	t_xyz;

typedef struct s_ambient_lightning
{
	int		lighting_ratio;
	t_rgb	rgb;
}	t_ambient_lightning;

typedef struct s_camera
{
	t_xyz	coordinates;
	t_vec	orientation_vector;
	int		field_of_range;
}	t_camera;

typedef struct s_light
{
	t_xyz	coordinates;
	int		brightness;
}	t_light;

//typedef struct s_sphere
//{
//	t_xyz	coordinates;
//	float	diameter;
//	t_rgb	rgb;
//}	t_sphere;

//typedef struct s_plane
//{
//	t_xyz	coordinates;
//	t_vec	orientation_vector;
//	t_rgb	rgb;
//}	t_plane;

typedef struct s_image {
	int			width;
	int			height;

}	t_image;

typedef struct s_cylinder
{
	t_xyz	coordinates;
	t_vec	orientation_vector;
	float	diameter;
	float	height;
	t_rgb	rgb;
}	t_cylinder;

//typedef struct s_data
//{
//	t_ambient_lightning	a;
//	t_camera			c;
//	t_light				l;
//	t_sphere			sp;
//	t_plane				pl;
//	t_cylinder			cy;
//}	t_data;

// MASTER STRUCT OF STRUCTS
//typedef struct s_mlx {
//	// void			*mlx;
//	// void			*window;
//	// int				display_menu;
//	t_data			d;
//	// t_coordinates	c;
//	// t_img			img;
//	// t_menu			menu;
//	// t_colors		colors;
//}	t_mlx;

enum e_values{
	// WINDOW_HEIGHT	= 960,
	// WINDOW_WIDTH	= 1280,
	// TOTAL_RANGE_Y	= 4,
	MAX_COLOR		= 16777215
};



#endif				// MAIN_H
