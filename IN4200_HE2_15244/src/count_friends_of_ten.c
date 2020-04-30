#include "count_friends_of_ten.h"


//=============================================================================
int count_friends_of_ten2(int M, int N, int** v)
//----------------------------------------------------------------------------
// Find the total number of "triple-friends of 10" inside the input 2D array v,
// which is of dimension M x N
//
// Arguments
// ---------
// M: number of rows in matrix
// N: number of columns in matrix
// **v: allocated input 2D array (matrix)
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
			if (j>=2){
				friends += v[i][j] + v[i][j-1] + v[i][j-2] == 10;
			}
			// check vertical row
			if (i>=2){
				friends += v[i][j] + v[i-1][j] + v[i-2][j] == 10;
			}
			// check diagonal
			if (i>=2 && j>=2){
				friends += v[i][j] + v[i-1][j-1] + v[i-2][j-2] == 10;
			}
			// check anti-diagonal
			if (i<M-2 && j<N-2) {
				friends += v[i][j] + v[i+1][j+1] + v[i+2][j+2] == 10;
			}
		}//cols loop
	}//rows loop

	return friends;
}



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
// **v: allocated input 2D array (matrix)
//
// Returns
// -------
// The total number of "triple-friends of 10"
//----------------------------------------------------------------------------
{
	int tot_num_friends = 0;
	int k = 10;

	for (size_t i = 1; i < M-1; i++) {
		for (size_t j = 1; j < N-1; j++) {
			if (v[i-1][j-1] + v[i][j] + v[i+1][j+1] == k) {
				tot_num_friends++;
			}
			if (v[i+1][j-1] + v[i][j] + v[i-1][j+1] == k) {
				tot_num_friends++;
			}
			if (v[i-1][j] + v[i][j] + v[i+1][j] == k) {
				tot_num_friends++;
			}
			if (v[i][j-1] + v[i][j] + v[i][j+1] == k) {
				tot_num_friends++;
			}
		}
	}

	for (size_t i = 1; i < M-1; i++) {
		if (v[i-1][0] + v[i][0] + v[i+1][0] == k) {
			tot_num_friends++;
		}
		if (v[i-1][N-1] + v[i][N-1] + v[i+1][N-1] == k) {
			tot_num_friends++;
		}
	}

	for (size_t j = 1; j < N-1; j++) {
		if (v[0][j-1] + v[0][j] + v[0][j+1] == k) {
			tot_num_friends++;
		}
		if (v[M-1][j-1] + v[M-1][j] + v[M-1][j+1] == k) {
			tot_num_friends++;
		}
	}

	return tot_num_friends;
}
