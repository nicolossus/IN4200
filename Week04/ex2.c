#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

void allocate_2d(double***, int, int);
void free_2d(double**);
void print_2d(double**, int, int);
void fill_2drandom(double**, int, int);
void matmul_2d(double**, double**, double**, int, int, int);
void printmat(double**, int, int);
void matmulfast_2d(double**, double**,double**, int, int, int);


int main(){
	clock_t t, t2;
	double **A, **B, **C, **D;
	int n, m, p;
	n = 100;
	m = 100;
	p = 100;

	allocate_2d(&A, n, m);
	allocate_2d(&B, m, p);
	allocate_2d(&C, n, p);
	allocate_2d(&D, n, p);

	fill_2drandom(A, n, m);
	fill_2drandom(B, m, p);

	/*
	      printf("A:\n");
	      printmat(A, n, m);

	      printf("B:\n");
	      printmat(B, m, p);
	 */

	t = clock();
	matmul_2d(A, B, C, n, m, p);
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC;

	t2 = clock();
	matmulfast_2d(A, B, D, n, m, p);
	t2 = clock() - t2;
	double t_tot2 = ((double)t2)/CLOCKS_PER_SEC;

	/*
	      printf("C:\n");
	      printmat(C, n, p);

	      printf("D:\n");
	      printmat(C, n, p);
	 */

	printf("Regular matmul\n");
	printf("Elapsed time: %f ms\n", 1e3*t_tot);

	printf("Fast matmul\n");
	printf("Elapsed time: %f ms\n", 1e3*t_tot2);


	//printf("Number of rows: %d\n", LEN(*A));
	//int row = sizeof(*A) / sizeof(*A[0]);
	//int column = sizeof(*A[0])/sizeof(A[0][0]);

	//printf("Number of rows: %d\n", row);
	//printf("Number of columns: %d\n", column);
	//printf("Number of columns: %d\n", LEN(A[0]));

	//printf("Number of rows: %d\n", LEN(B));
	//printf("Number of columns: %d\n", LEN(B[0]));

	free_2d(A);
	free_2d(B);
	free_2d(C);

	return 0;
}


void allocate_2d(double ***A, int nx, int ny){
	double **AA;
	AA = (double **)malloc(ny * sizeof(double *));
	AA[0] = (double *)malloc(ny * nx * sizeof(double)); // This is the actual underlying 1d array of size m * n.

	for (int i = 1; i < ny; i++) {
		AA[i] = &(AA[0][nx * i]);
	}

	*A = AA;
}

void fill_2drandom(double **A, int nx, int ny){
	//int nx = LEN(A);
	//int ny = LEN(A[0]);

	for (int i=0; i<nx; i++) {
		for (int j=0; j<ny; j++) {
			A[i][j] = (rand() % 100) + 1;
		}
	}


}

void free_2d(double **A){
	free(A[0]);
	free(A);
}

void print_2d(double **A, int nx, int ny){

	printf("[");
	for (int i=0; i<nx; i++) {
		printf("[");
		for (int j=0; j<ny; j++) {
			printf("%f\t", A[i][j]);
		}
		printf("]\n");
		printf("\n");
	}
	printf("]\n");
	printf("\n");


}

void printmat(double **A, int n, int m){
	for (size_t i = 0; i < n; ++i) {
		printf("| ");
		for (size_t j = 0; j < m; ++j) {
			printf("%.3f ", A[i][j]);
		}
		printf("|\n");
	}
}


// Assumes zero initialized C.
void matmulfast_2d(double **A, double **B, double **C, int n, int m, int p)
{
	int rest = p%4;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < p-rest; j+=4) { // Stride by 4.
			for (size_t k = 0; k < m; k++) { // Inner dim in A and B.
				C[i][j]   += A[i][k]*B[k][j];
				C[i][j+1] += A[i][k]*B[k][j+1];
				C[i][j+2] += A[i][k]*B[k][j+2];
				C[i][j+3] += A[i][k]*B[k][j+3];
			}
			// Rest loop.
			for (size_t j = p-rest; j < p; j++) {
				for (size_t k = 0; k < m; k++) {
					C[i][j]   += A[i][k]*B[k][j];
				}
			}
		}
	}

}


void matmul_2d(double **A, double **B, double **C, int n, int m, int p)
{
	for (size_t i = 0; i < n; i++) { // First dim in C.
		for (size_t j = 0; j < p; j++) { // Second dim in C.
			for (size_t k = 0; k < m; k++) { // Inner dim in A and B.
				C[i][j] += A[i][k]*B[k][j];
			}
		}
	}
}
