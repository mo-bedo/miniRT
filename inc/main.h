#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>
# include <stdio.h>

# define PI 3.14159f
# define RAY_T_MIN 0.0001f
# define RAY_T_MAX 1.0e30f
# define ADJUSTMENT_SIZE 0.2f
# define ADJUSTMENT_SCALE 1.2f
# define MIN_OBJECT_SIZE 0.1f
# define MAX_OBJECTS 100
# define PLANE_MAP_SCALE 100
# define RECURSION_DEPTH 3
# define LENGTH_NORMAL 1
# define TILE_SIZE 16
# define TILE_SIZE_PLANE 4
# define ROTATION_SPEED 6

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
// PAS OP HALF_WINDOW_WIDTH handmatig aanpassen!
# define HALF_WINDOW_WIDTH 320
// PAS OP HALF_WINDOW_HEIGHT handmatig aanpassen!
# define HALF_WINDOW_HEIGHT	240

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
typedef struct s_wxyz
{
	float		w;
	float		x;
	float		y;
	float		z;
}	t_wxyz;

typedef struct s_xyz
{
	float		x;
	float		y;
	float		z;
}	t_xyz;

typedef struct s_xy
{
	int			x;
	int			y;
}	t_xy;

typedef struct s_uv
{
	float		u;
	float		v;
}	t_uv;

// CAMERA
typedef struct s_camera {
	t_xyz		center;
	t_xyz		orientation;
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
	bool		is_cap;
	bool		is_inside;
	bool		checkerboard;
	bool		texture;
	t_map		texture_map;
	bool		bump;
	t_map		bump_map;
	t_xyz		intersect;
	float		t;
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

enum e_coordinates { X, Y, Z };
enum e_objects { NONE, PLANE, SPHERE, CYLINDER, CONE };
enum e_textures { CHECKERS, TEXTURE, BUMP_MAP };

void	error_message_and_exit(char *message);
void	print_time(char *action);

#endif				// MAIN_H
