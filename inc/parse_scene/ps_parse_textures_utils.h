/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_parse_textures_utils.h                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:22:31 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_PARSE_TEXTURES_UTILS_H
# define PS_PARSE_TEXTURES_UTILS_H

# include "main.h"

t_xyz	**allocate_map(int width, int height);
int		ft_strlcpy(char *dst, char *src, int size);
char	*get_path(char *input);
int		get_length_of_file(char *path);

#endif
