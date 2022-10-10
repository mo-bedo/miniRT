/* functies
	join 2 matrices columnwise
	seperate matrix into 2 around specified column

*/

#include "../../inc/utils/matrices.h"
#include "../../inc/utils/u_invert_matrix.h"
#include <math.h>



/////////// INVERT LOGARITME ////////////////
/*
| a1	a2		a3		1 		0		0 |	
| b1	b2		b3		0 		1		0 |	
| c1	c2		c3		0 		0		1 |	

Dmv elementary row operatios het volgende bereiken: (diagonaal op 1 en rest op 0)
a1 = 1	;	b1 en c1  = 0	; 	a2 en a3 = 0; 
b2 = 1	;	c2 naar 0		;	b3 = 0;
c3 = 1	;	

Dus eerst de diagonaalwaarde op 1 beginnend op 0,0, dan in dezelfde column de waardes daaronder naar 0, 
en dan in dezlefde rij de waardes rechts naar 0. en dan naar diagonaal waarde 1,1 naar 1 etc.
*/

// Turn matrix8 into matrix4 by taking the leftside of matrix8 (which is the inverted matrix)
t_matrix4	seperate_matrix(t_matrix8 obj)
{
	t_matrix4	ret;
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret.value[i][j] = obj.value[i][j + 4];
			j++;
		}
		i++;
	}
	return (ret);
}

bool	left_matrix_is_identity(t_matrix8 obj)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i != j)
				if (obj.value[i][j] != 0)
					return (false);
			if (i == j)
				if (obj.value[i][j] != 1)
					return (false);
			
			j++;
		}
		i++;
	}
	return (true);
}

t_matrix4	invert_matrix(t_matrix4 obj)
{
	// Als eerste een identity matrix toevoegen aan de huidige
	t_matrix4	identity;
	t_matrix8	A;

	identity = set_matrix_to_identity(identity);
	A = augment_matrices(obj, identity);

	// Current row en current column
	int	cRow;
	int	cCol;
	int	maxLoop = 100;		// later op 100
	int	i;
	bool	complete;
	double multi_factor;

	complete = false;
	i = 0;
	while (!complete && (i < maxLoop))
	{
		int diagnol_index = 0;
		while (diagnol_index < 4)	// dit loopt over de diagonaal van de matrix en zet ze op 1 
		{
			
			cRow = diagnol_index;
			cCol = diagnol_index;

			// vind de index van de hoogste waarde in de huidige column
			int maxIndex = find_row_with_max_value_at_column8(A, cRow, cCol);

			// als maxwaarde niet in de huidige rij zit wissel ze ze om
			if (maxIndex != cRow)
				A = swap_two_rows8(A, cRow, maxIndex);

			// zorg dat waarde cRow, cCol 1 is
			if (A.value[cRow][cCol] != 1)
			{
				multi_factor = 1.0 / A.value[cRow][cCol];

				// printf("waarde die naar 1 moet = %f mulitfactor = %f\n", A.value[cRow][cCol], multi_factor);
				A = multiply_row_by_number8(A, cRow, multi_factor);
				// print_matrix8(A);
			}

				/////// TOT HIER WERKT HIJ GOED ///////////


				//	dan moeten alles in de column eronder naar 0
				// dus rowindex is ervoor om de rest van de column eronder te bekijken
			int rowIndex;
				
			rowIndex = cRow + 1;
			while (rowIndex < 4)
			{
				// als het element al 0 is kunnen we door
				if (!close_enough(A.value[rowIndex][cCol], 0.0))
				{
					// Obtain the element to work with from the matrix diagonal.
					// As we aim to set all the diagonal elements to one, this should
					// always be valid for a matrix that can be inverted.
					int	row_one_index = cCol;

					float	current_element_value = A.value[rowIndex][cCol];

					float	row_one_value = A.value[row_one_index][cCol];
					// Als deze 0 is kunnen we door
					if (!close_enough(row_one_value, 0.0))
					{
						// bereken correctie factor om waarde om [rowindex][cCol] naar 0 te krijgen
						float	correctionFactor = - (current_element_value / row_one_value);

						A = multiply_row_and_add_to_row8(A, row_one_index, rowIndex, correctionFactor);
					}
				}
				rowIndex++;
			}

			// dan moet de row (rechtsboven) ook naar 0
			int col_index;
			col_index = cCol + 1;

			// loopt naar rechts
			while (col_index < 4)
			{
				
				if (!close_enough(A.value[cRow][col_index], 0.0))
				{
					int	row_one_index = col_index;

					float 	current_element_value = A.value[cRow][col_index];

					float	row_one_value = A.value[row_one_index][col_index];

					if (!close_enough(row_one_value, 0.0))
					{

						float correction_factor = - (current_element_value / row_one_value);

						A = multiply_row_and_add_to_row8(A, row_one_index, cRow, correction_factor);

					}


				}	
				col_index++;
			}




			diagnol_index++;
		}

		if (left_matrix_is_identity (A))
			break ;
		i++;
	}
	t_matrix4 ret;

	ret = seperate_matrix(A);
	return (ret);
}


