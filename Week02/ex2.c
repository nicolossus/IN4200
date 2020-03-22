#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>   // memcpy

typedef double data_type;

int main(){
	clock_t t_loop, t_memcpy;
	int n=1e6;

	// Allocate
	data_type *a = malloc(n * sizeof *a);
	data_type *b = malloc(n * sizeof *a);
	data_type *c = malloc(n * sizeof *a);

	// Initialize array a
	for (int i=0; i<n; i++) {
		a[i] = (rand() % 100) + 1;
	}

	// Copy array a to array b with for-loop
	t_loop = clock();
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}
	t_loop = clock() - t_loop;
	double time_taken_loop = ((double)t_loop)/CLOCKS_PER_SEC*1000;
	printf("copy with for-loop took %f milliseconds to execute \n", time_taken_loop);

	// Copy array a to array c with memcpy
	t_memcpy = clock();
	memcpy(c, a, n * sizeof *a);
	t_memcpy = clock() - t_memcpy;
	double time_taken_memcpy = ((double)t_memcpy)/CLOCKS_PER_SEC*1000;
	printf("copy with memcpy took %f milliseconds to execute \n", time_taken_memcpy);

	// Deallocate
	free(a);
	free(b);
	free(c);

	return 0;
}
