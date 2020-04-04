//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "src/read_graph_from_file1.h"
#include "src/read_graph_from_file2.h"
#include "src/helperfunc.h"

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
//----------------------------------------------------------------------------
// Counting mutual web linkage occurrences
//
// Parameters given on command line
// --------------------------------
// webgraph.txt: filename of web graph to be used in benchmark
// Nrep: number of function call repetitions. The average runtime is calculated
//----------------------------------------------------------------------------
{

	if (argc < 2) {
		printf("Web graph filename required.\n");
		exit(0);
	}

	char **table2D;
	int *row_ptr;
	int *col_idx;
	int N, N_links;

	read_graph_from_file1(argv[1], &N, &table2D);

	read_graph_from_file2(argv[1], &N, &N_links, &row_ptr, &col_idx);

	printvec(row_ptr, N+1);
	printvec(col_idx, N_links);

	freetable(table2D);
	free(row_ptr);
	free(col_idx);

	return 0;
}
//============================================================================
