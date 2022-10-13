/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:08:23 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_scene/ps_.h"
#include "parse_scene/ps_utils.h"
#include "main.h"
#include "mlx.h"
#include "ray_trace/rt_.h"
#include "user_input/ui_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <locale.h>

void	error_message_and_exit(char *message)
{
	ft_putstr("\nError\n");
	ft_putstr(message);
	ft_putstr("\n\n");
	exit(EXIT_FAILURE);
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
	initialize_vector(&mlx->background_color, 255, 255, 255);
	mlx->object_count = 0;
	mlx->selected_object = -1;
	mlx->selected_action = -1;
}

void	print_time(char *action)
{
	clock_t			time;
	static long int	start_time = 0;

	time = clock();
	setlocale(LC_NUMERIC, "");
	printf("%s", action);
	if (str_is_equal(action, "rt_", 2))
		printf("\t: %'12.ld\n", time - start_time);
	else
		printf("\t: %'12.ld\n", time);
	start_time = time;
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	print_time("start\t");
	init(&mlx);
	parse_scene(&mlx, argc, argv[1]);
	print_time("parse_scene");
	user_input(&mlx);
	ray_trace(&mlx);
	print_time("ray_trace");
	mlx_loop(mlx.mlx);
	exit(EXIT_SUCCESS);
}
