/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 17:42:31 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/09 14:33:05 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI__H
# define UI__H

# include "main.h"

enum e_key_codes {
	MOUSE_CLICK		= 1,
	SCROLL_UP		= 4,
	SCROLL_DOWN		= 5,
	MINUS			= 27,
	PLUS			= 24,
	LEFT			= 123,
	RIGHT			= 124,
	DOWN			= 125,
	UP				= 126,
	DIAMETER		= 2,
	SCALE			= 1,
	ROTATE			= 15,
	HEIGHT			= 4,
	ESC				= 53
};

// LINUX:
// enum e_key_codes{
// 	MOUSE_CLICK		= 1,
// 	SCROLL_UP		= 4,
// 	SCROLL_DOWN		= 5,
// 	MINUS			= 45,
// 	PLUS			= 61,
// 	LEFT			= 65361,
// 	RIGHT			= 65363,
// 	DOWN			= 65364,
// 	UP				= 65362,
// 	DIAMETER		= 100,
// 	SCALE			= 115,
// 	ROTATE			= 114,
// 	HEIGHT			= 104,
// 	ESC				= 65307
// };

void	user_input(t_mlx *mlx);

#endif