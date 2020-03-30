#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/*
   Conclusion
   For small N, baz, qux, bazqux best (pretty equal)
   For large N, foofaster, foofaster2 best (latter the better)
 */

void foo(int, double**, double**, int*);
void bar(int, double**, double**, int*);
void baz(int, double**, double**, int*);
void qux(int, double**, double**, int*);
void bazqux(int, double**, double**, int*);
void foofaster(int, double**, double**, int*);
void foofaster2(int, double**, double**, int*);

//===========================================================
int main(){
	clock_t t, t2, t3, t4, t5, t6, t7;

	int N = 1e4;

	// Allocate A for foo
	double **A = (double **)malloc(N * sizeof(double *));
	A[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < N; i++) {
		A[i] = &(A[0][N * i]);
	}

	// Allocate B for bar
	double **B = (double **)malloc(N * sizeof(double *));
	B[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < N; i++) {
		B[i] = &(B[0][N * i]);
	}

	// Allocate C for baz
	double **C = (double **)malloc(N * sizeof(double *));
	C[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < N; i++) {
		C[i] = &(C[0][N * i]);
	}

	// Allocate D for qux
	double **D = (double **)malloc(N * sizeof(double *));
	D[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < N; i++) {
		D[i] = &(D[0][N * i]);
	}

	// Allocate E for bazqux
	double **E = (double **)malloc(N * sizeof(double *));
	E[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < N; i++) {
		E[i] = &(E[0][N * i]);
	}

	// Allocate F for foofaster
	double **F = (double **)malloc(N * sizeof(double *));
	F[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < N; i++) {
		F[i] = &(F[0][N * i]);
	}

	// Allocate G for foofaster2
	double **G = (double **)malloc(N * sizeof(double *));
	G[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < N; i++) {
		G[i] = &(G[0][N * i]);
	}

	// Allocate s
	double **s = (double **)malloc(N * sizeof(double *));
	s[0] = (double *)malloc(N * N * sizeof(double)); // This is the actual underlying 1d array of size m * n.
	for (size_t i = 1; i < N; i++) {
		s[i] = &(A[0][N * i]);
	}

	// Allocate v
	int *v = malloc(N * sizeof *v);

	// Fill s, v

	for (size_t i=0; i<N; i++) {
		for (size_t j=0; j<N; j++) {
			s[i][j] = (rand() % 100) + 1;
		}
	}

	for (size_t i=0; i<N; i++) {
		v[i] = (rand() % 100) + 1;
	}

	// Func calls
	t = clock();
	foo(N, A, s, v);
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC;
	printf("foo() took %f milliseconds to execute \n", 1000*t_tot);

	t2 = clock();
	bar(N, B, s, v);
	t2 = clock() - t2;
	double t2_tot = ((double)t2)/CLOCKS_PER_SEC;
	printf("bar() (optimized foo) took %f milliseconds to execute \n", 1000*t2_tot);

	t3 = clock();
	baz(N, C, s, v);
	t3 = clock() - t3;
	double t3_tot = ((double)t3)/CLOCKS_PER_SEC;
	printf("baz() (optimized bar) took %f milliseconds to execute \n", 1000*t3_tot);

	t4 = clock();
	baz(N, D, s, v);
	t4 = clock() - t4;
	double t4_tot = ((double)t4)/CLOCKS_PER_SEC;
	printf("qux() (optimized bar?) took %f milliseconds to execute \n", 1000*t4_tot);

	t5 = clock();
	bazqux(N, E, s, v);
	t5 = clock() - t5;
	double t5_tot = ((double)t5)/CLOCKS_PER_SEC;
	printf("bazqux() (combined baz & qux) took %f milliseconds to execute \n", 1000*t5_tot);

	t6 = clock();
	foofaster(N, F, s, v);
	t6 = clock() - t6;
	double t6_tot = ((double)t6)/CLOCKS_PER_SEC;
	printf("foofaster() (will it win?) took %f milliseconds to execute \n", 1000*t6_tot);

	t7 = clock();
	foofaster2(N, G, s, v);
	t7 = clock() - t7;
	double t7_tot = ((double)t7)/CLOCKS_PER_SEC;
	printf("foofaster2() (best of the best?) took %f milliseconds to execute \n", 1000*t7_tot);

	// Deallocate
	free(A[0]);
	free(A);
	free(B[0]);
	free(B);
	free(C[0]);
	free(C);
	free(D[0]);
	free(D);
	free(E[0]);
	free(E);
	free(F[0]);
	free(F);
	free(G[0]);
	free(G);
	free(s[0]);
	free(s);
	free(v);

	return 0;
}
//===========================================================


