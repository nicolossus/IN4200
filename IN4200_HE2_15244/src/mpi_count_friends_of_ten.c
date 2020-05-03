#include "mpi_count_friends_of_ten.h"


#define MASTER 0               /* taskid of first task */
#define FROM_MASTER 1        /* setting a message type */
#define FROM_SLAVE 2         /* setting a message type */

//=============================================================================
int MPI_count_friends_of_ten(int M, int N, int** v)
//----------------------------------------------------------------------------
// Find the total number of "triple-friends of 10" inside the input 2D array v,
// which is of dimension M x N. Implementation is parallelized with mpi.
//
// Arguments
// ---------
// M: number of rows in matrix
// N: number of columns in matrix
// **v: allocated input 2D array (matrix)
//
// Returns
// -------
// The total number of "triple-friends of 10"
//----------------------------------------------------------------------------
{
  int friends=0;
  int **vpart=NULL;
  int taskid, numtasks, numworkers, chunk, rest, offset, tag, slave_rows, ghostpoints;

  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  numworkers = numtasks-1;

  MPI_Bcast(&N, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

  // MASTER
  if (taskid == MASTER){
    chunk = M / numworkers;
    rest = M % numworkers;
    offset = 0;

    tag = FROM_MASTER;
    for (int dest=1; dest<=numworkers; dest++)
      {
         slave_rows = (dest <= rest) ? chunk+1 : chunk;
         ghostpoints = (dest < (numworkers) && (M - offset - slave_rows) >= 2) ? 2 : 0;
         slave_rows += ghostpoints;
         MPI_Send(&ghostpoints, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
         MPI_Send(&slave_rows, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
         MPI_Send(&v[offset][0], slave_rows*N, MPI_INT, dest, tag, MPI_COMM_WORLD);
         offset += slave_rows - ghostpoints;
      }
  }

  // SLAVE
  if (taskid > MASTER){

      tag = FROM_MASTER;
      MPI_Recv(&ghostpoints, 1, MPI_INT, MASTER, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&slave_rows, 1, MPI_INT, MASTER, tag, MPI_COMM_WORLD, &status);

      // Allocate slave array
      vpart = (int **)malloc(slave_rows * sizeof(int *));
      vpart[0] = (int *)malloc(slave_rows*N * sizeof(int));
      for (int i=1; i<slave_rows; i++){
        vpart[i] = vpart[i-1]+N;
      }

      MPI_Recv(&vpart[0][0], slave_rows*N, MPI_INT, MASTER, tag, MPI_COMM_WORLD, &status);

     	// iterate the rows
     	for (int i=0; i<slave_rows-ghostpoints; i++) {
     		// iterate the columns
     		for (int j=0; j<N; j++){
     			// check horizontal row
     			if (j<N-2){
     				friends += vpart[i][j] + vpart[i][j+1] + vpart[i][j+2] == 10;
     			}
     			// check vertical row
     			if (i<slave_rows-2){
     				friends += vpart[i][j] + vpart[i+1][j] + vpart[i+2][j] == 10;
     			}
     			// check diagonal
     			if (i<slave_rows-2 && j<N-2){
     				friends += vpart[i][j] + vpart[i+1][j+1] + vpart[i+2][j+2] == 10;
     			}
     			// check anti-diagonal
     			if (i<slave_rows-2 && j>=2){
     				friends += vpart[i][j] + vpart[i+1][j-1] + vpart[i+2][j-2] == 10;
     			}
     		}
     	}
      free(vpart[0]);
    	free(vpart);
     }

  return friends;
}
