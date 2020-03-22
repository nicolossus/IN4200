/*
   When assigning values to the entries of a m × n matrix, it is common
   to use a nested for-loop with the outer index looping over the rows
   and the inner index looping over the columns. Does it matter if the
   sequence of these two loops is swapped? Write a C program to test
   your hypothesis.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void fill_cols_first(double**, int, int);
void fill_rows_first(double**, int, int);

int main(){

	clock_t t_cols, t_rows;

	double **A;
	int m, n;
	m = n = 10000;

	A = (double **)malloc(m * sizeof(double *));
	A[0] = (double *)malloc(m * n * sizeof(double)); // This is the actual underlying 1d array of size m * n.

	for (int i = 1; i < m; i++) {
		A[i] = &(A[0][n * i]);
	}

	// Benchmark
	int Nrep;
	Nrep = 10;

	// Fill columns first
	t_cols = clock();
	for (int i=0; i<Nrep; i++) {
		fill_cols_first(A, m, n);
	}
	t_cols = clock() - t_cols;
	double time_taken_cols = ((double)t_cols)/CLOCKS_PER_SEC/Nrep;
	printf("fill_cols_first() took %f seconds to execute \n", time_taken_cols);

	// Fill rows first
	t_rows = clock();
	for (int i=0; i<Nrep; i++) {
		fill_rows_first(A, m, n);
	}
	t_rows = clock() - t_rows;
	double time_taken_rows = ((double)t_rows)/CLOCKS_PER_SEC/Nrep;
	printf("fill_rows_first() took %f seconds to execute \n", time_taken_rows);


	free(A[0]);
	free(A);

	return 0;
}

void fill_cols_first(double **arr, int rows, int cols){
	for (int j=0; j<cols; j++) {
		for (int i=0; i<rows; i++) {
			arr[i][j] = i*j;
		}
	}
}

void fill_rows_first(double **arr, int rows, int cols){
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			arr[i][j] = i*j;
		}
	}
}
