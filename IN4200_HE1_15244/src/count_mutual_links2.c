#include "count_mutual_links2.h"

//=============================================================================
int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
{
	int mutual_links = 0;
	int counter;

	for (int i = 0; i < N; i++) {
		counter = row_ptr[i+1] - row_ptr[i];
		mutual_links += counter*(counter-1)*0.5;
		for (int j = row_ptr[i]; j < row_ptr[i+1]; j++) {
			num_involvements[col_idx[j]] += counter-1;
		}
	}


	return mutual_links;
}
//=============================================================================
