#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

double numerical_integration(double, double, int);

int main(){
	double x_min, x_max, res, tol;
	int N, slices, ndiv;

	x_min = 0.0;
	x_max = 1.0;
	slices = 1;
	tol = 1e-10;
	res = 0.0;
	N = 8;

	while ( fabs(res - M_PI) > tol ) {
		res = numerical_integration(x_min, x_max, slices);
		slices += 100;
	}
	printf("With %i slices and tolerance %.12f, the result is: %.12f \n", slices, tol, res);

	ndiv = 1e6;
	double start = __rdtsc();
	res = numerical_integration(x_min, x_max, ndiv);
	double end = __rdtsc();
	double avg = ((double)(end-start))/ndiv;
	printf("Avg. number of cycles: %f\n", avg);

	return 0;
}

double numerical_integration(double x_min, double x_max, int slices){
	double delta_x = (x_max-x_min)/slices;
	double x, sum = 0.0;
	for (int i=0; i<slices; i++) {
		x = x_min + (i+0.5)*delta_x;
		sum = sum + 4.0/(1.0+x*x);
	}
	return sum*delta_x;
}
