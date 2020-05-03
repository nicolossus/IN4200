#include "mpi_count_friends_of_ten.h"

#define MASTER 0        // task ID of master task
#define FROM_MASTER 1   // specify message ID (aka tag)

//=============================================================================
int MPI_count_friends_of_ten(int M, int N, int** v)
//----------------------------------------------------------------------------
// Find the total number of "triple-friends of 10" inside the input 2D array v
// of dimension M x N. Implementation is MPI-parallelized. The master task
// distributes the 2D array (matrix) between numslaves-1 slave tasks which
// finds the number of "triple-friends of 10" within their partition.
//
// Arguments
// ---------
// M: number of rows in matrix
// N: number of columns in matrix
// **v: allocated input 2D array (matrix)
//
// Returns
// -------
// The number of "triple-friends of 10" found by a slave task.
//----------------------------------------------------------------------------
{
  int friends=0;
  int taskid, numtasks, numslaves, chunk, rest, offset, slave_rows, ghostpoints;

  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  numslaves = numtasks-1;

  // broadcast N to all processes
  MPI_Bcast(&N, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

  /*---------------------------- MASTER ----------------------------*/
  if (taskid == MASTER){
    // Distribute matrix data to the slave tasks

    chunk = M / numslaves;
    rest = M % numslaves;
    offset = 0;

    for (int slave=1; slave<=numslaves; slave++){
      // determine which rows to distribute to slave
      slave_rows = (slave <= rest) ? chunk+1 : chunk;
      // allow the slave to "see" into the next partition if it is not the last
      // or will be out of bounds
      ghostpoints = (slave < (numslaves) && (M - offset - slave_rows) >= 2) ? 2 : 0;
      slave_rows += ghostpoints;
      MPI_Send(&ghostpoints, 1, MPI_INT, slave, FROM_MASTER, MPI_COMM_WORLD);
      MPI_Send(&slave_rows, 1, MPI_INT, slave, FROM_MASTER, MPI_COMM_WORLD);
      MPI_Send(&v[offset][0], slave_rows*N, MPI_INT, slave, FROM_MASTER, MPI_COMM_WORLD);
      // offset for next partition to distribute
      offset += slave_rows - ghostpoints;
    }
  }

  /*---------------------------- SLAVE(S) -----------------------------*/
  if (taskid > MASTER){
      // Receive work partition from master task and calculate number of friends

      MPI_Recv(&ghostpoints, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);
      MPI_Recv(&slave_rows, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);

      // allocate array for slave's chunck of matrix
      v = (int **)malloc(slave_rows * sizeof(int *));
      v[0] = (int *)malloc(slave_rows*N * sizeof(int));
      for (int i=1; i<slave_rows; i++){
        v[i] = v[i-1]+N;
      }

      MPI_Recv(&v[0][0], slave_rows*N, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);

     	// iterate the rows
     	for (int i=0; i<slave_rows-ghostpoints; i++) {
     		// iterate the columns
     		for (int j=0; j<N; j++){
     			// check horizontal row
     			if (j<N-2){
     				friends += v[i][j] + v[i][j+1] + v[i][j+2] == 10;
     			}
     			// check vertical row
     			if (i<slave_rows-2){
     				friends += v[i][j] + v[i+1][j] + v[i+2][j] == 10;
     			}
     			// check diagonal
     			if (i<slave_rows-2 && j<N-2){
     				friends += v[i][j] + v[i+1][j+1] + v[i+2][j+2] == 10;
     			}
     			// check anti-diagonal
     			if (i<slave_rows-2 && j>=2){
     				friends += v[i][j] + v[i+1][j-1] + v[i+2][j-2] == 10;
     			}
     		}
     	}
      // deallocate slave array
      free(v[0]);
    	free(v);
     }

  return friends;
}
