#ifndef U_INVERT_MATRIX_H
# define U_INVERT_MATRIX_H

#include "main.h"
#include "matrices.h"

// t_matrix4	swap_two_rows(t_matrix4 obj, int row1, int row2);
t_matrix8	swap_two_rows8(t_matrix8 obj, int row1, int row2);
// t_matrix4	multiply_row_by_number(t_matrix4 obj, int row, float nb);
t_matrix8	multiply_row_by_number8(t_matrix8 obj, int row, float nb);
// t_matrix4	multiply_row_and_add_to_row(t_matrix4 obj, int row1, int row2, float nb);
t_matrix8	multiply_row_and_add_to_row8(t_matrix8 obj, int row1, int row2, float nb);
// int			find_row_with_max_value_at_column(t_matrix4 obj, int, int column);
int			find_row_with_max_value_at_column8(t_matrix8 obj, int, int column);
bool		compare_matrix_sum(t_matrix4 lhs, t_matrix4 rhs, double tolerance);
t_matrix8	augment_matrices(t_matrix4 lhs, t_matrix4 rhs);
bool	close_enough(float value1, float value2);

#endif
