#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>


void printvec(double*, int);
void printmat(double**, int, int);

int main(int argc, const char * argv[]){
	int m = 3;
	int n = 2;

	// Allocate A, y, x
	double **A = (double **)malloc(m * sizeof(double *));
	A[0] = (double *)malloc(m * n * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < m; i++) {
		A[i] = &(A[0][n * i]);
	}

	double *y = malloc(n * sizeof *y);
	double *x = malloc(n * sizeof *x);

	// Fill A, y

	for (size_t i=0; i<m; i++) {
		for (size_t j=0; j<n; j++) {
			A[i][j] = (rand() % 100) + 1;
		}
	}

	for (size_t i=0; i<n; i++) {
		y[i] = (rand() % 100) + 1;
	}


	// Misc
	printf("A =\n");
	printmat(A, m, n);
	printf("y =\n");
	printvec(y, n);

	// Deallocate

	free(A[0]);
	free(A);

	free(y);
	free(x);


	return 0;
}




void dense_mat_vec(int m, int n, double *x, double *A, double *y)
{
	int i, j;
	for (i=0; i<m; i++)
	{
		double tmp = 0.;
		for (j=0; j<n; j++)
			tmp += A[i*n+j]*y[j];
		x[i] = tmp;
	}
}


void printmat(double **A, int m, int n){
	for (size_t i = 0; i < m; ++i) {
		printf("| ");
		for (size_t j = 0; j < n; ++j) {
			printf("%.3f ", A[i][j]);
		}
		printf("|\n");
	}
}

void printvec(double *v, int n){
	printf("| ");
	for (size_t i = 0; i < n; ++i) {
		printf("%.3f ", v[i]);
	}
	printf("|\n");
}
