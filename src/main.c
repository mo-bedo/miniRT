/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 19:39:27 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_scene/ps_.h"
#include "parse_scene/ps_utils.h"
#include "main.h"
#include "mlx.h"
#include "ray_trace.h"
#include "interaction.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

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
		error_message_and_exit("Can't creat mlx_window");
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	mlx->aspect_ratio = (double) WINDOW_WIDTH / (double) WINDOW_HEIGHT;
	mlx->background_color.x = MIN_COLOR;
	mlx->background_color.y = MIN_COLOR;
	mlx->background_color.z = MIN_COLOR;
	mlx->o.pl_count = 0;
	mlx->o.sp_count = 0;
	mlx->o.cy_count = 0;
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	clock_t CPU_time_1 = clock();
	if (argc < 2 || check_extension(argv[1]) == false)
		error_message_and_exit("Please provide a scene description file");
	init(&mlx);
	parse_scene(&mlx, argv[1]);
	clock_t CPU_time_2 = clock();
	printf("Time after parsing\t: %ld\n", CPU_time_2);
	ray_trace(&mlx);
	mlx_hook(mlx.window, 17, 0, close_window, &mlx);
	// mlx_mouse_hook(mlx.window, mouse_hook, &mlx);
	mlx_key_hook(mlx.window, key_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
