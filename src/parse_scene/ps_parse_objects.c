/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:39:26 by mweitenb          #+#    #+#             */
/*   Updated: 2022/10/13 16:28:14 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/ps_parse_textures.h"
#include "parse_scene/ps_utils.h"
#include "utils/u_.h"

// static t_xyz	get_angle_over_the_axes(t_xyz vector1, t_xyz vector2)
// {
// 	t_xyz	angles;
// 	t_xyz	v1;
// 	t_xyz	v2;

// 	if (vector2.y < 0)
// 		vector2 = multiply_vector(vector2, -1);
// 	angles.x = 0;
// 	angles.y = 0;
// 	angles.z = 0;

// 	// Rotation over X axis
// 	v1 = vector1;
// 	v1.x = 0;
// 	v2 = vector2;
// 	v2.x = 0;
// 	angles.x = get_angle_between_vectors(v1, v2);
// 	if (v2.z > 0)
// 		angles.x *= -1;

// 	// Rotation over Z axis
// 	v1 = vector1;
// 	v1.z = 0;
// 	v2 = vector2;
// 	v2.z = 0;
// 	angles.z = get_angle_between_vectors(v1, v2);
// 	if (v2.x < 0)
// 		angles.z *= -1;
// 	return (angles);
// }

static void	parse_plane(t_object *object, char **line)
{
	*line += 2;
	object->type = PLANE;
	object->center = parse_xyz(line, MIN_XYZ, MAX_XYZ);
	object->orientation = parse_orientation(line);
}

static void	parse_sphere(t_object *object, char **line)
{
	*line += 2;
	object->type = SPHERE;
	object->center = parse_xyz(line, MIN_XYZ, MAX_XYZ);
	object->radius = parse_float(line, MIN_DIAMETER, MAX_DIAMETER) / 2;
}

static void	parse_cylinder(t_object *object, char **line)
{
	*line += 2;
	object->type = CYLINDER;
	object->center = parse_xyz(line, MIN_XYZ, MAX_XYZ);
	object->orientation = parse_orientation(line);
	object->radius = parse_float(line, MIN_DIAMETER, MAX_DIAMETER) / 2;
	object->height = parse_float(line, MIN_CY_HEIGHT, MAX_CY_HEIGHT);
	// t_xyz new;
	// initialize_vector(&new, 1, -1, 0);
	// t_xyz rotation = get_angle_over_the_axes(object->orientation, new);
	// object->orientation = rotate_vector(object->orientation, rotation);
}

void	parse_objects(t_mlx *mlx, char *line)
{
	int	i;

	if (mlx->object_count >= MAX_OBJECTS)
		error_message_and_exit("Too many objects in scene");
	i = mlx->object_count;
	if (str_is_equal(line, "pl", 2))
		parse_plane(&mlx->object[i], &line);
	if (str_is_equal(line, "sp", 2))
		parse_sphere(&mlx->object[i], &line);
	if (str_is_equal(line, "cy", 2))
		parse_cylinder(&mlx->object[i], &line);
	normalize_vector(&mlx->object[i].orientation);
	mlx->object[i].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->object[i].specular = 0;
	mlx->object[i].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->object[i].reflective = 0;
	mlx->object[i].reflective
		= parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
	parse_textures(&mlx->object[i], &line);
	mlx->object[i].t = RAY_T_MAX;
	mlx->object_count += 1;
}
