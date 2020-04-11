#include "count_mutual_links1.h"

//=============================================================================
int count_mutual_links1(int N, char **table2D, int *num_involvements)
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
{
	int mutual_links = 0;
	int counter = 0;
	int *involved_idx = calloc((N), sizeof(*involved_idx));

	#if defined(_OPENMP)
	{
		#pragma omp parallel for private(counter) reduction(+:mutual_links, involved_idx[:N], num_involvements[:N])
		{
			for (size_t i=0; i<N; i++) {
				memset(involved_idx, 0, N*sizeof(*involved_idx));
				counter = 0;
				for (size_t j=0; j<N; j++) {
					if (table2D[i][j]) {
						counter++;
						involved_idx[j] = j+1;
					}
				}
				for (int k=0; k<N; k++) {
					if (involved_idx[k]) {
						num_involvements[k] += counter-1;
					}
				}
				mutual_links += counter*(counter-1)*0.5;
			}
		}
	}
	#else
	{
		for (size_t i=0; i<N; i++) {
			memset(involved_idx, 0, N*sizeof(*involved_idx));
			counter = 0;
			for (size_t j=0; j<N; j++) {
				if (table2D[i][j]) {
					counter++;
					involved_idx[j] = j+1;
				}
			}
			for (int k=0; k<N; k++) {
				if (involved_idx[k]) {
					num_involvements[k] += counter-1;
				}
			}
			mutual_links += counter*(counter-1)*0.5;
		}
	}
 #endif

	free(involved_idx);

	return mutual_links;
}
//=============================================================================
