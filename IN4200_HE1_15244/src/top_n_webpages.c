#include "top_n_webpages.h"

//=============================================================================
void top_n_webpages(int num_webpages, int *num_involvements, int n)
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
{
	if (n > num_webpages) {
		printf("n cannot be larger than num_webpages. n is set to %d\n", num_webpages);
		n = num_webpages;
	}
	int *top_results = malloc(n * sizeof(*top_results));
	calc_top_n_webpages(num_webpages, num_involvements, top_results, n);

	for (int i=0; i<n; i++) {
		printf("%d. w%d is involved %d times\n",
		       i+1, top_results[i]+1, num_involvements[top_results[i]]);
	}
	free(top_results);
}
//=============================================================================


//=============================================================================
void calc_top_n_webpages(int num_webpages, int *num_involvements, int *top_results, int n)
//----------------------------------------------------------------------------
// MIN
//----------------------------------------------------------------------------
{

	if (n > num_webpages) {
		printf("n cannot be larger than num_webpages. n is set to %d\n", num_webpages);
		n = num_webpages;
	}

	int *num_involvements_cpy = (int *)malloc(num_webpages * sizeof(num_involvements_cpy));
	memcpy(num_involvements_cpy, num_involvements, num_webpages * sizeof(*num_involvements));
	int top_webpage = 0;

 #if defined(_OPENMP)
	{
		int Nt = omp_get_max_threads();
		int *top_results_tmp = malloc(n*Nt * sizeof(*top_results_tmp));

 #pragma omp parallel
		{
			int id = omp_get_thread_num();
			for (int i=0; i<n; i++) {
				if (id<Nt) {
					for (int j=id*num_webpages/Nt; j<(id+1)*num_webpages/Nt; j++) {
						if (num_involvements_cpy[top_webpage]<=num_involvements_cpy[j]) {
							top_webpage = j;
						}
					}
				}
				else{
					for (int j=id*num_webpages/Nt; j<num_webpages; j++) {
						if (num_involvements_cpy[top_webpage]<=num_involvements_cpy[j]) {
							top_webpage = j;
						}
					}
				}
				top_results_tmp[id*n+i] = top_webpage;
				num_involvements_cpy[top_webpage] = -1;
			}

 #pragma omp barrier
 #pragma omp master
			{
				memcpy(num_involvements_cpy, num_involvements, num_webpages*sizeof(num_involvements));
				for (int i = 0; i<n; i++) {
					for (int j = 0; j<n*Nt; j++) {
						if (num_involvements_cpy[top_webpage] <= num_involvements_cpy[top_results_tmp[j]]) {
							top_webpage = top_results_tmp[j];
						}
					}
					top_results[i] = top_webpage;
					num_involvements_cpy[top_webpage] = -1;
				}
			}
		}
		free(top_results_tmp);
	}
 #else
	{
		for (size_t i=0; i<n; i++) {
			for (size_t j=0; j<num_webpages; j++) {
				top_webpage = MAXIDX(top_webpage, j, num_involvements_cpy);
			}
			top_results[i] = top_webpage;
			num_involvements_cpy[top_webpage] = -1;
		}
	}
 #endif

	free(num_involvements_cpy);
}


//=============================================================================
void top_n_webpages_serial_faster(int num_webpages, int *num_involvements, int n)
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
{
	if (n > num_webpages) {
		printf("n cannot be larger than num_webpages. n is set to %d\n", num_webpages);
		n = num_webpages;
	}
	int *num_involvements_cpy = malloc(num_webpages * sizeof(*num_involvements_cpy));
	memcpy(num_involvements_cpy, num_involvements, num_webpages * sizeof(*num_involvements));
	int top_webpage = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<num_webpages; j++) {
			top_webpage = MAXIDX(top_webpage, j, num_involvements_cpy);
		}
		printf("%d. w%d is involved %d times\n",
		       i+1, top_webpage+1, num_involvements[top_webpage]);
		num_involvements_cpy[top_webpage] = -1;
	}

	free(num_involvements_cpy);
}
//=============================================================================
