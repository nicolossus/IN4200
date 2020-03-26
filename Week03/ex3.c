#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(){
	clock_t t_pow, t_fast;
	double x, y, tmp, tmp2, x2, x4, x32, x64;
	y = 100.0;
	x = 2.0;      // 2^100 = 1.2676506e30

	// Benchmark
	printf("Expected: 1.2676506e+30\n");
	int Nrep;
	Nrep = 100;

	// pow
	t_pow = clock();
	for (int i=0; i<Nrep; i++) {
		tmp = pow(x, y);
	}
	t_pow = clock() - t_pow;
	double time_taken_pow = ((double)t_pow)/CLOCKS_PER_SEC/Nrep*1e9;
	printf("pow(x, 100) took %f ns to execute \n", time_taken_pow);
	printf("pow=%fe+30\n", tmp*1e-30); // benchmark for 2^100

	// x^4*x^32*x^64=x^100
	t_fast = clock();
	for (int i=0; i<Nrep; i++) {
		x2 = x*x;
		x4 = x2*x2;
		x32 = x4*x4*x4*x4;
		x64 = x32*x32;
		tmp2 = x4*x32*x64;
	}
	t_fast = clock() - t_fast;
	double time_taken_fast = ((double)t_fast)/CLOCKS_PER_SEC/Nrep*1e9;
	printf("fast implementation took %f ns to execute \n", time_taken_fast);
	printf("fast=%fe+30\n", tmp*1e-30); // benchmark for 2^100

	return 0;
}
