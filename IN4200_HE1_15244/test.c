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
int test_read_graph_from_file1();
int test_read_graph_from_file2();
int test_count_mutual_links1();
int test_count_mutual_links2();
int test_calc_top_n_webpages();


//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
//----------------------------------------------------------------------------
// Test implemented functions.
//
// Parameters given on command line
// --------------------------------
// program.c: filename of program with function to be tested
//----------------------------------------------------------------------------
{
	if (argc < 2) {
		printf("Program filename required. Provide 'all' to test all, else specify which file.\n");
		exit(0);
	}

	int passed_tests=0;
	int total_tests;

	if (strcmp(argv[1], "read_graph_from_file1.c") == 0)
	{
		passed_tests = test_read_graph_from_file1();
		total_tests = 3;
	}
	else if (strcmp(argv[1], "read_graph_from_file2.c") == 0)
	{
		passed_tests = test_read_graph_from_file2();
		total_tests = 4;
	}
	else if (strcmp(argv[1], "count_mutual_links1.c") == 0)
	{
		passed_tests = test_count_mutual_links1();
		total_tests = 2;
	}
	else if (strcmp(argv[1], "count_mutual_links2.c") == 0)
	{
		passed_tests = test_count_mutual_links2();
		total_tests = 2;
	}
	else if (strcmp(argv[1], "top_n_webpages.c") == 0)
	{
		passed_tests = test_calc_top_n_webpages();
		total_tests = 1;
	}
	else if (strcmp(argv[1], "all") == 0) {
		passed_tests = test_read_graph_from_file1();
		passed_tests += test_read_graph_from_file2();
		passed_tests += test_count_mutual_links1();
		passed_tests += test_count_mutual_links2();
		passed_tests += test_calc_top_n_webpages();
		total_tests = 12;
	}
	else
	{
		printf("Provided filename not valid. Provide one of the following:\n" );
		printf("'read_graph_from_file1.c'\n'read_graph_from_file2.c'\n\
		'count_mutual_links1.c'\n'count_mutual_links2.c'\n'top_n_webpages.c'");
		printf("'all' to test all\n");
		exit(0);
	}

	printf("\nMain() passed %d test(s) of %d total\n\n", passed_tests, total_tests);

	return 0;
}
//============================================================================


//=============================================================================
int test_read_graph_from_file1()
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file1.c'
//----------------------------------------------------------------------------
{
	printf("\n------------------------------\n");
	printf("Test 'read_graph_from_file1.c'\n");
	printf("------------------------------\n");
	printf("Web graph file: '8-webpages.txt' located in data folder\n");

	int passed_tests = 0;
	clock_t t;

	char table2D_expected[8][8] = {
		{0, 0, 0, 0, 0, 0, 1, 0},
		{1, 0, 1, 1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0, 1, 0},
		{0, 0, 0, 1, 1, 0, 0, 1},
		{0, 0, 0, 0, 1, 0, 0, 1},
		{0, 0, 0, 0, 1, 1, 1, 0}
	};

	char **table2D;
	int N;
	int nedges=0;

	t = clock();
	read_graph_from_file1("data/8-webpages.txt", &N, &table2D);
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC;
	printf("\nTime usage:\nread_graph_from_file1() took %f milliseconds to execute \n\n", 1000*t_tot);

	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < N; ++j) {
			if (table2D[i][j] == 1) {
				nedges += 1;
			}
		}
	}

	// Test: Read number of nodes
	if (N == 8) {
		printf("Passed test 'Read number of nodes'. Expected: 8. Found: %d\n", N);
		passed_tests += 1;
	}
	else
	{
		printf("Failed test 'Read number of nodes'. Expected: 8. Found: %d\n", N);
	}

	// Test: Read number of edges
	if (nedges == 17) {
		printf("Passed test 'Read number of edges'. Expected: 17. Found: %d\n", nedges);
		passed_tests += 1;
	}
	else
	{
		printf("Failed test 'Read number of edges'. Expected: 17. Found: %d\n", nedges);
	}

	// Test: Compare read table2D vs expected
	int flag = 0;
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			if (table2D_expected[i][j] != table2D[i][j]) {
				flag = 1;
			}
		}
	}
	if (flag == 0) {
		printf("Passed test 'Compare table2D'. Entries matched expectation.\n");
		passed_tests += 1;
	}
	else{
		printf("Failed test 'Compare table2D'. Entries don't match expectation.\n");
	}
	printf("Read table:\n");
	printmat(table2D, N, N);
	freetable(table2D);

	return passed_tests;
}
//=============================================================================


