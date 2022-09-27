/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:20:58 by mweitenb          #+#    #+#             */
/*   Updated: 2022/09/23 20:06:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_scene/parse_scene.h"
#include "camera.h"
#include "main.h"
#include "mlx.h"
#include "ray_trace.h"
#include "shape.h"
#include "utils.h"
#include "vector_math.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

bool	check_extension(char *filename)
{
	char *extension;
	
	extension = ft_strrchr(filename, '.');
	if (ft_strncmp(extension, ".rt", 4) == 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_img		img; 
	t_cam		cam;

	if (argc < 2 || check_extension(argv[1]) == false)
		error_message_and_exit("Please provide a scene description file");
	parse_scene(&mlx, argv[1]);
//	printf("%f %f %f\n", mlx.d.o.pl[0].xyz.x, mlx.d.o.pl[0].xyz.y, mlx.d.o.pl[0].xyz.z);
 	mlx.mlx = mlx_init();
 	mlx.window = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (!mlx.window)
	{
		printf("mlx_window error\n");
		return (1);
	}
//	cam = init_cam(camera_origin, camera_orientation, camera_upguide, fov / 2, (float) image.width / (float) image.height);
//	ray_trace(mlx, image, cam, shapes);

// 	img.img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);



	cam = init_cam(mlx);
	ray_trace(&mlx, cam);
	mlx_loop(mlx.mlx);

	return (0);
}

/*
 * 	t_cam cam;

	//// Van de parser input
	//// cam
	t_vec camera_origin;
	camera_origin.x = 55.0;
	camera_origin.y = 111.0;
	camera_origin.z = -40.0;
	t_vec camera_orientation;
	camera_orientation.x = 1.0;
	camera_orientation.y = 0.0;
	camera_orientation.z = 0.0;
	t_vec camera_upguide;
	camera_upguide.x = 0.0;
	camera_upguide.y = 1.0;
	camera_upguide.z = 0.0;
	//// plane
	t_shape	shapes;
	shapes.spheres = malloc (2 * sizeof (t_sphere));
	shapes.sphere_count = 2;
	shapes.planes = malloc (1 * sizeof (t_plane));
	shapes.plane_count = 1;
	t_plane plane;
	plane.normal.x = 0.0;
	plane.normal.y = 1.0;
	plane.normal.z = 0.0;
	plane.position.x = 1.0;
	plane.position.y = 380.0;
	plane.position.z = 0.0;
	shapes.planes[0] = plane;


	t_sphere	sphere;
	sphere.centre.x = 130.0;
	sphere.centre.y = 30.0;
	sphere.centre.z = 10.0;
	sphere.radius = 30;
	shapes.spheres[0] = sphere;
	t_sphere	sphere1;
	sphere1.centre.x = 30.0;
	sphere1.centre.y = 30.0;
	sphere1.centre.z = 10.0;
	sphere1.radius = 30;
	shapes.spheres[1] = sphere1;

	int fov = 180;
 */