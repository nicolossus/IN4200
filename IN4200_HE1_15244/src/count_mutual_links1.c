#include "count_mutual_links1.h"

//=============================================================================
int count_mutual_links1(int N, char **table2D, int *num_involvements)
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
// **table2D: web graph stored as 2D table
// *num_involvements: allocated array of length N for storing the number of
//										involvements per webpage
//
// Returns
// -------
// mutual_links: the total number of mutual webpage linkages
//----------------------------------------------------------------------------
{
	int mutual_links = 0;
	int counter = 0;

	#ifdef _OPENMP
	{
		// Parallelized version

		#pragma omp parallel for private(counter) reduction(+:mutual_links) schedule(auto)
		for (int i=0; i<N; i++) {
			counter = 0;  // Reset for each row (or webpage)
			for (int j=0; j<N; j++) {
				// Adds 1 to counter if column j has a direct link
				counter += table2D[i][j];
			}
			// Sum the number of involvements for a webpage
			for (size_t k=0; k<N; k++) {
				if (table2D[i][k]) { // True if table element is 1
					num_involvements[k] += counter-1;
				}
			}
			// Calculate contribution to the total number of mutual links
			// The formula follows from Pascal's triangle shifted down one row
			mutual_links += counter*(counter-1)*0.5;
		}
	}
	#else
	{
		// Serial version

		for (size_t i=0; i<N; i++) {
			counter = 0;  // Reset for each row (or webpage)
			for (size_t j=0; j<N; j++) {
				// Adds 1 to counter if column j has a direct link
				counter += table2D[i][j];
			}
			// Sum the number of involvements for a webpage
			for (size_t k=0; k<N; k++) {
				if (table2D[i][k]) { // True if table element is 1
					num_involvements[k] += counter-1;
				}
			}
			// Calculate contribution to the total number of mutual links
			// The formula follows from Pascal's triangle shifted down one row
			mutual_links += counter*(counter-1)*0.5;
		}
	}
 #endif

	return mutual_links;
}
//=============================================================================
