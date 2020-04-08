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
#include "src/count_mutual_links1.h"
#include "src/count_mutual_links2.h"
#include "src/top_n_webpages.h"
#include "src/helperfunc.h"

//=================================
// Function prototypes
void benchmark_read_graph_from_file1(char*, int);
void benchmark_read_graph_from_file2(char*, int);
void benchmark_count_mutual_links1(char*, int);
void benchmark_count_mutual_links2(char*, int);
void benchmark_calc_top_n_webpages(char*, int);
void benchmark_method1(char*, int);
void benchmark_method2(char*, int);

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
		benchmark_read_graph_from_file1(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "read_graph_from_file2.c") == 0)
	{
		benchmark_read_graph_from_file2(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "count_mutual_links1.c") == 0)
	{
		benchmark_count_mutual_links1(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "count_mutual_links2.c") == 0)
	{
		benchmark_count_mutual_links2(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "top_n_webpages.c") == 0)
	{
		benchmark_calc_top_n_webpages(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "method1") == 0)
	{
		benchmark_method1(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "method2") == 0)
	{
		benchmark_method2(argv[2], Nrep);
	}
	else if (strcmp(argv[1], "all") == 0) {
		benchmark_read_graph_from_file1(argv[2], Nrep);
		benchmark_read_graph_from_file2(argv[2], Nrep);
		benchmark_count_mutual_links1(argv[2], Nrep);
		benchmark_count_mutual_links2(argv[2], Nrep);
		benchmark_calc_top_n_webpages(argv[2], Nrep);
		benchmark_method1(argv[2], Nrep);
		benchmark_method2(argv[2], Nrep);
	}
	else
	{
		printf("Provided filename not valid. Provide one of the following:\n" );
		printf("'read_graph_from_file1.c'\n'read_graph_from_file2.c'\n 'count_mutual_links1.c'\n");
		printf("'all' to test all\n");
		exit(0);
	}

	return 0;
}
//============================================================================


//=============================================================================
void benchmark_read_graph_from_file1(char *graphfile, int Nrep)
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
void benchmark_read_graph_from_file2(char *graphfile, int Nrep)
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


