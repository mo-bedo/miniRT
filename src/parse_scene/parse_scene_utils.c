#include "parse_scene/parse_scene_utils.h"
#include "utils.h"

static void	skip_chars_of_parsed_number(char **str)
{
	while (**str && ft_is_space(**str))
		*str += 1;
	while (**str && **str == '-')
		*str += 1;
	while (**str && ft_is_digit(**str))
		*str += 1;
	if (**str == '.')
	{
		*str += 1;
		while (**str && ft_is_digit(**str))
			*str += 1;
	}
	if (**str && **str == ',')
		*str += 1;
}

int	parse_int(char **str, int min, int max)
{
	int	number;

	number = ft_atoi(*str);
	if (number < min || number > max)
		error_message_and_exit("integer input error");
	skip_chars_of_parsed_number(str);
	return (number);
}

float	parse_float(char **str, int min, int max)
{
	float	number;

	number = ft_atof(*str);
	if (number < min || number > max)
		error_message_and_exit("float value input error");
	skip_chars_of_parsed_number(str);
	return (number);
}

// static int	create_color(int transparancy, int red, int green, int blue)
// {
// 	return (transparancy << 24 | red << 16 | green << 8 | blue);
// }

// mogelijk optie om rgb meteen naar 1 int te parsen (zie functie create_color hierboven)
// dan kan de struct t_rgb weg.
t_rgb	parse_rgb(char **str)
{
	t_rgb	rgb;

	rgb.red = parse_int(str, MIN_COLOR, MAX_COLOR);
	rgb.blue = parse_int(str, MIN_COLOR, MAX_COLOR);
	rgb.green = parse_int(str, MIN_COLOR, MAX_COLOR);
	return (rgb);
}

t_xyz	parse_xyz(char **str, int min, int max)
{
	t_xyz	xyz;

	xyz.x = parse_float(str, min, max);
	xyz.y = parse_float(str, min, max);
	xyz.z = parse_float(str, min, max);
	return (xyz);
}
