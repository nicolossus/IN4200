#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>


void sweep_serial(int, double**, int, double**, double**);
void sweep_omp(int, double**, int, double**, double**);
void zeros2D(double***, int, int);
void random_matrix(double***, int, int);
void free2D(double**);

int main(int argc, char *argv[]){

  int Nrep = 1;
  int N = 1000;
  int n = 10;

  double **table1, **table2, **mask;
  random_matrix(&table1, N, N);
  random_matrix(&mask, n, n);
  random_matrix(&table2, N-n+1, N-n+1);


  double ts = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		sweep_serial(N, table1, n, mask, table2);
	}
	ts = omp_get_wtime() - ts;
	double ts_tot = ((double)ts)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nserial_func()\
  took %f milliseconds to execute \n\n", Nrep, 1000*ts_tot);


  double to = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		sweep_omp(N, table1, n, mask, table2);
	}
	to = omp_get_wtime() - to;
	double to_tot = ((double)to)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nomp_func()\
  took %f milliseconds to execute \n\n", Nrep, 1000*to_tot);

  free2D(table1);
  free2D(table2);
  free2D(mask);

  return 0;
}



void sweep_serial (int N, double **table1, int n, double **mask, double**table2)
{
  int i,j,ii,jj;
  double temp;
  for (i=0; i<=N-n; i++){
    for (j=0; j<=N-n; j++) {
      temp = 0.0;
      for (ii=0; ii<n; ii++){
        for (jj=0; jj<n; jj++){
          temp += table1[i+ii][j+jj]*mask[ii][jj];
        }
      }
      table2[i][j] = temp;
    }
  }
}


void sweep_omp (int N, double **table1, int n, double **mask, double**table2)
{
  int i,j,ii,jj;
  double temp;
  #pragma omp parallel for collapse(2) reduction(+: temp) private(ii, jj)
  {
    for (i=0; i<=N-n; i++)
      for (j=0; j<=N-n; j++) {
        temp = 0.0;
        for (ii=0; ii<n; ii++)
          for (jj=0; jj<n; jj++)
            temp += table1[i+ii][j+jj]*mask[ii][jj];
        table2[i][j] = temp;
      }
    }
}


/*
void sweep_omp (int N, double **table1, int n, double **mask, double**table2)
{
  int i,j,ii,jj;
  double temp;
  //#pragma omp parallel for collapse(2) reduction(+: temp) private(ii, jj)
  #pragma omp parallel for collapse(2) reduction(+: temp) private(ii, jj)
  {
    for (i=0; i<=N-n; i++){
      for (j=0; j<=N-n; j++) {
        temp = 0.0;
        for (ii=0; ii<n; ii++){
          for (jj=0; jj<n; jj++){
            temp += table1[i+ii][j+jj]*mask[ii][jj];
          }
        }
        table2[i][j] = temp;
      }
    }
  }
}
*/


//=============================================================================
void zeros2D(double ***A, int M, int N)
//----------------------------------------------------------------------------
// Allocate 2D array initialized with zeros
//
// Arguments
// ---------
// A : Address of 2D array
// M : number of rows
// N : number of cols
//----------------------------------------------------------------------------
{
	*A = calloc(M, sizeof (*A));
	(*A)[0] = calloc(M*N, sizeof (*A)[0]);
	for (size_t i = 1; i < M; i++) {
		(*A)[i] = &((*A)[0][i*N]);
	}
}
//=============================================================================


//=============================================================================
void random_matrix(double*** A, int M, int N)
//----------------------------------------------------------------------------
// Assign 2D array random nonnegative integer values 1 - 9
//
// Arguments
// ---------
// **A: 2D test array
//----------------------------------------------------------------------------
{
	zeros2D(A, M, N);
	for (size_t i=0; i<M; i++) {
		for (size_t j=0; j<N; j++) {
			(*A)[i][j] = (rand() % 9) + 1;
		}
	}
}
//=============================================================================


//=============================================================================
void free2D(double **A)
//----------------------------------------------------------------------------
// Deallocate 2D array
//
// Arguments
// ---------
// **A: 2D array
//----------------------------------------------------------------------------
{
	free(A[0]);
	free(A);
}
//=============================================================================
