//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <omp.h>
#define MAXIDX(oldidx, i, arr) (((arr[oldidx]) > (arr[i])) ? (oldidx) : (i))

struct Compare {int val; int index; };
#pragma omp declare reduction(maximum : struct Compare : omp_out = omp_in.val > omp_out.val ? omp_in : omp_out)

void printvec(int*, int);

int main(){

	int n = 5;
	int m = 10;
	int *A = malloc(n * sizeof(*A));
	int *B = malloc(n * sizeof(*B));

	// Fill B = {0,1,2,3,4,5,6,7,8,9}
	for (int i=0; i<m; i++) {
		B[i] = i;
	}

	printf("B = ");
	printvec(B, m);


	int index = 0;
	int max = 0;
	int i, k;



#pragma omp parallel for shared(A, B)
	for (k=0; k<n; k++) {
		for (i = 0; i < m; i++) {
			if (B[i] > max) {
					 #pragma omp critical
				{
					max = B[i];
					index = i;
				}
			}
		}
		A[k] = index;
		B[index] = -1;
	}

	printf("A = ");
	printvec(A, n);

	free(A);
	free(B);

	return 0;
}

void printvec(int *v, int n)
{
	printf("| ");
	for (size_t i = 0; i < n; ++i) {
		printf("%d ", v[i]);
	}
	printf("|\n");
}