//=============================================================================
int test_read_graph_from_file2()
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file1.c'
//----------------------------------------------------------------------------
{
	printf("\n------------------------------\n");
	printf("Test 'read_graph_from_file2.c'\n");
	printf("------------------------------\n");
	printf("Web graph file: '8-webpages.txt' located in data folder\n");

	int passed_tests = 0;
	clock_t t;

	int col_idx_expected[17] = {6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6};
	int row_ptr_expected[9] = {0, 1, 4, 5, 6, 9, 12, 14, 17};

	int *row_ptr;
	int *col_idx;
	int N, N_links;

	t = clock();
	read_graph_from_file2("data/8-webpages.txt", &N, &N_links, &row_ptr, &col_idx);
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC;
	printf("\nTime usage:\nread_graph_from_file2() took %f milliseconds to execute \n\n", 1000*t_tot);


	// Test: Read number of nodes
	if (N == 8) {
		printf("Passed test 'Read number of nodes'. Expected: 8. Found: %d\n", N);
		passed_tests += 1;
	}
	else
	{
		printf("Failed test 'Read number of nodes'. Expected: 8. Found: %d\n", N);
	}

	// Test: Read number of edges
	if (N_links == 17) {
		printf("Passed test 'Read number of edges'. Expected: 17. Found: %d\n", N_links);
		passed_tests += 1;
	}
	else
	{
		printf("Failed test 'Read number of edges'. Expected: 17. Found: %d\n", N_links);
	}

	// Test: Compare read row_ptr vs expected
	int flag = 0;
	for (size_t i=0; i<N+1; i++) {
		if (row_ptr_expected[i] != row_ptr[i])
		{
			flag = 1;
		}
	}
	if (flag == 0) {
		printf("Passed test 'Compare row_ptr'. Entries matched expectation.\n");
		passed_tests += 1;
	}
	else{
		printf("Failed test 'Compare row_ptr'. Entries don't match expectation.\n");
	}

	printf("Read row_ptr:\n");
	printvec(row_ptr, N+1);

	// Test: Compare read col_idx vs expected
	int flag2 = 0;
	for (size_t i=0; i<N_links; i++) {
		if (col_idx_expected[i] != col_idx[i])
		{
			flag2 = 1;
		}
	}
	if (flag2 == 0) {
		printf("Passed test 'Compare col_idx'. Entries matched expectation.\n");
		passed_tests += 1;
	}
	else{
		printf("Failed test 'Compare col_idx'. Entries don't match expectation.\n");
	}
	printf("Read col_idx:\n");
	printvec(col_idx, N_links);

	free(row_ptr);
	free(col_idx);

	return passed_tests;
}
//=============================================================================


//=============================================================================
int test_count_mutual_links1()
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file1.c'
//----------------------------------------------------------------------------
{
	printf("\n------------------------------\n");
	printf("Test 'count_mutual_links1.c'\n");
	printf("------------------------------\n");
	printf("Web graph file: '8-webpages.txt' located in data folder\n");

	int passed_tests = 0;
	clock_t t;

	int num_involvements_expected[8] = {2, 0, 4, 6, 5, 2, 4, 3};

	char **table2D;
	int N, mutual_links;
	read_graph_from_file1("data/8-webpages.txt", &N, &table2D);
	int *num_involvements = calloc((N), sizeof(*num_involvements));
	t = clock();
	mutual_links = count_mutual_links1(N, table2D, num_involvements);
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC;
	printf("\nTime usage:\ncount_mutual_links1() took %f milliseconds to execute \n\n", 1000*t_tot);

	// Test: Count mutual links
	if (mutual_links == 13) {
		printf("Passed test 'Count mutual links'. Expected: 13. Found: %d\n", mutual_links);
		passed_tests += 1;
	}
	else
	{
		printf("Failed test 'Count mutual links'. Expected: 13. Found: %d\n", mutual_links);
	}

	// Test: Compare counted num_involvements vs expected
	int flag = 0;
	for (size_t i=0; i<N; i++) {
		if (num_involvements_expected[i] != num_involvements[i])
		{
			flag = 1;
		}
	}
	if (flag == 0) {
		printf("Passed test 'Compare num_involvements'. Entries matched expectation.\n");
		passed_tests += 1;
	}
	else{
		printf("Failed test 'Compare num_involvements'. Entries don't match expectation.\n");
	}

	printf("Counted num_involvements:\n");
	printvec(num_involvements, N);

	freetable(table2D);
	free(num_involvements);

	return passed_tests;
}
//=============================================================================


