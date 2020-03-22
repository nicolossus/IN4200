/*
   Write a C program to verify that the limit of 1 - 1/2^2 + 1/2^4 - 1/2^6 + ...
   is 4/5
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double convergence(int);

int main(){
	int N;
	double r;
	N = 10;
	r = convergence(N);
	printf("r=%f", r);
	return 0;
}

double convergence(int N){
	double r;
	r = 0;
	for (int i=1; i<N; i++) {
		r += pow(-1, i+1) * pow(4, 1-i);
	}
	return r;
}
