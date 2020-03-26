#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(){
	clock_t t, t2;

	int N = 1e6;
	int stride = 10;
	double *A = malloc(N * sizeof *A);
	double *B = malloc(N * sizeof *B);
	double s = 50.0;

	for (int i=0; i<N; i++) {
		B[i] = (rand() % 100) + 1;
	}

	t = clock();
	for (int i=0; i<N; i++) {
		A[i] = s*B[i];
	}
	t = clock() - t;

	double t_tot = ((double)t)/CLOCKS_PER_SEC;
	int n_bytes = 2 * N * sizeof *A;

	printf("Regular loop\n");
	printf("Elapsed time: %f ms\n", 1000*t_tot);
	printf("Effective Memory bandwidth: %f GBytes per sec\n", n_bytes/t_tot/1e9);
	printf("GFlops: %f\n\n", N/t_tot/1e9);

	t2 = clock();
	for (int i=0; i<N; i+=stride) {
		A[i] = s*B[i];
	}
	t2 = clock() - t2;

	double t_tot2 = ((double)t2)/CLOCKS_PER_SEC;
	int n_bytes2 = ((double)n_bytes)/stride;

	printf("Loop with stride\n");
	printf("Elapsed time: %f ms\n", 1000*t_tot2);
	printf("Effective Memory bandwidth: %f GBytes per sec\n", n_bytes2/t_tot2/1e9);
	printf("GFlops: %f\n\n", N/((double)stride* t_tot2)/1e9);

	free(A);
	free(B);

	return 0;
}
