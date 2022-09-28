/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interaction.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 17:42:31 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/28 17:42:33 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTION_H
# define INTERACTION_H

enum e_key_codes{
	MOUSE_CLICK	= 1,
	SCROLL_UP	= 4,
	SCROLL_DOWN	= 5,
	MINUS		= 27,
	PLUS		= 24,
	LEFT		= 123,
	RIGHT		= 124,
	DOWN		= 125,
	UP			= 126,
	SPACEBAR	= 49,
	TAB			= 48,
	SHIFT		= 57,
	ESC			= 53,
	ZERO		= 29,
	ONE			= 18,
	TWO			= 19,
	THREE		= 20,
	FOUR		= 21
};

int		key_hook(int keycode, t_mlx *mlx);
int		mouse_hook(int keycode, int x, int y, t_mlx *mlx);

#endif