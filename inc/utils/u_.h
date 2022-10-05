/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 16:07:41 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "main.h"
# include "utils/u_conversion.h"

void	ft_putstr(char *s);
void	error_message_and_exit(char *message);
int		close_window(t_mlx *mlx);
int		ft_is_digit(int c);
int		ft_is_space(char c);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
double	get_smallest_double(double a, double b);
float	ft_min_float(float a, float b);
float	ft_max_float(float a, float b);

#endif
