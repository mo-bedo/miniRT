/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_bonus.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:12:48 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_BONUS_H
# define PS_BONUS_H

# include "main_bonus.h"

bool	has_valid_extension(char *filename, char *valid_ext);
void	parse_scene(t_mlx	*mlx, int argc, char *input);

#endif
