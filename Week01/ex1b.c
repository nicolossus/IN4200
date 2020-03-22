/*
   Write a C program that allocates a 1D array of length n which is
   prescribed at runtime. You are supposed to first assign the values
   of the array with random numbers, and then find the maximum and
   minimum values. (You can use e.g. the rand function from stdlib.h.)
   int argc, char *argv[]
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "minmax.h"

void fill_random(int*, int);
int maximum(int*, int);
int minimum(int*, int);

int main(){
	int n, max, *rand_array;
	n = 12;
	rand_array = (int *)malloc(n * sizeof(int));
	fill_random(rand_array, n);

	for (int i=0; i<n; i++) {
		printf("%d ", rand_array[i]);
	}
	printf("\n");

	max = maximum(rand_array, n);
	printf("Max=%d \n", max);

	max = minimum(rand_array, n);
	printf("Min=%d \n", max);

	free(rand_array);
	return 0;
}

void fill_random(int *arr, int n){
	for (int i = 0; i < n; i++) {
		arr[i] = (rand() % 100) + 1;
	}
}

int maximum(int *arr, int n){
	int max = arr[0];
	for (int i=1; i<n; i++) {
		max = MAX(max, arr[i]);
	}
	return max;
}

int minimum(int *arr, int n){
	int min = arr[0];
	for (int i=1; i<n; i++) {
		min = MIN(min, arr[i]);
	}
	return min;
}
