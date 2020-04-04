//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include "src/read_graph_from_file1.h"
#include "src/read_graph_from_file2.h"
#include "src/helperfunc.h"

//=================================
// Function prototypes
void benchmark_read_graph1(char*, int);
void benchmark_read_graph2(char*, int);

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
//----------------------------------------------------------------------------
// Benchmark implemented functions. Specify filename of
//
// Parameters given on command line
// --------------------------------
// program.c: filename of program with function to be benchmarked
// webgraph.txt: filename of web graph to be used in benchmark
// Nrep: number of function call repetitions. The average runtime is calculated
//----------------------------------------------------------------------------
{
	if (argc < 4) {
		printf("Please provide program filename, web graph filename and number of \
    repetitions on command line. program.c webgraph.txt Nrep required. Provide \
    'all' to test all, else specify which file.\n");
		exit(0);
	}

	int Nrep = atoi(argv[3]);

	if (strcmp(argv[1], "read_graph_from_file1.c") == 0)
	{
		benchmark_read_graph1(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "read_graph_from_file2.c") == 0)
	{
		benchmark_read_graph2(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "all") == 0) {
		benchmark_read_graph1(argv[2], Nrep);
	}
	else
	{
		printf("Provided filename not valid. Provide one of the following:\n" );
		printf("'read_graph_from_file1.c'\n'read_graph_from_file2.c'\n");
		printf("'all' to test all\n");
		exit(0);
	}

	return 0;
}
//============================================================================


//=============================================================================
void benchmark_read_graph1(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file1.c'
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'read_graph_from_file1.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	clock_t t;

	char **table2D;
	int N;

	t = clock();
	for (int i=0; i<Nrep; i++) {
		read_graph_from_file1(graphfile, &N, &table2D);
	}
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nread_graph_from_file1()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);
	freetable(table2D);

}
//=============================================================================

//=============================================================================
void benchmark_read_graph2(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file1.c'
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'read_graph_from_file2.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	clock_t t;

	int *row_ptr;
	int *col_idx;
	int N, N_links;

	t = clock();
	for (int i=0; i<Nrep; i++) {
		read_graph_from_file2(graphfile, &N, &N_links, &row_ptr, &col_idx);
	}
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nread_graph_from_file2()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	free(row_ptr);
	free(col_idx);

}
//=============================================================================
