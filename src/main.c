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
	t_cam		cam;

	if (argc < 2 || check_extension(argv[1]) == false)
		error_message_and_exit("Please provide a scene description file");
	parse_scene(&mlx, argv[1]);
 	mlx.mlx = mlx_init();
 	mlx.window = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (!mlx.window)
	{
		printf("mlx_window error\n");
		return (1);
	}
	cam = init_cam(mlx);
	ray_trace(&mlx, cam);
	mlx_loop(mlx.mlx);
	return (0);
}
