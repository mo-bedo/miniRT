/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:45:14 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U__H
# define U__H

# include "main.h"
# include "utils/u_conversion.h"
# include "utils/u_compare.h"

int     ft_strlen(const char *s);
void	ft_putstr(char *s);
int		ft_is_digit(int c);
int		ft_is_space(char c);
void	*ft_calloc(size_t count, size_t size);
void	initialize_empty_vector(t_xyz *vector);
void	initialize_black_color(t_xyz *vector);
void	initialize_white_color(t_xyz *vector);

#endif