////////////// INVERT MATH ////////////////

t_matrix8	augment_matrices(t_matrix4 lhs, t_matrix4 rhs)
{
	int	i;
	int	j;
	t_matrix8	ret;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret.value[i][j] = lhs.value[i][j];
			ret.value[i][j + 4] = rhs.value[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}


t_matrix4	swap_two_rows(t_matrix4 obj, int row1, int row2)
{
	float	swap[4];
	int		i;

	i = 0;
	while (i < 4)
	{
		swap[i] = obj.value[row1][i];
		obj.value[row1][i] = obj.value[row2][i];
		obj.value[row2][i] = swap[i];
		i++;
	}
	return (obj);
}

t_matrix8	swap_two_rows8(t_matrix8 obj, int row1, int row2)
{
	float	swap[8];
	int		i;

	i = 0;
	while (i < 8)
	{
		swap[i] = obj.value[row1][i];
		obj.value[row1][i] = obj.value[row2][i];
		obj.value[row2][i] = swap[i];
		i++;
	}
	return (obj);
}

t_matrix4	multiply_row_by_number(t_matrix4 obj, int row, float nb)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		obj.value[row][i] = obj.value[row][i] * nb;
		i++;
	}
	return (obj);
}

t_matrix8	multiply_row_by_number8(t_matrix8 obj, int row, float nb)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		obj.value[row][i] = obj.value[row][i] * nb;
		i++;
	}
	return (obj);
}

// Mulitplies row1 by nb and adds result to row2
t_matrix4	multiply_row_and_add_to_row(t_matrix4 obj, int row1, int row2, float nb)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		obj.value[row2][i] += obj.value[row1][i] * nb;
		i++;
	}
	return (obj);
}

t_matrix8	multiply_row_and_add_to_row8(t_matrix8 obj, int row1, int row2, float nb)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		obj.value[row2][i] += obj.value[row1][i] * nb;
		i++;
	}
	return (obj);
}

// 	Max[0] holds value, max[1] holds row index
// 	Finds max value starting from row
int		find_row_with_max_value_at_column(t_matrix4 obj, int row, int column)
{
	float	max[2];

	max[0] = obj.value[row][column];
	max[1] = row;
	row++;
	while (row < 4)
	{
		if (max[0] < obj.value[row][column])
		{
			max[0] = obj.value[row][column];
			max[1] = row;
		}
		row++;
	}
	return (max[1]);

}

int		find_row_with_max_value_at_column8(t_matrix8 obj, int row, int column)
{
	float	max[2];

	max[0] = obj.value[row][column];
	max[1] = row;
	row++;
	while (row < 4)
	{
		if (max[0] < obj.value[row][column])
		{
			max[0] = obj.value[row][column];
			max[1] = row;
		}
		row++;
	}
	return (max[1]);

}

