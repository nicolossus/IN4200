//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "src/read_graph_from_file1.h"
#include "src/helperfunc.h"

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
//----------------------------------------------------------------------------
// Counting mutual web linkage occurrences
//----------------------------------------------------------------------------
{

	char **table2D;
	int N;

	read_graph_from_file1("data/test_graph.txt", &N, &table2D);

	printmat(table2D, N, N);

	return 0;
}
//============================================================================
