/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 21:00:39 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_scene/ps_.h"
#include "parse_scene/ps_utils.h"
#include "main.h"
#include "mlx.h"
#include "ray_trace/rt_.h"
#include "interaction.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <locale.h>

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
	mlx->background_color.x = MAX_COLOR;
	mlx->background_color.y = MAX_COLOR;
	mlx->background_color.z = MAX_COLOR;
	mlx->o.pl_count = 0;
	mlx->o.sp_count = 0;
	mlx->o.cy_count = 0;
}

void	print_time(char *action)
{
	clock_t		time;

	time = clock();
	setlocale(LC_NUMERIC, "");
	printf("%s", action);
	printf("\t: %'12.ld\n", time);
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	print_time("start\t");
	init(&mlx);
	parse_scene(&mlx, argc, argv[1]);
	print_time("parse_scene");
	interaction(&mlx);
	ray_trace(&mlx);
	print_time("ray_trace");
	mlx_loop(mlx.mlx);
	return (0);
}
