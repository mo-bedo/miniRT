/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 19:32:17 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>

# include <time.h>
# include <stdio.h>
# define DEBUG_STR(X) printf(#X" = %s\n", X);
# define DEBUG_INT(X) printf(#X" = %d\n", X);
# define DEBUG_FLOAT(X) printf(#X" = %f\n", X);
# define DEBUG_DOUBLE(X) printf(#X" = %lf\n", X);

// IMAGE
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

// COORDINATES
typedef struct s_xyz
{
	float		x;
	float		y;
	float		z;
}	t_xyz;

typedef struct s_uv
{
	float		u;
	float		v;
}	t_uv;

// CAMERA
typedef struct s_camera {
	t_xyz		center;
	t_xyz		rotation_angles;
	float		canvas_distance;
}	t_camera;

// LIGHTS
typedef struct s_ambient_light
{
	t_xyz		color;
}	t_ambient_light;

typedef struct s_light
{
	t_xyz		origin;
	t_xyz		color;
}	t_light;

// OBJECTS
typedef struct s_map
{
	int			width;
	int			height;
	t_xyz		**map;
}	t_map;

typedef struct s_object
{
	int			type;
	t_xyz		center;
	t_xyz		vector_orientation;
	float		radius;
	float		height;
	t_xyz		color;
	bool		checkerboard;
	bool		image;
	float		specular;
	float		reflective;
	t_map		texture_map;
	// int			bump_map_fd;
	t_xyz		position;
	double		t;
	t_xyz		normal;
}	t_object;

// MASTER STRUCT OF STRUCTS
typedef struct s_mlx {
	void			*mlx;
	void			*window;
	t_img			img;
	t_camera		camera;
	t_ambient_light	ambient_light;
	t_light			light[100];
	int				light_count;
	t_object		object[100];
	int				object_count;
	t_xyz			background_color;
}	t_mlx;

enum e_values{
	WINDOW_WIDTH	= 640,
	WINDOW_HEIGHT	= 480,
	MAX_OBJECTS		= 100,
	X				= 0,
	Y				= 1,
	Z				= 2,
	LENGTH_NORMAL	= 1,
	RECURSION_DEPTH	= 3,
	NONE			= 0,
	PLANE			= 1,
	SPHERE			= 2,
	CYLINDER		= 3,
	CHECKERS		= 0,
	IMAGE			= 1,
	BUMP			= 2
};

void	print_time(char *action);

#endif				// MAIN_H


// resize image;
// convert earth.ppm -resize 100x50 earth_small.ppm

// convert P6 to P3
// convert earth_small.ppm -compress none earth_small.ppm
