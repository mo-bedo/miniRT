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
 	// mlx = mlx_init();
 	// mlx.window = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	// if (!mlx.window)
	// {
	// 	printf("mlx_window error\n");
	// 	return (1);
	// }
 	// img.img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// cam = init_cam(mlx);
	// ray_trace(cam, mlx.d.o.pl[0], mlx.d.o.sp[0]);
	// mlx_loop(mlx.mlx);

	return (0);
}
