#include "count_mutual_links2.h"

//=============================================================================
int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
//----------------------------------------------------------------------------
// Count the total number of mutual webpage linkage occurrences, as well as the
// number of times that a webpage is involved as outbound for the mutual web
// linkages.
//
// Note that the num_involvements array used to store the number of
// involvements is assumed to be already allocated.
//
// Arguments
// ---------
// N: number of webpages as int
// N_links: number of links as int
// *row_ptr: web graph stored in CRS format
// *col_idx: web graph stored in CRS format
// *num_involvements: allocated array of length N for storing the number of
//										involvements per webpage
//
// Returns
// -------
// mutual_links: the total number of mutual webpage linkages
//----------------------------------------------------------------------------
{
	int mutual_links = 0;
	int counter;

	#if defined(_OPENMP)
	{
		// Parallelized version

		// Array reduction is only possible with OpenMP 4.5, which is not installed
		// on IFI's student server. The code runs with the pragma declaration
		// without num_involvements[:N] in the reduction, but this does not always
		// yield the correct results. To run on IFI machines, change which #pragma
		// is commented out

		//#pragma omp parallel for private(counter) reduction(+:mutual_links)
		 #pragma omp parallel for private(counter) reduction(+:mutual_links, num_involvements[:N])
		for (int i = 0; i < N; i++) {
			// Mutual linkage occurences in current row
			counter = row_ptr[i+1] - row_ptr[i];

			// Calculate contribution to the total number of mutual links
			// The formula follows from Pascal's triangle shifted down one row
			mutual_links += counter*(counter-1)*0.5;

			// Sum the number of involvements for a webpage
			// row_start = row_ptr[i] and row_end = row_ptr[i+1]
			for (int j = row_ptr[i]; j < row_ptr[i+1]; j++) {
				num_involvements[col_idx[j]] += counter-1;
			}
		}

	}
	#else
	{
		// Serial version

		for (size_t i = 0; i < N; i++) {
			// Mutual linkage occurences in current row
			counter = row_ptr[i+1] - row_ptr[i];

			// Calculate contribution to the total number of mutual links
			// The formula follows from Pascal's triangle shifted down one row
			mutual_links += counter*(counter-1)*0.5;

			// Sum the number of involvements for a webpage
			// row_start = row_ptr[i] and row_end = row_ptr[i+1]
			for (size_t j = row_ptr[i]; j < row_ptr[i+1]; j++) {
				num_involvements[col_idx[j]] += counter-1;
			}
		}
	}
	#endif

	return mutual_links;
}
//=============================================================================
