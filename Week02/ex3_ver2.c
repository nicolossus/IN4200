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

	double ***u, ***v;
	int nx, ny, nz, Nt;
	nx = ny = nz = 20;
	Nt = 10;

	// Allocate 3D array

	u = (double ***)calloc(nz, sizeof(double **) * sizeof(double *));
	u[0] = (double **)calloc(nz * ny, sizeof(double *));
	u[0][0] = (double *)calloc(nz * ny * nx, sizeof(double)); // This is the actual underlying 1d array of size nx * ny * nz.

	v = (double ***)calloc(nz, sizeof(double **) * sizeof(double *));
	v[0] = (double **)calloc(nz * ny, sizeof(double *));
	v[0][0] = (double *)calloc(nz * ny * nx, sizeof(double)); // This is the actual underlying 1d array of size nx * ny * nz.


	for (int i = 1; i < nz; i++) {
		u[i] = &(u[0][ny * i]);
		v[i] = &(v[0][ny * i]);
	}

	for (int j=1; j<nz*ny; j++) {
		u[0][j] = &(u[0][0][nx * j]);
		v[0][j] = &(v[0][0][nx * j]);
	}

	// Fill v
	double fact = 1/((nx-1)*(ny-1)*(nz-1));
	for (int i=0; i<nz; i++) {
		for (int j=0; j<ny; j++) {
			for (int k=0; k<nx; k++) {
				v[i][j][k] = 2.0 + sin(((double)i*j*k*M_PI)*fact);
			}
		}
	}


// Solve
	double fact2 = 1.0/6.0;
	for (int t=0; t<Nt; t++) {
		for (int i=1; i<nz-2; i++) {
			for (int j=1; j<ny-2; j++) {
				for (int k=1; k<nx-2; k++) {
					u[i][j][k] = v[i][j][k] + (v[i-1][j][k]+v[i][j-1][k]+v[i][j][k-1]-6*v[i][j][k]+v[i+1][j][k]+v[i][j+1][k]+v[i][j][k+1])*fact2;
				}
			}
		}
		//memcpy(&v, &u, sizeof(u));
	}






	//solve(u, v, nx, ny, nz, Nt);
	printf("Success!\n");

	printf("Print u\n");
	print_3d(u, nx, ny, nz);
	printf("Print v\n");
	//print_3d(v, nx, ny, nz);

	free_3d(u);
	free_3d(v);

	// Free

	free(u[0][0]);
	free(u[0]);
	free(u);

	free(v[0][0]);
	free(v[0]);
	free(v);

	return 0;
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
					u[i][j][k] = v[i][j][k] + (v[i-1][j][k]+v[i][j-1][k]+v[i][j][k-1]-6*v[i][j][k]+v[i+1][j][k]+v[i][j+1][k]+v[i][j][k+1])/((double)denom);
				}
			}
		}
		//memcpy(&v, &u, sizeof(u));
	}
}
//==========================================================================
