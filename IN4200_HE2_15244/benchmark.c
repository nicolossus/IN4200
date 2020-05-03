//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <string.h>
#include "src/count_friends_of_ten.h"
#include "src/helperfunc.h"

//=================================
// Function prototypes
void benchmark_serial(int Nrep);
void benchmark_parallel(int Nrep);

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
//----------------------------------------------------------------------------
// Benchmark implemented functions.
//
// Parameters given on command line
// --------------------------------
// program.c: filename of program with function to be benchmarked
// webgraph.txt: filename of web graph to be used in benchmark
// Nrep: number of function call repetitions. The average runtime is calculated
//----------------------------------------------------------------------------
{
	if (argc < 3) {
		printf("Please provide 'serial' or 'parallel' and number of function call \
    repetitions (Nrep) on command line.\n");
		exit(0);
	}

	int Nrep = atoi(argv[2]);

	if (strcmp(argv[1], "serial") == 0)
	{
		benchmark_serial(Nrep);
	}
	else if (strcmp(argv[1], "parallel") == 0)
	{
		benchmark_parallel(Nrep);
	}
	else
	{
		printf("Provided arguments on command line not valid. Provide 'serial' or \
    'parallel' and number of function call repetitions (Nrep) on command line\n");
		exit(0);
	}

	return 0;
}
//============================================================================


void benchmark_serial(int Nrep){
  int M = 1000;
  int N = 1000;
  int **v, friends;
  random_matrix(&v, M, N);
  printf("\nGenerating a %d x %d random matrix\n", M, N);
  double t = MPI_Wtime();
	for (int i=0; i<Nrep; i++) {
		friends = count_friends_of_ten(M, N, v);
	}
	t = MPI_Wtime() - t;
	double t_tot = ((double)t)/Nrep;
	printf("Time usage averaged over %d repetitions:\ncount_friends_of_ten()\
  took %f milliseconds to execute.\n\n", Nrep, 1000*t_tot);
  free2D(v);
}

void benchmark_parallel(int Nrep){
  printf("Worker's be workin'\n");
}
