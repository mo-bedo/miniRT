/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_compare.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 19:49:01 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_COMPARE_H
# define U_COMPARE_H

# include "main.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
double	get_smallest_double(double a, double b);
float	ft_min_float(float a, float b);
float	ft_max_float(float a, float b);

#endif