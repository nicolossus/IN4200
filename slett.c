#include "top_n_webpages.h"

void top_n_webpages(int num_webpages, int *num_involvements, int n){
	/*
	   The function for printing the top n webpages ranked from number of involvements.
	   All calculations have been split into a different function calc_top_n_webpages
	   that function also returns an index array of the top webpages.
	 */
	if(n>num_webpages) {
		n = num_webpages;
		printf("n cannot be larger than num_webpages, n is set equal to num_webpages %d\n",num_webpages);
	}

	int *top_results = (int *)malloc(n*sizeof(top_results));

	calc_top_n_webpages(num_webpages, num_involvements, top_results, n);

	for (size_t i = 0; i < n; i++) {
		printf("Ranking: %ld, Webpage number: %d, Number of involvements: %d\n", i+1, top_results[i], num_involvements[top_results[i]]);
	}
	free(top_results);
}


void calc_top_n_webpages(int num_webpages, int *num_involvements, int *top_results, int n){
	/*
	   This function is made because we dont want to print the results each time we benchmark
	   the top_n_webpages function. We have essentially made another function doing the same
	   thing that top_n_webpages were supposed to do, but this one is more test and benchmark
	   friendly because it will just return the results instead of printing them.
	 */

	int *dummy_array = (int *)malloc(num_webpages*sizeof(dummy_array));

	memcpy(dummy_array, num_involvements, num_webpages*sizeof(num_involvements));

	int top_webpage = 0;

  #if defined(_OPENMP)
	{
		int n_thread = omp_get_max_threads();
		int *temp_top_results = malloc(n*n_thread*sizeof(*temp_top_results));

    #pragma omp parallel
		{
			int thread_id = omp_get_thread_num();
			int rest = num_webpages%n_thread;

			for (int i = 0; i < n; i++) {
				//printf("%d", thread_id);
				if(thread_id<n_thread) {
					for (int j = thread_id*num_webpages/n_thread; j < (thread_id+1)*num_webpages/n_thread; j++) {
						if (dummy_array[top_webpage]<=dummy_array[j]) {
							top_webpage = j;
						}
					}
				}
				else{
					for (int j = thread_id*num_webpages/n_thread; j < num_webpages; j++) {
						if (dummy_array[top_webpage]<=dummy_array[j]) {
							top_webpage = j;
						}
					}
				}
				temp_top_results[n*thread_id+i] = top_webpage;
				dummy_array[top_webpage] = -1;
			}
      #pragma omp barrier
      #pragma omp master
			{
				memcpy(dummy_array, num_involvements, num_webpages*sizeof(num_involvements));
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n*n_thread; j++) {
						if (dummy_array[top_webpage] <= dummy_array[temp_top_results[j]]) {
							top_webpage = temp_top_results[j];
						}
					}
					top_results[i] = top_webpage;
					dummy_array[top_webpage] = -1;
				}
			}
		}
		free(temp_top_results);
	}
  #else
	{
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < num_webpages; j++) {
				top_webpage = MAXIDX(top_webpage, j, dummy_array);
			}
			top_results[i] = top_webpage;
			dummy_array[top_webpage] = -1;
		}
	}
  #endif

	free(dummy_array);
}