//=============================================================================
int test_count_mutual_links2()
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file2.c'
//----------------------------------------------------------------------------
{
	printf("\n------------------------------\n");
	printf("Test 'count_mutual_links2.c'\n");
	printf("------------------------------\n");
	printf("Web graph file: '8-webpages.txt' located in data folder\n");

	int passed_tests = 0;
	clock_t t;

	int num_involvements_expected[8] = {2, 0, 4, 6, 5, 2, 4, 3};

	int *row_ptr;
	int *col_idx;
	int N, N_links, mutual_links;

	read_graph_from_file2("data/8-webpages.txt", &N, &N_links, &row_ptr, &col_idx);
	int *num_involvements = calloc((N), sizeof(*num_involvements));
	t = clock();
	mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC;
	printf("\nTime usage:\ncount_mutual_links2() took %f milliseconds to execute \n\n", 1000*t_tot);

	// Test: Count mutual links
	if (mutual_links == 13) {
		printf("Passed test 'Count mutual links'. Expected: 13. Found: %d\n", mutual_links);
		passed_tests += 1;
	}
	else
	{
		printf("Failed test 'Count mutual links'. Expected: 13. Found: %d\n", mutual_links);
	}

	// Test: Compare counted num_involvements vs expected
	int flag = 0;
	for (size_t i=0; i<N; i++) {
		if (num_involvements_expected[i] != num_involvements[i])
		{
			flag = 1;
		}
	}
	if (flag == 0) {
		printf("Passed test 'Compare num_involvements'. Entries matched expectation.\n");
		passed_tests += 1;
	}
	else{
		printf("Failed test 'Compare num_involvements'. Entries don't match expectation.\n");
	}

	printf("Counted num_involvements:\n");
	printvec(num_involvements, N);

	free(row_ptr);
	free(col_idx);
	free(num_involvements);

	return passed_tests;
}
//=============================================================================


//=============================================================================
int test_calc_top_n_webpages()
//----------------------------------------------------------------------------
// Test function for 'top_n_webpages.c'
//----------------------------------------------------------------------------
{
	printf("\n------------------------------\n");
	printf("Test 'top_n_webpages.c'\n");
	printf("------------------------------\n");
	printf("Web graph file: '8-webpages.txt' located in data folder\n");

	int passed_tests = 0;
	clock_t t;

	int top_results_expected[8] = {3, 4, 6, 2, 7, 5, 0, 1};

	char **table2D;
	int N, mutual_links;
	int n = 8;
	read_graph_from_file1("data/8-webpages.txt", &N, &table2D);
	int *num_involvements = calloc((N), sizeof(*num_involvements));
	mutual_links = count_mutual_links1(N, table2D, num_involvements);
	int *top_results = malloc(n * sizeof(*top_results));

	t = clock();
	calc_top_n_webpages(N, num_involvements, top_results, n);
	t = clock() - t;
	double t_tot = ((double)t)/CLOCKS_PER_SEC;
	printf("\nTime usage:\ncalc_top_n_webpages() took %f milliseconds to execute \n\n", 1000*t_tot);

	// Test: Compare calculated top_results vs expected
	int flag = 0;
	for (size_t i=0; i<n; i++) {
		if (top_results_expected[i] != top_results[i])
		{
			flag = 1;
		}
	}
	if (flag == 0) {
		printf("Passed test 'Compare top_results'. Entries matched expectation.\n");
		passed_tests += 1;
	}
	else{
		printf("Failed test 'Compare top_results'. Entries don't match expectation.\n");
	}

	printf("Calculated top_results:\n");
	printvec(top_results, n);

	freetable(table2D);
	free(num_involvements);
	free(top_results);

	return passed_tests;
}
//=============================================================================
