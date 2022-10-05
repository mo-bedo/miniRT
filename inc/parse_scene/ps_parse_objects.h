/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_parse_objects.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:37:06 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_PARSE_OBJECTS_H
# define PS_PARSE_OBJECTS_H

# include "main.h"

void	parse_plane(t_mlx *mlx, char *line);
void	parse_sphere(t_mlx *mlx, char *line);
void	parse_cylinder(t_mlx *mlx, char *line);

#endif
