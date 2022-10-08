/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:58:22 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/ps_parse_line.h"
#include "parse_scene/ps_utils.h"
#include "utils/u_vector_math.h"
#include "utils/u_.h"
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

static void	check_if_capital_elements_are_declared_multiple_times(char *line)
{
	static int	a = 0;
	static int	c = 0;
	static int	l = 0;
	static int	total_objects = 0;

	if (ft_strncmp(line, "A", 1) == 0)
		a++;
	else if (ft_strncmp(line, "C", 1) == 0)
		c++;
	// else if (ft_strncmp(line, "L", 1) == 0)
		// l++;
	else
		total_objects++;
	if (a > 1 || l > 1)
		error_message_and_exit("Scene declares multiple lights");
	if (c > 1)
		error_message_and_exit("Scene declares multiple cameras");
	if (total_objects > MAX_OBJECTS)
		error_message_and_exit("Too many objects in scene");
}

void	parse_scene(t_mlx *mlx, int argc, char *input)
{
	int		rt_file;
	int		there_is_a_new_line;
	char	*line;

	if (argc != 2 || has_no_valid_extension(input, ".rt"))
		error_message_and_exit("Please provide a scene description file");
	rt_file = open(input, O_RDONLY);
	if (rt_file < 0)
		error_message_and_exit("File does not exist");
	while (1)
	{
		line = (char *)ft_calloc(sizeof(char), 1);
		there_is_a_new_line = get_next_line(&line, rt_file);
		check_if_capital_elements_are_declared_multiple_times(line);
		parse_line(mlx, line);
		free(line);
		if (!there_is_a_new_line)
			return ;
	}
}