// van video code:  this-> = rhs en input is lhs. Dus input - this->
// Functions compares all elements of the two matrices and returns true
// if the difference in cumulative sum is lower then the tolerance
bool	compare_matrix_by_sum(t_matrix4 lhs, t_matrix4 rhs, double tolerance)
{
	int		i;
	int		j;
	double	cumulative_sum;

	cumulative_sum = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		{
			cumulative_sum += ((lhs.value[i][j] - rhs.value[i][j]) * (lhs.value[i][j] - rhs.value[i][j]));
			j++;
		}
		i++;
	}		
	
										// total elements -1 ( = aantal rows * aantal columns - 1)
	cumulative_sum = sqrt(cumulative_sum / ((4 * 4) - 1));
	if (cumulative_sum <= tolerance)
		return (true);
	else
		return (false);
}

bool	close_enough(float value1, float value2)
{
	return (fabs(value1 - value2) < 1e-9);
}

// Compares 2 matrices element by element and returns true if they are equal (or close enough < 1e-9)
bool	compare_matrix_by_element(t_matrix4 lhs, t_matrix4 rhs)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		{
			if (!(fabs(lhs.value[i][j] - rhs.value[i][j]) < 1e-9))
				return (false);
			j++;
		}
		i++;
	}				
	return (true);
}




// int main()
// {
// 	t_matrix4 c;
// 	t_matrix4 b;
// 	t_matrix4 m;
	
// 	int x = 3;
// 	for (int i = 0; i < 2; i++)
// 	{
// 		x++;
// 		for (int j = 0; j < 4; j++)
// 		{
// 			x+= 3; 
// 			b.value[i][j] = x;
// 		}
	
// 	}
// 	x = -15;
// 	for (int i = 2; i < 4; i++)
// 	{
// 		x++;
// 		for (int j = 0; j < 4; j++)
// 		{
// 			x-= 3; 
// 			b.value[i][j] = x;
// 		}
	
// 	}

// 	printf("input matrix: \n");
// 	print_matrix(b);

// 	invert_matrix(b);











	// x = 5;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x-= 1; 
	// 		c.value[i][j] = x;
	// 	}
	
	// }
	// print_matrix(c);
	// print_matrix(b);
	// t_matrix8	big = augment_matrices(c, b);
	// print_matrix8(big);
	

	// b = multiply_row_and_add_to_row(b, 0, 1, 2);
	// print_matrix(b);
	

	// x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x--;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x-= 3; 
	// 		c.value[i][j] = x;
	// 	}
	
	// }

			////////////////// TEST MAX VALUE IN ROW	////////////////
	// int	x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		c.value[i][j] = x;
	// 	}
	// }
	// x = 5;	
	// for (int i = 0; i < 4; i++)
	// {
	// 	x--;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x-= 3; 
	// 		b.value[i][j] = x;
	// 	}
	// }	

	// print_matrix(b);
	// printf("row with max value in column 2 = %i\n", find_row_with_max_value_at_column(b, 2, 2));
	// print_matrix(c);
	// printf("row with max value in column 2 = %i\n\n", find_row_with_max_value_at_column(c, 0, 2));



			////////////////// TEST SWAP VALUE IN ROW	////////////////
	// x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		c.value[i][j] = x;
	// 	}
	// }
	// t_matrix8 A = augment_matrices(c, c);
	// print_matrix8(A);
	// A = swap_two_rows8(A, 1, 2);
	// print_matrix8(A);

	// print_matrix(c);
	// c = swap_two_rows(c, 1, 2);
	// print_matrix(c);




			////////////////// TEST COMPARE BY ELEMENT	////////////////
	// 	int x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		b.value[i][j] = x;
	// 	}
	
	// }
	// x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		c.value[i][j] = x;
	// 	}
	
	// }
	// print_matrix(c);
	// print_matrix(b);
	// if (compare_matrix_by_element(b, c))
	// 	printf("Should print because they have same elements over all\n");
	// b.value[0][0] = 2;
	// print_matrix(c);
	// print_matrix(b);
	// if (!compare_matrix_by_element(b, c))
	// 	printf("Should print because they do not have same elements over all\n");

		/////////////////// AUGMENT MATRICES /////////////////////
	// int x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		b.value[i][j] = x;
	// 	}
	
	// }
	// x = 5;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x-= 1; 
	// 		c.value[i][j] = x;
	// 	}
	
	// }
	// print_matrix(c);
	// print_matrix(b);
	// t_matrix8	big = augment_matrices(c, b);
	// print_matrix8(big);

// }

