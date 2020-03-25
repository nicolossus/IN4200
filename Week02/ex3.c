#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>   // memcpy


void print_3d(double***, int, int, int);
void allocate_3d(double****, int, int, int);
void free_3d(double***);
void initialize(double***, double***, int, int, int);
void solve(double***, double***, int, int, int, int);

//==========================================================================
int main(){
	clock_t t;
	double ***u, ***v, num_flo;
	int nx, ny, nz, Nt;
	nx = ny = nz = 5;
	Nt = 5;
	num_flo = 9*(nx - 2)*(ny - 2)*(nz - 2)*Nt;

	allocate_3d(&u, nx, ny, nz);
	allocate_3d(&v, nx, ny, nz);
	initialize(v, u, nx, ny, nz);

	/*
	      printf("Print initial u\n");
	      print_3d(u, nx, ny, nz);
	      printf("Print initial v\n");
	      print_3d(v, nx, ny, nz);
	 */

	t = clock();
	solve(u, v, nx, ny, nz, Nt); // call solve
	t = clock() - t;
	double total_time = ((double)t)/CLOCKS_PER_SEC;
	printf("Solver success!\n");
	printf("Time elapsed %f s.\nMFLOPS: %f\n\n", total_time, (double)num_flo/(double)total_time/1e6);

	/*
	      printf("Print simulated u\n");
	      print_3d(u, nx, ny, nz);
	      printf("Print simulated v\n");
	      print_3d(v, nx, ny, nz);
	 */

	free_3d(u);
	free_3d(v);

	return 0;
}
//==========================================================================


//==========================================================================
void allocate_3d(double ****A, int nx, int ny, int nz){
	double ***AA;
	AA = (double ***)malloc(nz * sizeof(double **) * sizeof(double *));
	AA[0] = (double **)malloc(nz * ny * sizeof(double *));
	AA[0][0] = (double *)malloc(nz * ny * nx * sizeof(double)); // This is the actual underlying 1d array of size nx * ny * nz.

	for (int i = 1; i < nz; i++) {
		AA[i] = &(AA[0][ny * i]);
	}

	for (int j=1; j<nz*ny; j++) {
		AA[0][j] = &(AA[0][0][nx * j]);
	}

	*A = AA;

}
//==========================================================================


//==========================================================================
void free_3d(double ***A){
	free(A[0][0]);
	free(A[0]);
	free(A);
}
//==========================================================================


//==========================================================================
void initialize(double ***v, double ***u, int nx, int ny, int nz){
	double denom = (nx-1)*(ny-1)*(nz-1);
	for (int i=0; i<nz; i++) {
		for (int j=0; j<ny; j++) {
			for (int k=0; k<nx; k++) {
				v[i][j][k] = 2.0 + sin(((double)i*j*k*M_PI)/denom);
				u[i][j][k] = 0.0;
			}
		}
	}
}
//==========================================================================


//==========================================================================
void print_3d(double ***A, int nx, int ny, int nz){
	for (int i=0; i<nz; i++) {
		//printf("[");
		for (int j=0; j<ny; j++) {
			//printf("[");
			for (int k=0; k<nx; k++) {
				printf("%f\t", A[i][j][k]);
			}
			//printf("]\n");
			printf("\n");
		}
		//printf("]\n");
		printf("\n");
	}

}
//==========================================================================


//==========================================================================
void solve(double ***u, double ***v, int nx, int ny, int nz, int Nt){
	double denom = 1.0/6.0;
	for (int t=0; t<Nt; t++) {
		for (int i=1; i<nz-2; i++) {
			for (int j=1; j<ny-2; j++) {
				for (int k=1; k<nx-2; k++) {
					u[i][j][k] = v[i][j][k] + (v[i-1][j][k]+v[i][j-1][k]+v[i][j][k-1]-6*v[i][j][k]+v[i+1][j][k]+v[i][j+1][k]+v[i][j][k+1])*denom;
				}
			}
			for(int ii = 0; ii < nx; ii++) {
				for(int jj = 0; jj < ny; jj++) {
					memcpy(v[ii][jj], u[ii][jj], sizeof(double)*nz);
				}
			}
		}
		//memcpy(&v, &u, sizeof(u));
	}
}
//==========================================================================
