#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(){

	int N = 100;

	// Allocate A, B, y
	double **A = (double **)malloc(N * sizeof(double *));
	A[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.

	for (size_t i = 1; i < N; i++) {
		A[i] = &(A[0][N * i]);
	}

	double *B = malloc(N * sizeof *B);
	double *y = malloc(N * sizeof *y);

	// Fill A, B

	for (size_t i=0; i<N; i++) {
		for (size_t j=0; j<N; j++) {
			A[i][j] = (rand() % 100) + 1;
		}
	}

	for (size_t i=0; i<N; i++) {
		B[i] = (rand() % 100) + 1;
	}

	// Unroll and jam

	int rest = N % 4;
	for (size_t j=0; j<N-rest; j+=4) {
		for (size_t i=0; i<=j; i++) {
			y[j] += A[j][i]*B[i];
			y[j+1] += A[j+1][i]*B[i];
			y[j+2] += A[j+2][i]*B[i];
			y[j+3] += A[j+3][i]*B[i];
		}
	}

	// Rest loop
	for (size_t j=N-rest; j<N; j++) {
		for (size_t i=0; i<=j; i++) {
			y[j] += A[j][i]*B[i];
		}
	}


	free(A[0]);
	free(A);
	free(B);
	free(y);

	return 0;
}
