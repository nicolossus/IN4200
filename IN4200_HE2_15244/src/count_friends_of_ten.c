#include "count_friends_of_ten.h"

//=============================================================================
int count_friends_of_ten(int M, int N, int** v)
//----------------------------------------------------------------------------
// Find the total number of "triple-friends of 10" inside the input 2D array v,
// which is of dimension M x N
//
// Arguments
// ---------
// M: number of rows in matrix
// N: number of columns in matrix
// **v: input 2D array (matrix)
//
// Returns
// -------
// The total number of "triple-friends of 10"
//----------------------------------------------------------------------------
{
	int friends = 0;
	// iterate the rows
	for (int i=0; i<M; i++) {
		// iterate the columns
		for (int j=0; j<N; j++){
			// check horizontal row
			if (j<N-2)
			{
				friends += v[i][j] + v[i][j+1] + v[i][j+2] == 10;
			}
			// check vertical row
			if (i<M-2)
			{
				friends += v[i][j] + v[i+1][j] + v[i+2][j] == 10;
			}
			// check diagonal
			if (i<M-2 && j<N-2)
			{
				friends += v[i][j] + v[i+1][j+1] + v[i+2][j+2] == 10;
			}
			// check anti-diagonal
			if (i<M-2 && j>=2)
			{
				friends += v[i][j] + v[i+1][j-1] + v[i+2][j-2] == 10;
			}
		}
	}
	return friends;
}
