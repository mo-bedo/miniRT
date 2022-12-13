#ifndef UI__H
# define UI__H

# include "main.h"

enum e_key_codes_common {
	MOUSE_CLICK		= 1,
	SCROLL_UP		= 4,
	SCROLL_DOWN		= 5
};

enum e_key_codes_macos {
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

enum e_key_codes_linux {
	MINUS_LINUX		= 45,
	PLUS_LINUX		= 61,
	LEFT_LINUX		= 65361,
	RIGHT_LINUX		= 65363,
	DOWN_LINUX		= 65364,
	UP_LINUX		= 65362,
	CLOSER_LINUX	= 45,
	FURTHER_LINUX	= 61,
	DIAMETER_LINUX	= 100,
	SCALE_LINUX		= 115,
	ROTATE_LINUX	= 114,
	HEIGHT_LINUX	= 104,
	TRANSLATE_LINUX	= 116,
	ESC_LINUX		= 65307
};

void	user_input(t_mlx *mlx);

#endif