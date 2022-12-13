#ifndef U__H
# define U__H

# include "main.h"
# include "utils/u_compare.h"
# include "utils/u_conversion.h"
# include "utils/u_identify.h"
# include "utils/u_rotate_vector.h"
# include "utils/u_vector_math.h"
# include "utils/u_vector_operators.h"

void	ft_putstr(char *s);
void	*ft_calloc(size_t count, size_t size);
void	initialize_quaternion(t_wxyz *q, float w, t_xyz vector);
t_wxyz	multiply_quaternion(t_wxyz q1, t_wxyz q2);

#endif
