/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_bonus.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 17:42:31 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/11 18:16:14 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_BONUS_H
# define UI_BONUS_H

# include "main_bonus.h"

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
	CLOSER			= 27,
	FURTHER			= 24,
	DIAMETER		= 2,
	SCALE			= 1,
	ROTATE			= 15,
	HEIGHT			= 4,
	TRANSLATE		= 17,
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