//=============================================================================
void benchmark_count_mutual_links1(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file1.c'
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'count_mutual_links1.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	clock_t t;

	char **table2D;
	int N, mutual_links;
	read_graph_from_file1(graphfile, &N, &table2D);
	int *num_involvements = calloc((N), sizeof(*num_involvements));
	t = clock();
	for (int i=0; i<Nrep; i++) {
		mutual_links = count_mutual_links1(N, table2D, num_involvements);
	}
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC/Nrep;
	printf("\nTime usage averaged over %d repetitions:\ncount_mutual_links1()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	freetable(table2D);
	free(num_involvements);

}
//=============================================================================

/*
   //=============================================================================
   void benchmark_count_mutual_links2(char *graphfile, int Nrep)
   //----------------------------------------------------------------------------
   // Test function for 'read_graph_from_file1.c'
   //----------------------------------------------------------------------------
   {
        printf("\n-----------------------------------\n");
        printf("Benchmark 'count_mutual_links2.c'\n");
        printf("-----------------------------------\n");
        printf("Web graph file: '%s'\n", graphfile);

        clock_t t;

        int *row_ptr;
        int *col_idx;
        int N, N_links, mutual_links;

        read_graph_from_file2(graphfile, &N, &N_links, &row_ptr, &col_idx);
        int *num_involvements = calloc((N), sizeof(*num_involvements));
        t = clock();
        mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

        t = clock();
        for (int i=0; i<Nrep; i++) {
                mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
        }
        t = clock() - t;
        double t_tot = ((double)t)/CLOCKS_PER_SEC/Nrep;
        printf("\nTime usage averaged over %d repetitions:\ncount_mutual_links2()\
   took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

        free(row_ptr);
        free(col_idx);
        free(num_involvements);

   }
   //=============================================================================
 */


//=============================================================================
void benchmark_count_mutual_links2(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file1.c'
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'count_mutual_links2.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	int *row_ptr;
	int *col_idx;
	int N, N_links, mutual_links;

	read_graph_from_file2(graphfile, &N, &N_links, &row_ptr, &col_idx);
	int *num_involvements = calloc((N), sizeof(*num_involvements));

	#if defined(_OPENMP)
	{
		double start = omp_get_wtime();
		for (int i=0; i<Nrep; i++) {
			mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
		}
		double end = omp_get_wtime();
		double t_tot = end - start;
		printf("\nTime usage averaged over %d repetitions:\ncount_mutual_links2()\
	  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot/Nrep);
	}
 #else
	{
		clock_t t;
		t = clock();
		for (int i=0; i<Nrep; i++) {
			mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
		}
		t = clock() - t;
		double t_tot = ((double)t)/CLOCKS_PER_SEC/Nrep;
		printf("\nTime usage averaged over %d repetitions:\ncount_mutual_links2()\
	  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);
	}
 #endif

	free(row_ptr);
	free(col_idx);
	free(num_involvements);

}
//=============================================================================


//=============================================================================
void benchmark_calc_top_n_webpages(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark function for 'top_n_webpages.c'
// This only benchmarks the implementation of calc_top_n_webpages(), which
// searches the num_involvements array for the indices corresponding to the n
// top webpage nodes and stores them in top_results.
// It is deemed to verbose to benchmark top_n_webpages(), as it print results
// to screen with each call. Time used by the printf function is not extensive,
// but the complexity of the for-loop in top_n_webpages() which prints goes as
// n. For normal use cases this is not significant, but for larger n the
// execution time of top_n_webpages() will be longer than calc_top_n_webpages().
// To accomendate for this the function top_n_webpages_faster() has also been
// implemented, which calculates and prints with complexity N*n rather than
// N*n+n in top_n_webpages()
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'top_n_webpages.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	clock_t t;

	char **table2D;
	int N, mutual_links;
	int n = 8;
	read_graph_from_file1(graphfile, &N, &table2D);
	int *num_involvements = calloc((N), sizeof(*num_involvements));
	mutual_links = count_mutual_links1(N, table2D, num_involvements);

	int *top_results = malloc(n * sizeof(*top_results));

	t = clock();
	for (int i=0; i<Nrep; i++) {
		calc_top_n_webpages(N, num_involvements, top_results, n);
	}
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC/Nrep;
	printf("\nTime usage averaged over %d repetitions:\ncalc_top_n_webpages()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	freetable(table2D);
	free(num_involvements);
	free(top_results);

}
//=============================================================================


//=============================================================================
void benchmark_method1(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark method 1 with 2D table as storage format with all allocations,
// function calls and deallocations
//----------------------------------------------------------------------------
{
	printf("\n------------------------------------------------------------------------\n");
	printf("Benchmark method 1 with 2D table as storage format with all allocations,\n\
function calls and deallocations.\n");
	printf("------------------------------------------------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	clock_t t;

	t = clock();
	for (int i=0; i<Nrep; i++) {
		char **table2D;
		int N, mutual_links;
		int n = 10;
		read_graph_from_file1(graphfile, &N, &table2D);
		int *num_involvements = calloc((N), sizeof(*num_involvements));
		mutual_links = count_mutual_links1(N, table2D, num_involvements);
		int *top_results = malloc(n * sizeof(*top_results));
		calc_top_n_webpages(N, num_involvements, top_results, n);

		freetable(table2D);
		free(top_results);
		free(num_involvements);
	}
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nMethod 1\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

}
//=============================================================================


//=============================================================================
void benchmark_method2(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark method 1 with 2D table as storage format with all allocations,
// function calls and deallocations
//----------------------------------------------------------------------------
{
	printf("\n------------------------------------------------------------------------\n");
	printf("Benchmark method 2 with CRS as storage format with all allocations,\n\
function calls and deallocations. Top 10 webpages is ranked.\n");
	printf("------------------------------------------------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	clock_t t;

	t = clock();
	for (int i=0; i<Nrep; i++) {

		int *row_ptr;
		int *col_idx;
		int N, N_links, mutual_links;
		int n = 10;

		read_graph_from_file2(graphfile, &N, &N_links, &row_ptr, &col_idx);
		int *num_involvements = calloc((N), sizeof(*num_involvements));
		mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
		int *top_results = malloc(n * sizeof(*top_results));
		calc_top_n_webpages(N, num_involvements, top_results, n);

		free(row_ptr);
		free(col_idx);
		free(top_results);
		free(num_involvements);
	}
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nMethod 2\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

}
//=============================================================================
