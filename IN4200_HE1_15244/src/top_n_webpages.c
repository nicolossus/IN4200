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
		printf("Webpage node %d ranks %d with %d involvements\n",
		       top_results[i], i+1, num_involvements[top_results[i]]);
	}
	free(top_results);
}
//=============================================================================


//=============================================================================
void calc_top_n_webpages(int num_webpages, int *num_involvements, int *top_results, int n)
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
{
	int *num_involvements_cpy = malloc(num_webpages * sizeof(*num_involvements_cpy));
	memcpy(num_involvements_cpy, num_involvements, num_webpages * sizeof(*num_involvements));
	int top_webpage = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<num_webpages; j++) {
			top_webpage = MAXIDX(top_webpage, j, num_involvements_cpy);
		}
		top_results[i] = top_webpage;
		num_involvements_cpy[top_webpage] = -1;
	}

	free(num_involvements_cpy);
}


//=============================================================================
void top_n_webpages_faster(int num_webpages, int *num_involvements, int n)
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
		printf("Webpage node %d ranks %d with %d involvements\n", top_webpage+1,
		       i+1, num_involvements_cpy[top_webpage]);
		num_involvements_cpy[top_webpage] = -1;
	}

	free(num_involvements_cpy);
}
//=============================================================================
