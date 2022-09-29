/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 15:49:21 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_scene/ps.h"
#include "main.h"
#include "mlx.h"
#include "ray_trace.h"
#include "interaction.h"
#include "utils/utils.h"
#include "utils/vector_math.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

bool	check_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (ft_strncmp(extension, ".rt", 4) == 0)
		return (true);
	return (false);
}

static void	init(t_mlx	*mlx)
{
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	mlx->img.img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->window)
		error_message_and_exit("mlx_window error");
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	mlx->aspect_ratio = (double) WINDOW_WIDTH / (double) WINDOW_HEIGHT;
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc < 2 || check_extension(argv[1]) == false)
		error_message_and_exit("Please provide a scene description file");
	init(&mlx);
	parse_scene(&mlx, argv[1]);
	ray_trace(&mlx);
	mlx_hook(mlx.window, 17, 0, close_window, &mlx);
	mlx_mouse_hook(mlx.window, mouse_hook, &mlx);
	mlx_key_hook(mlx.window, key_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
