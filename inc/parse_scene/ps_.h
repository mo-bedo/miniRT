/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:12:48 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS__H
# define PS__H

# include "main.h"

bool	has_valid_extension(char *filename, char *valid_ext);
void	parse_scene(t_mlx	*mlx, int argc, char *input);

#endif