//===========================================================
void foo(int N, double **mat, double **s, int *v) {
	int i,j;
	double val;
	for (j=0; j<N; j++)
		for (i=0; i<N; i++) {
			val = 1.0*(v[j]%256);
			mat[i][j] = s[i][j]*(sin(val)*sin(val)-cos(val)*cos(val));
		}
}
//===========================================================


//===========================================================
void bar(int N, double **mat, double **s, int *v) {
	// Optimized foo
	//double val;
	for (size_t j=0; j<N; j++) {
		double fact = -cos(2.0*(v[j]%256));
		//val = 1.0*(v[j]%256);
		//double fact = sin(val)*sin(val)-cos(val)*cos(val);
		for (size_t i=0; i<N; i++) {
			mat[i][j] = s[i][j]*fact;
		}
	}
}
//===========================================================


//===========================================================
void baz(int N, double **mat, double **s, int *v) {
	// Optimized foo
	int rest = N % 4;
	for (size_t j=0; j<N-rest; j+=4) {
		double val1 = -cos(2.0*(v[j]%256));
		double val2 = -cos(2.0*(v[j+1]%256));
		double val3 = -cos(2.0*(v[j+2]%256));
		double val4 = -cos(2.0*(v[j+3]%256));

		for (size_t i=0; i<N; i++) {
			mat[i][j] = s[i][j]*val1;
			mat[i][j+1] = s[i][j+1]*val2;
			mat[i][j+2] = s[i][j+2]*val3;
			mat[i][j+3] = s[i][j+2]*val4;
		}
	}

	for (size_t j=N-rest; j<N; j++) {
		double val1 = -cos(2.0*(v[j]%256));
		for (size_t i=0; i<N; i++) {
			mat[i][j] = s[i][j]*val1;
		}
	}
}
//===========================================================


//===========================================================
void qux(int N, double **mat, double **s, int *v){
	int rest = N%4;
	for (size_t j=0; j<N; j++) {
		double fact = -cos(2.0*(v[j]%256));
		for (size_t i=0; i<N-rest; i+=4) {
			mat[i][j] = s[i][j]*fact;
			mat[i+1][j] = s[i+1][j]*fact;
			mat[i+2][j] = s[i+2][j]*fact;
			mat[i+3][j] = s[i+3][j]*fact;
		}
		for(size_t i = N-rest; i < N; i++) {
			mat[i][j] = s[i][j]*fact;
		}
	}

}
//===========================================================


//===========================================================
void bazqux(int N, double **mat, double **s, int *v) {
	// Combined baz & qux
	int rest = N % 4;
	for (size_t j=0; j<N-rest; j+=4) {
		double val1 = -cos(2.0*(v[j]%256));
		double val2 = -cos(2.0*(v[j+1]%256));
		double val3 = -cos(2.0*(v[j+2]%256));
		double val4 = -cos(2.0*(v[j+3]%256));

		for (size_t i=0; i<N-rest; i+=4) {
			mat[i][j] = s[i][j]*val1;
			mat[i+1][j] = s[i+1][j]*val1;
			mat[i+2][j] = s[i+2][j]*val1;
			mat[i+3][j] = s[i+3][j]*val1;
			mat[i][j+1] = s[i][j+1]*val2;
			mat[i][j+2] = s[i][j+2]*val3;
			mat[i][j+3] = s[i][j+2]*val4;
		}
	}

	for (size_t j=N-rest; j<N; j++) {
		double val1 = -cos(2.0*(v[j]%256));
		for (size_t i=N-rest; i<N; i++) {
			mat[i][j] = s[i][j]*val1;
		}
	}
}
//===========================================================


//===========================================================
void foofaster (int N, double **mat, double **s, int *v)
{
	double *val = malloc(256 * sizeof *val);
	int *vtab = malloc(N * sizeof *vtab);
	// Table of possible values. This should really be constructed once,
	// outside the scope of this function.
	for (int i = 0; i < 256; i++) {
		val[i] = -cos(2.0*i);
	}
	// Table matching values of v to values in val.
	for (size_t i = 0; i < N; i++) {
		vtab[i] = abs(v[i]%256);
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			mat[j][i] = s[j][i]*val[vtab[i]];
		}
	}
	free(val);
	free(vtab);
}
//===========================================================

//===========================================================
void foofaster2 (int N, double **mat, double **s, int *v)
{
	double *val = malloc(256 * sizeof *val);
	int *vtab = malloc(N * sizeof *vtab);
	// Table of possible values. This should really be constructed once,
	// outside the scope of this function.
	for (int i = 0; i < 256; i++) {
		val[i] = -cos(2.0*i);
	}
	// Table matching values of v to values in val.

	for (int j = 0; j < N; j++) {
		vtab[j] = abs(v[j]%256);
		for (int i = 0; i < N; i++) {
			mat[j][i] = s[j][i]*val[vtab[i]];
		}
	}
	free(val);
	free(vtab);
}
//===========================================================
