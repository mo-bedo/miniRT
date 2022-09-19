#include "miniRT.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->address + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_line(t_data *data, int heigth, int length, int color)
{
	for (int i = 0; i < 300; i++)
	{
		my_pixel_put(data, heigth, length + i, color);
	}
}

int circle(t_data *data)
{
	for (int i = 0; i < 400; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			if (pow(i, 2) + pow (j, 2) < 10000)
			{
				my_pixel_put(data, i + 200, j + 200, 0x00FF00);
				my_pixel_put(data, -i + 200, j + 200, 0x00FF00);
				my_pixel_put(data, i + 200, -j + 200, 0x00FF00);
			}
		}
	}
	return 1;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_vec	v;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "my window");
	img.img = mlx_new_image(mlx, 800, 600);
	img.address = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length, &img.endian);
	v.x = 10;
	v.y = 15;
	circle(&img);
//
//	draw_line(&img, 20, 30, 0x0000FF);
//	draw_line(&img, 21, 30, 0x0000FF);
//	draw_line(&img, 45, 30, 0x00FF00);
//	draw_line(&img, 46, 30, 0x00FF00);
//	draw_line(&img, 77, 30, 0xFF0000);
//	draw_line(&img, 78, 30, 0xFF0000);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
