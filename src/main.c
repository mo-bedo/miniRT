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



// #include "utils/matrices.h"
// #include "utils/u_invert_matrix.h"

// int main()
// {
// 	t_matrix4 c;
// 	t_matrix4 b;
// 	t_matrix4 m;
	
// 	int x = 3;
// 	for (int i = 0; i < 2; i++)
// 	{
// 		x++;
// 		for (int j = 0; j < 4; j++)
// 		{
// 			x+= 3; 
// 			b.value[i][j] = x;
// 		}
	
// 	}
// 	x = -15;
// 	for (int i = 2; i < 4; i++)
// 	{
// 		x++;
// 		for (int j = 0; j < 4; j++)
// 		{
// 			x-= 3; 
// 			b.value[i][j] = x;
// 		}
	
// 	}

// 	b.value[0][0] = 1;
// 	b.value[0][1] = 4;
// 	b.value[0][2] = 2;
// 	b.value[0][3] = 3;
// 	b.value[1][0] = 3;
// 	b.value[1][1] = -1;
// 	b.value[1][2] = 4;
// 	b.value[1][3] = -3;
// 	b.value[2][0] = -1;
// 	b.value[2][1] = 1;
// 	b.value[2][2] = 3;
// 	b.value[2][3] = 5;
// 	b.value[3][0] = 1;
// 	b.value[3][1] = -01;
// 	b.value[3][2] = 4;
// 	b.value[3][3] = 1;

// 	// printf("input matrix: \n");
// 	// print_matrix(b);

// 	t_matrix4 invert;

// 	invert = invert_matrix(b);


// 	print_matrix(invert);

	// t_matrix8 A;



	// b = set_matrix_to_identity(b);
	// c = set_matrix_to_identity(c);

	// // b.value[0][2] = 1;

	// A = augment_matrices(b, c);

	// print_matrix8(A);

	// if (left_matrix_is_identity(A))
	// 	printf("should print\n");







