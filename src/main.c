/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/09 19:02:57 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#include "main.h"
#include "parse_scene/ps_.h"
#include "parse_scene/ps_utils.h"
#include "ray_trace/rt_.h"
#include "user_input/ui_.h"
#include "utils/u_.h"

void	error_message_and_exit(char *message)
{
	ft_putstr("\e[1;1H\e[2J");
	ft_putstr("Error\n");
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

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	ft_putstr("\e[1;1H\e[2J");
	init(&mlx);
	parse_scene(&mlx, argc, argv[1]);
	user_input(&mlx);
	ray_trace(&mlx);
	mlx_loop(mlx.mlx);
	exit(EXIT_SUCCESS);
}
