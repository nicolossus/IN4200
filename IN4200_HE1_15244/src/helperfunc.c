#include "helperfunc.h"

void printmat(char **A, int m, int n){
	for (size_t i = 0; i < m; ++i) {
		printf("| ");
		for (size_t j = 0; j < n; ++j) {
			printf("%d ", A[i][j]);
		}
		printf("|\n");
	}
}
