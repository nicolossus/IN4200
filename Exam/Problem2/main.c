
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>


void serial_func();
void omp_func();
void printvec(char*, int);

int main(int argc, char *argv[]){

  int Nrep = 1;

  double ts = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		serial_func();
	}
	ts = omp_get_wtime() - ts;
	double ts_tot = ((double)ts)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nserial_func()\
  took %f milliseconds to execute \n\n", Nrep, 1000*ts_tot);


  double to = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		omp_func();
	}
	to = omp_get_wtime() - to;
	double to_tot = ((double)to)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nomp_func()\
  took %f milliseconds to execute \n\n", Nrep, 1000*to_tot);

  return 0;
}


void serial_func()
{
  int i,j, sqrt_N;
  int N = 1e3;
  char *array = malloc(N);  // N is a predefined very large integer
  array[0] = array[1] = 0;
  for (i=2; i<N; i++){
    array[i] = 1;
  }
  int counter = 0;
  sqrt_N = (int)(sqrt(N)); // square root of N
  for (i=2; i<=sqrt_N; i++) {
    if (array[i]) {
      printf("i=%d\n", i);
      for (j=i*i; j<N; j+=i){
        array[j] = 0;
      }
      //printvec(array, N);
      counter++;
    }
  }
  printf("counter: %d\n", counter);

  free (array);
}


void omp_func(){
  int i,j, sqrt_N;
  int N = 1e6;
  char *array = malloc(N);  // N is a predefined very large integer
  array[0] = array[1] = 0;
  #pragma omp parallel for
  for (i=2; i<N; i++)
    array[i] = 1;


  sqrt_N = (int)(sqrt(N)); // square root of N
  for (i=2; i<=sqrt_N; i++) {
    if (array[i]){
      #pragma omp parallel for
      for (j=i*i; j<N; j+=i)
        array[j] = 0;
    }
  }

  free (array);
}


//=============================================================================
void printvec(char *v, int n)
{
	printf("| ");
	for (size_t i = 0; i < n; ++i) {
		printf("%d ", v[i]);
	}
	printf("|\n");
}
//=============================================================================
