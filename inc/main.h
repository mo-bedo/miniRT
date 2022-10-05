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

typedef struct s_xy
{
	float		x;
	float		y;
}	t_xy;

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
typedef struct s_plane
{
	t_xyz		center;
	t_xyz		vector_orientation;
	t_xyz		color;
	int			specular;
	float		reflective;
}	t_plane;

typedef struct s_sphere
{
	t_xyz		center;
	float		radius;
	t_xyz		color;
	int			specular;
	float		reflective;
}	t_sphere;

typedef struct s_cylinder
{
	t_xyz		center;
	t_xyz		vector_orientation;
	float		radius;
	float		height;
	t_xyz		color;
	int			specular;
	float		reflective;
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

// MASTER STRUCT OF STRUCTS
typedef struct s_mlx {
	void			*mlx;
	void			*window;
	t_img			img;
	t_camera		camera;
	t_ambient_light	ambient_light;
	t_light			light[100];
	int				light_count;
	t_objects		o;
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
	CYLINDER		= 3
};

#endif				// MAIN_H
