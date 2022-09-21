/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/21 18:52:59 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_input.h"
#include "utils.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <stdlib.h>
# include <fcntl.h>
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

// BUG		: als scene.rt eindigt op \n -> neverending loop
// TO DO	: controleren of scene file .rt extensie heeft
static void	init(t_mlx	*mlx, char *input)
{
	int		rt_file = open(input, O_RDONLY);
	char	*line;

	while (1)
	{
		line = get_next_line(rt_file);
		if (!line)
			return ;
		parse_input(mlx, line);
		free(line);
	}
	// mlx->mlx = mlx_init();
	// mlx->window = mlx_new_window(mlx->mlx,
	// 		WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT");
	// mlx->img.img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// mlx->img.addr = mlx_get_data_addr(mlx->img.img,
	// 		&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	// init_data(mlx);
	// mlx->display_menu = 1;
}

// static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
// 	char	*dst;
// 	int		offset;

// 	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	dst = &img->addr[offset];
// 	*(unsigned int *)dst = color;
// }

// int circle(t_data *data)
// {
// 	for (int i = 0; i < 400; i++)
// 	{
// 		for (int j = 0; j < 600; j++)
// 		{
// 			if (pow(i, 2) + pow (j, 2) < 10000)
// 			{
// 				my_mlx_pixel_put(data, i + 200, j + 200, 0x00FF00);
// 				my_mlx_pixel_put(data, -i + 200, j + 200, 0x00FF00);
// 				my_mlx_pixel_put(data, i + 200, -j + 200, 0x00FF00);
// 			}
// 		}
// 	}
// 	return (1);
// }

int	main(int argc, char **argv)
{
	t_mlx			mlx;

	if (argc < 2)
		error_message_and_exit("Please provide a scene description file");
	init(&mlx, argv[1]);
	// circle(&img);
	// mlx_hook(mlx.window, 17, 0, close_window, &mlx);
	// mlx_loop(mlx.mlx);
	exit(EXIT_SUCCESS);
}

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;
// 	t_vec	v;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 800, 600, "my window");
// 	img.img = mlx_new_image(mlx, 800, 600);
// 	img.address = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length, &img.endian);
// 	v.x = 10;
// 	v.y = 15;
// 	circle(&img);
// //
// //	draw_line(&img, 20, 30, 0x0000FF);
// //	draw_line(&img, 21, 30, 0x0000FF);
// //	draw_line(&img, 45, 30, 0x00FF00);
// //	draw_line(&img, 46, 30, 0x00FF00);
// //	draw_line(&img, 77, 30, 0xFF0000);
// //	draw_line(&img, 78, 30, 0xFF0000);

// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// 	return (0);
// }
