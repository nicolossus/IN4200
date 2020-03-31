#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
int main (int nargs, char **args) {
	int N = 1e8;
	int *a = calloc(N, sizeof *a);
	int *b = calloc(N, sizeof *b);
	int *c = calloc(N, sizeof *c);

	for (size_t i=0; i<N; i++) {
		b[i] = (rand() % 100) + 1;
		c[i] = (rand() % 100) + 1;
	}


	#pragma omp parallel for
	for (size_t i=0; i<N; i++)
		a[i] = b[i] + c[i];

	free(a);
	free(b);
	free(c);

	return 0;
}
