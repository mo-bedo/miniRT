/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by mweitenb          #+#    #+#             */
/*   Updated: 2022/10/17 12:04:31 by jbedaux          ###   ########.fr       */
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

# define PI 3.14159f
# define RAY_T_MIN 0.0001f
# define RAY_T_MAX 1.0e30f

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
// # define WINDOW_WIDTH 1280
// # define WINDOW_HEIGHT 960
# define HALF_WINDOW_WIDTH WINDOW_WIDTH / 2
# define HALF_WINDOW_HEIGHT	WINDOW_HEIGHT / 2
# define MAX_OBJECTS 100
# define PLANE_MAP_SCALE 20

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
	t_xyz		orientation;
	float		radius;
	float		height;
	t_xyz		color;
	float		specular;
	float		reflective;
	bool		checkerboard;
	bool		texture;
	t_map		texture_map;
	bool		bump;
	t_map		bump_map;
	t_xyz		intersect;
	double		t;
	int			id;
	t_xyz		normal;
}	t_object;

// MASTER STRUCT OF STRUCTS
typedef struct s_mlx {
	void			*mlx;
	void			*window;
	t_img			img;
	t_camera		camera;
	t_ambient_light	ambient_light;
	t_light			light[MAX_OBJECTS];
	int				light_count;
	t_object		object[MAX_OBJECTS];
	int				object_count;
	t_xyz			background_color;
	int				selected_object;
	int				selected_action;
}	t_mlx;

enum e_values{
	RECURSION_DEPTH		= 3,
	X					= 0,
	Y					= 1,
	Z					= 2,
	LENGTH_NORMAL		= 1,
	NONE				= 0,
	PLANE				= 1,
	SPHERE				= 2,
	CYLINDER			= 3,
	CONE				= 4,
	CHECKERS			= 0,
	TEXTURE				= 1,
	BUMP_MAP			= 2,
	BUMP_SCALE			= 30
};

void	error_message_and_exit(char *message);
void	print_time(char *action);

#endif				// MAIN_H
// resize image;
// convert earth.ppm -resize 300x150 earth_small.ppm
// convert P6 to P3
// convert earth_small.ppm -compress none earth_small.ppm
