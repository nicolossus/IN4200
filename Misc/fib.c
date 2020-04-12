#include <omp.h>

int main(){

	done = new int[nmax+1];
	for (i=0; i<=nmax; i++)
		done[i] = 0;
	done[0] = 1;
	done[1] = 1;

	return 0;
}

int fib(int n)
{
	int i, j;
	omp_set_lock( &(dolock[n]) );
	if (!done[n]) {
#pragma omp task shared(i) firstprivate(n)
		i = fib(n-1);
#pragma omp task shared(j) firstprivate(n)
		j = fib(n-2);
#pragma omp taskwait
		value[n] = i+j;
		done[n] = 1;
	}
	omp_unset_lock( &(dolock[n]) );
	return value[n];
}
