#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
int main (int nargs, char **args) {
	clock_t t1, t2;
	int N = 1e8;
	double *a = calloc(N, sizeof *a);
	double *b = calloc(N, sizeof *b);

	for (size_t i=0; i<N; i++) {
		a[i] = (rand() % 100) + 1;
		b[i] = (rand() % 100) + 1;
	}

	// Timing with regular clock

	t1 = clock();
	double dotp1 = 0;
	for (size_t i = 0; i < N; i++) {
		dotp1 += a[i] * b[i];
	}
	t1 = clock() - t1;
	double t1_tot = ((double)t1)/CLOCKS_PER_SEC;
	printf("serial loop took %f milliseconds to execute \n", 1000*t1_tot);

	double dotp2 = 0;
	t2 = clock();
	#pragma omp parallel for reduction (+ : dotp2)
	for (size_t i = 0; i < N; i++) {
		dotp2 += a[i] * b[i];
	}
	t2 = clock() - t2;
	double t2_tot = ((double)t2)/CLOCKS_PER_SEC;
	printf("parallelized loop took %f milliseconds to execute \n", 1000*t2_tot);

	// Timing with omp
	/*
	      double dotp3 = 0;
	      double t1_omp = omp_get_wtime();
	      for (size_t i = 0; i < N; i++) {
	              dotp3 += a[i] * b[i];
	      }
	      t1_omp = omp_get_wtime() - t1_omp;
	      printf("omp time - serial loop took %f milliseconds to execute \n", 1000*t1_omp);

	      double dotp4 = 0;
	      double t2_omp = omp_get_wtime();
	 #pragma omp parallel for reduction (+ : dotp4)
	      for (size_t i = 0; i < N; i++) {
	              dotp4 += a[i] * b[i];
	      }
	      t2_omp = omp_get_wtime() - t2_omp;
	      printf("omp time - parallelized loop took %f milliseconds to execute \n", 1000*t2_omp);
	 */

	free(a);
	free(b);

	return 0;
}
