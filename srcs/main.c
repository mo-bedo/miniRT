/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/21 18:53:49 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "main.h"
#include "mlx.h"
#include "parse_input.h"
#include "ray_trace.h"
#include "shape.h"
#include "utils.h"
#include "vector_math.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// int	close_window(t_mlx *mlx)
// {
// 	mlx_destroy_window(mlx->mlx, mlx->window);
// 	exit(EXIT_SUCCESS);
// }

// void	init_data(t_mlx *mlx)
// {
// 	mlx->c.image_ratio = (double)WINDOW_HEIGHT / (double)WINDOW_WIDTH;
// 	mlx->c.total_range_y = TOTAL_RANGE_Y;
// 	mlx->c.total_range_x = mlx->c.total_range_y / mlx->c.image_ratio;
// 	mlx->c.size_of_pixel = mlx->c.total_range_y / WINDOW_HEIGHT;
// 	mlx->c.center_x = mlx->c.total_range_x / 2;
// 	mlx->c.center_y = mlx->c.total_range_y / 2;
// 	mlx->colors.color = 0;
// 	mlx->colors.opacity = 200;
// }

static char	*add_buffer_to_line(char *old, char buffer)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (old[len])
		len++;
	new = (char *)ft_calloc(sizeof(char), (len + 2));
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	new[i++] = buffer;
	new[i] = 0;
	free(old);
	return (new);
}

static char	*get_next_line(int fd)
{
	char	buffer;
	char	*line;

	line = (char *)ft_calloc(sizeof(char), 1);
	line[0] = 0;
	while (read(fd, &buffer, 1) && buffer != '\n')
	{
		line = add_buffer_to_line(line, buffer);
	}
	if (buffer == '\n')
		line = add_buffer_to_line(line, '\n');
	return (line);
}

//// BUG		: als scene.rt eindigt op \n -> neverending loop
//// TO DO	: controleren of scene file .rt extensie heeft
//static void	init(t_mlx	*mlx, char *input)
//{
//	int		rt_file = open(input, O_RDONLY);
//	char	*line;
//
//	while (1)
//	{
//		line = get_next_line(rt_file);
//		if (!line)
//			return ;
//		parse_input(mlx, line);
//		free(line);
//	}
//	// mlx->mlx = mlx_init();
//	// mlx->window = mlx_new_window(mlx->mlx,
//	// 		WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT");
//	// mlx->img.img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
//	// mlx->img.addr = mlx_get_data_addr(mlx->img.img,
//	// 		&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
//	// init_data(mlx);
//	// mlx->display_menu = 1;
//}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_image image;
	image.width = 800;
	image.height = 600;

	mlx = malloc (sizeof(t_mlx));
 	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		printf("mlx_init error\n");
		return (1);
	}
 	mlx->window = mlx_new_window(mlx->mlx, image.width, image.height, "my window");
	if (!mlx->window)
	{
		printf("mlx_window error\n");
		return (1);
	}
// 	mlx->img = mlx_new_image(mlx, width, heigth);
//	mlx->img->addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	t_cam cam;

	//// Van de parser input
	//// cam
	t_vec camera_origin;
	camera_origin.x = -50.0;
	camera_origin.y = 0;
	camera_origin.z = 20;
	t_vec camera_orientation;
	camera_orientation.x = 0.0;
	camera_orientation.y = 0.0;
	camera_orientation.z = 1.0;
	t_vec camera_upguide;
	camera_upguide.x = 0.0;
	camera_upguide.y = 1.0;
	camera_upguide.z = 0.0;
	//// plane
	t_shape	shapes;
	t_plane plane;
	shapes.planes = &plane;
	plane.normal.x = 0.0;
	plane.normal.y = 0.0;
	plane.normal.z = 1.0;
	plane.position.x = 0.0;
	plane.position.y = 50.0;
	plane.position.z = 0.0;
	t_sphere	sphere;
	sphere.centre.x = 30.0;
	sphere.centre.y = 30.0;
	sphere.centre.x = -30.0;
	sphere.radius = 30;
	shapes.spheres = &sphere;

	int fov = 180;

	cam = init_cam(camera_origin, camera_orientation, camera_upguide, fov / 2, (float) image.width / (float) image.height);
	ray_trace(mlx, image, cam, shapes);
	mlx_loop(mlx->mlx);
	return (0);
}
