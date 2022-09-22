/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/21 17:44:10 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "main.h"

void	ft_putstr(char *s);
int		ft_isdigit(int c);
int		is_space(char c);
void	error_message_and_exit(char *message);
int		ft_atoi(const char *str);
int		ft_char_to_digit(int c);
void	*ft_calloc(size_t count, size_t size);

#endif
