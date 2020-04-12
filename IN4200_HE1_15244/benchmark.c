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
void benchmark_calc_top_n_webpages_serial(char*, int);
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
    repetitions on command line. program.c webgraph.txt Nrep required.\n");
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
	else if (strcmp(argv[1], "top_n_webpages_serial.c") == 0)
	{
		benchmark_calc_top_n_webpages_serial(argv[2], Nrep);
	}
	else
	{
		printf("Provided filename not valid. Provide one of the following:\n" );
		printf("'read_graph_from_file1.c'\n'read_graph_from_file2.c'\n\
		'count_mutual_links1.c'\n'count_mutual_links2.c'\n'top_n_webpages.c'\n\
		'top_n_webpages_serial.c'\n");
		exit(0);
	}

	return 0;
}
//============================================================================


//=============================================================================
void benchmark_read_graph_from_file1(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark function for 'read_graph_from_file1.c'.
//
// Arguments
// ---------
// *graphfile: filename of web graph as str
// Nrep: number of function call repetitions as int.
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'read_graph_from_file1.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	char **table2D;
	int N;

	double t = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		read_graph_from_file1(graphfile, &N, &table2D);
	}
	t = omp_get_wtime() - t;
	double t_tot = ((double)t)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nread_graph_from_file1()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	FILE *outfile;
	outfile=fopen("time.txt", "w");
	if(outfile == NULL)
		exit(0);
	fprintf(outfile, "%f", 1000*t_tot);
	fclose(outfile);

	freetable(table2D);

}
//=============================================================================


//=============================================================================
void benchmark_read_graph_from_file2(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark function for 'read_graph_from_file2.c'.
//
// Arguments
// ---------
// *graphfile: filename of web graph as str
// Nrep: number of function call repetitions as int.
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'read_graph_from_file2.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	int *row_ptr;
	int *col_idx;
	int N, N_links;

	double t = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		read_graph_from_file2(graphfile, &N, &N_links, &row_ptr, &col_idx);
	}
	t = omp_get_wtime() - t;
	double t_tot = ((double)t)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\nread_graph_from_file2()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	FILE *outfile;
	outfile=fopen("time.txt", "w");
	if(outfile == NULL)
		exit(0);
	fprintf(outfile, "%f", 1000*t_tot);
	fclose(outfile);

	free(row_ptr);
	free(col_idx);

}
//=============================================================================


//=============================================================================
void benchmark_count_mutual_links1(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark function for 'count_mutual_links1.c'
//
// Arguments
// ---------
// *graphfile: filename of web graph as str
// Nrep: number of function call repetitions as int.
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'count_mutual_links1.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	char **table2D;
	int N, mutual_links;
	read_graph_from_file1(graphfile, &N, &table2D);
	int *num_involvements = calloc((N), sizeof(*num_involvements));
	double t = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		mutual_links = count_mutual_links1(N, table2D, num_involvements);
	}
	t = omp_get_wtime() - t;
	double t_tot = ((double)t)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\ncount_mutual_links1()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	FILE *outfile;
	outfile=fopen("time.txt", "w");
	if(outfile == NULL)
		exit(0);
	fprintf(outfile, "%f", 1000*t_tot);
	fclose(outfile);

	freetable(table2D);
	free(num_involvements);

}
//=============================================================================


//=============================================================================
void benchmark_count_mutual_links2(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark function for 'count_mutual_links2.c'
//
// Arguments
// ---------
// *graphfile: filename of web graph as str
// Nrep: number of function call repetitions as int.
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

	double t = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
	}
	t = omp_get_wtime() - t;
	double t_tot = ((double)t)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\ncount_mutual_links2()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	FILE *outfile;
	outfile=fopen("time.txt", "w");
	if(outfile == NULL)
		exit(0);
	fprintf(outfile, "%f", 1000*t_tot);
	fclose(outfile);

	free(row_ptr);
	free(col_idx);
	free(num_involvements);

}
//=============================================================================


//=============================================================================
void benchmark_calc_top_n_webpages(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark function for 'top_n_webpages.c'
//
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
//
// Arguments
// ---------
// *graphfile: filename of web graph as str
// Nrep: number of function call repetitions as int.
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'top_n_webpages.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	int *row_ptr;
	int *col_idx;
	int N, N_links, mutual_links;
	int n = 100;

	read_graph_from_file2(graphfile, &N, &N_links, &row_ptr, &col_idx);
	int *num_involvements = calloc((N), sizeof(*num_involvements));
	mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

	int *top_results = malloc(n * sizeof(*top_results));

	double t = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		calc_top_n_webpages(N, num_involvements, top_results, n);
	}
	t = omp_get_wtime() - t;
	double t_tot = ((double)t)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\ncalc_top_n_webpages()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	FILE *outfile;
	outfile=fopen("time.txt", "w");
	if(outfile == NULL)
		exit(0);
	fprintf(outfile, "%f", 1000*t_tot);
	fclose(outfile);

	free(row_ptr);
	free(col_idx);
	free(num_involvements);
	free(top_results);

}
//=============================================================================


//=============================================================================
void benchmark_calc_top_n_webpages_serial(char *graphfile, int Nrep)
//----------------------------------------------------------------------------
// Benchmark function for the serial version of 'top_n_webpages.c'
//
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
//
// Arguments
// ---------
// *graphfile: filename of web graph as str
// Nrep: number of function call repetitions as int.
//----------------------------------------------------------------------------
{
	printf("\n-----------------------------------\n");
	printf("Benchmark 'top_n_webpages.c'\n");
	printf("-----------------------------------\n");
	printf("Web graph file: '%s'\n", graphfile);

	int *row_ptr;
	int *col_idx;
	int N, N_links, mutual_links;
	int n = 100;

	read_graph_from_file2(graphfile, &N, &N_links, &row_ptr, &col_idx);
	int *num_involvements = calloc((N), sizeof(*num_involvements));
	mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

	int *top_results = malloc(n * sizeof(*top_results));

	double t = omp_get_wtime();
	for (int i=0; i<Nrep; i++) {
		// This is the serial version of calc_top_n_webpages
		int *num_involvements_cpy = (int *)malloc(N * sizeof(num_involvements_cpy));
		memcpy(num_involvements_cpy, num_involvements, N * sizeof(*num_involvements));
		int top_webpage = 0;
		for (size_t i=0; i<n; i++) {
			for (size_t j=0; j<N; j++) {
				top_webpage = MAXIDX(top_webpage, j, num_involvements_cpy);
			}
			top_results[i] = top_webpage;
			num_involvements_cpy[top_webpage] = -1;
		}
		free(num_involvements_cpy);
	}
	t = omp_get_wtime() - t;
	double t_tot = ((double)t)/Nrep;
	printf("\nTime usage averaged over %d repetitions:\ncalc_top_n_webpages()\
  took %f milliseconds to execute \n\n", Nrep, 1000*t_tot);

	FILE *outfile;
	outfile=fopen("time.txt", "w");
	if(outfile == NULL)
		exit(0);
	fprintf(outfile, "%f", 1000*t_tot);
	fclose(outfile);

	free(row_ptr);
	free(col_idx);
	free(num_involvements);
	free(top_results);

}
//=============================================================================
