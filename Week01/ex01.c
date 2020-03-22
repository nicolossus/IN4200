#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void convergence(int);
void allocate1Darr(int);

int main() {
	convergence(10);
}


void convergence(int N){
	/* Function for verifying that the limit of 1 - 1/2^2 + 1/2^4 - 1/2^6 + ...
	   is 4/5*/

	double limval = 0;
	for (int i=1; i<N; i++) {
		limval += pow(-1, i+1) * pow(4, 1-i);
	}

	printf("After %i iterations, the series has converged to the limit %.2lf\n",
	       N, limval);
}

void allocate1Darr(int n){

}
