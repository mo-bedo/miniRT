#include "main.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

bool	ft_is_digit(int c)
{
	if (c && c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	ft_is_space(char c)
{
	if (c && (c == ' ' || c == '\f' || c == '\n'
			|| c == '\r' || c == '\t' || c == '\v'))
		return (true);
	return (false);
}
