//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include "src/mpi_count_friends_of_ten.h"
#include "src/helperfunc.h"

#define MASTER 0               /* taskid of first task */

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char **argv)
//----------------------------------------------------------------------------
// Find the total number of "triple-friends of 10" in a 2D array (matrix) of
// dimension M x N
//
// Arguments given on command line
// --------------------------------
//
//
//----------------------------------------------------------------------------
{
  int M=0, N=0, rank, friends, tot_friends;
  int **v=NULL;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == MASTER) {
    M = atoi(argv[1]);
		N = atoi(argv[2]);
    //random_matrix(&v, M, N);
    test_matrix(&v);
  }

  friends = MPI_count_friends_of_ten(M, N, v);
  if (rank == MASTER){
    printf("MPI rank <%d>: I'm MASTER and distribute work to my slaves\n", rank);
  }
  else{
    printf("MPI rank <%d>: I'm SLAVE and found number of triple friends: %d\n", rank, friends);
  }
  MPI_Reduce(&friends, &tot_friends, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == MASTER){
    printf("MASTER: My slaves found total of triple friends: %d\n", tot_friends);
    free2D(v);
  }

  MPI_Finalize ();
  return 0;
}
