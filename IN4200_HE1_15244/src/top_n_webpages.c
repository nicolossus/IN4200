#include "top_n_webpages.h"

/*
   This program contains 3 functions:
                                1. top_n_webpages()
                                2. calc_top_n_webpages()
                                3. top_n_webpages_serial_faster()

   top_n_webpages() is a wrapper function for calc_top_n_webpages() which
   prints the results calculated by the latter. The rationale for doing the
   calculation of the top results in a seperate function were that it was
   deemed to verbose to print the results in the benchmark and test programs.
   Thus, the benchmark and test program call the calc_top_n_webpages()
   function.

   The 3rd function, top_n_webpages_serial_faster, both calculates and prints
   the results as serialized code. This is slightly faster, at least in serial,
   than the other procedure, since the complexity is reduced by a for-loop of n
   (the printout of the top results).
 */


//=============================================================================
void top_n_webpages(int num_webpages, int *num_involvements, int n)
//----------------------------------------------------------------------------
// Find the top n webpages with respect to the number of involvements in mutual
// linkages. Results are printed to screen.
//
// Arguments
// ---------
// num_webpages: number of webpages as int
// *num_involvements: pre-calculated num_involvements array
// n: the number of webpages to rank
//----------------------------------------------------------------------------
{
	if (n > num_webpages) {
		printf("n cannot be larger than num_webpages. n is set to %d\n", num_webpages);
		n = num_webpages;
	}

	printf("Top %d webpages:\n", n);

	// Allocate array for storing top n results
	int *top_results = malloc(n * sizeof(*top_results));

	// Call function that calculates the top results
	calc_top_n_webpages(num_webpages, num_involvements, top_results, n);

	// Print results to screen
	for (int i=0; i<n; i++) {
		printf("%d. w%d is involved %d times\n",
		       i+1, top_results[i]+1, num_involvements[top_results[i]]);
	}

	// Deallocate top results array
	free(top_results);
}
//=============================================================================


//=============================================================================
void calc_top_n_webpages(int num_webpages, int *num_involvements, int *top_results, int n)
//----------------------------------------------------------------------------
// Calculate the top n webpages with respect to the number of involvements in
// mutual linkages. Stores results in the top_results array.
//
// Arguments
// ---------
// num_webpages: number of webpages as int
// *num_involvements: pre-calculated num_involvements array
// *num_involvements: allocated top_results array for storing the top results
// n: the number of webpages to rank
//----------------------------------------------------------------------------
{

	if (n > num_webpages) {
		// Check also included here to ensure right use in benchmark and test
		// programs
		n = num_webpages;
	}

	// Copy the num_involvements array to avoid mutating the original
	int *num_involvements_cpy = (int *)malloc(num_webpages * sizeof(num_involvements_cpy));
	memcpy(num_involvements_cpy, num_involvements, num_webpages * sizeof(*num_involvements));

	int top_webpage = 0;

 #ifdef _OPENMP
	{
		// Parallelized version

		// Get upper bound on the number of threads that could be used, and use
		// to allocate sufficient storage dynamically for the top results across
		// all threads in the team formed at the subsequent active parallel region
		int Nt = omp_get_max_threads();
		int *top_results_tmp = (int *)malloc(n*Nt * sizeof(*top_results_tmp));
		int i, j;
		int maxval;

 #pragma omp parallel
		{
			int id = omp_get_thread_num();
			for (int i=0; i<n; i++) {
				if (id != Nt-1) {
					// Split list between threads
					maxval = -1;
					for (int j=id*num_webpages/Nt; j<(id+1)*num_webpages/Nt; j++) {
						// Find the index (corresponds to webpage node) with maximum number
						// of involvements
						if (num_involvements_cpy[top_webpage] < num_involvements_cpy[j]) {
							top_webpage = j;
						}
					}
				}
				else{
					// Same as above for remaining part of list
					for (int j=id*num_webpages/Nt; j<num_webpages; j++) {
						if (num_involvements_cpy[top_webpage] < num_involvements_cpy[j]) {
							top_webpage = j;
						}
					}
				}

				// Write top result to top_results array shared across threads
				top_results_tmp[id*n+i] = top_webpage;

				// Set number of involvements to -1 for the recently found top webpage
				// so that the same webpage is not found as top again
				num_involvements_cpy[top_webpage] = -1;
			}

 #pragma omp barrier
 #pragma omp master
			{
				// Recopy the num_involvements array since the previous copy is mutated
				memcpy(num_involvements_cpy, num_involvements, num_webpages*sizeof(num_involvements));
				for (int i=0; i<n; i++) {
					// For each webpage to rank
					for (int j=0; j<n*Nt; j++) {
						// Find the index (corresponds to webpage node) with maximum number
						// of involvements
						if (num_involvements_cpy[top_webpage] < num_involvements_cpy[top_results_tmp[j]]) {
							top_webpage = top_results_tmp[j];
						}
					}

					// Write current top result to top_results array
					top_results[i] = top_webpage;

					// Set number of involvements to -1 for the recently found top webpage
					// so that the same webpage is not found as top again
					num_involvements_cpy[top_webpage] = -1;
				}
			}
		}
		// Deallocate top results array used by all threads
		free(top_results_tmp);

	}
 #else
	{
		// Serial version

		for (size_t i=0; i<n; i++) {
			// For each webpage to rank
			for (size_t j=0; j<num_webpages; j++) {
				// Find the index (corresponds to webpage node) with maximum number
				// of involvements
				top_webpage = MAXIDX(top_webpage, j, num_involvements_cpy);
			}

			// Write current top result to top_results array
			top_results[i] = top_webpage;

			// Set number of involvements to -1 for the recently found top webpage
			// so that the same webpage is not found as top again
			num_involvements_cpy[top_webpage] = -1;
		}
	}
 #endif

	// Deallocate copy
	free(num_involvements_cpy);
}


//=============================================================================
void top_n_webpages_serial_faster(int num_webpages, int *num_involvements, int n)
//----------------------------------------------------------------------------
// Find the top n webpages with respect to the number of involvements in mutual
// linkages. Results are printed to screen.
//
// Arguments
// ---------
// num_webpages: number of webpages as int
// *num_involvements: pre-calculated num_involvements array
// n: the number of webpages to rank
//----------------------------------------------------------------------------
{
	if (n > num_webpages) {
		printf("n cannot be larger than num_webpages. n is set to %d\n", num_webpages);
		n = num_webpages;
	}
	printf("Top %d webpages:\n", n);

	// Copy the num_involvements array to avoid mutating the original
	int *num_involvements_cpy = malloc(num_webpages * sizeof(*num_involvements_cpy));
	memcpy(num_involvements_cpy, num_involvements, num_webpages * sizeof(*num_involvements));

	int top_webpage = 0;
	for (int i=0; i<n; i++) {
		// For each webpage to rank
		for (int j=0; j<num_webpages; j++) {
			// Find the index (corresponds to webpage node) with maximum number
			// of involvements
			top_webpage = MAXIDX(top_webpage, j, num_involvements_cpy);
		}

		// Print result to screen
		printf("%d. w%d is involved %d times\n",
		       i+1, top_webpage+1, num_involvements[top_webpage]);

		// Set number of involvements to -1 for the recently found top webpage
		// so that the same webpage is not found as top again
		num_involvements_cpy[top_webpage] = -1;
	}

	// Deallocate copy
	free(num_involvements_cpy);
}
//=============================================================================
