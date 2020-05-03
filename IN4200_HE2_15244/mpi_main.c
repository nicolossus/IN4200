//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include "src/mpi_count_friends_of_ten.h"
#include "src/helperfunc.h"

#define MASTER 0   // taskid of first task

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char **argv)
//----------------------------------------------------------------------------
// Find the total number of "triple-friends of 10" in a 2D array (matrix) of
// dimension M x N with MPI-parallelized code. Master task allocates the 2D
// array, assigned with appropriate integer values, and then calls the
// ``mpi_count_friends_of_ten`` to distribute array partitions to workers
// which counts and returns the number of “triple-friends of 10” in their
// respective partition. The total number of “triple-friends of 10” is found
// by sum reduction in the main program.
//
// Arguments given on command line
// --------------------------------
// Standard use: M (number of matrix rows) and N (number of matrix columns)
// Test case: "test"
//----------------------------------------------------------------------------
{
  int M=0, N=0, rank, friends, tot_friends;
  int **v=NULL;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == MASTER) {
    if (strcmp(argv[1], "test") == 0) {
      M = 4;
  		N = 5;
      test_matrix(&v);
  		printf("\nTest matrix with 7 friends of 10:\n");
  		print_testmat(v);
  	}
    else{
      M = atoi(argv[1]);
  		N = atoi(argv[2]);
      random_matrix(&v, M, N);
      if ((M*N) < 101) {
  			printf("\nRandom %d x %d matrix:\n", M, N);
  			printmat(v, M, N);
  		}
  		else
  		{
  			printf("\nGenerating a %d x %d random matrix\n", M, N);
  		}
    }
  }

  friends = MPI_count_friends_of_ten(M, N, v);
  if (rank == MASTER){
    printf("MPI rank <%d>: I'm MASTER and distribute work to my slaves\n", rank);
  }
  else{
    printf("MPI rank <%d>: I'm SLAVE and found number of triple friends: %d\n", rank, friends);
  }
  MPI_Reduce(&friends, &tot_friends, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  // Attempt to synchronize output with barrier, although output ordering is not
  // guaranteed in MPI programs.
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == MASTER){
    printf("MASTER: My slaves found total of triple friends: %d\n", tot_friends);
    free2D(v);
  }

  MPI_Finalize ();
  return 0;
}
