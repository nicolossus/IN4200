#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(){

	double ***A;
	int l, m, n;
	l = m = n = 5;

	A = (double ***)malloc(l * sizeof(double **) * sizeof(double *));
	A[0] = (double **)malloc(l * m * sizeof(double *));
	A[0][0] = (double *)malloc(l * m * n * sizeof(double)); // This is the actual underlying 1d array of size l * m * n.

	for (int i = 1; i < l; i++) {
		A[i] = &(A[0][m * i]);
	}

	for (int j=1; j<l*m; j++) {
		A[0][j] = &(A[0][0][n * j]);
	}

	// Fill array
	for (int i=0; i<l; i++) {
		for (int j=0; j<m; j++) {
			for (int k=0; k<n; k++) {
				A[i][j][k] = i+j+k;
			}
		}
	}

	// Print array
	//printf("[");
	for (int i=0; i<l; i++) {
		//printf("[");
		for (int j=0; j<m; j++) {
			//printf("[");
			for (int k=0; k<n; k++) {
				printf("%f\t", A[i][j][k]);
			}
			//printf("]\n");
			printf("\n");
		}
		//printf("]\n");
		printf("\n");
	}
	//printf("]");

	return 0;
}
