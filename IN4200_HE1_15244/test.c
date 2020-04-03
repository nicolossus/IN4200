//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include "src/read_graph_from_file1.h"
#include "src/helperfunc.h"

//=================================
// Function prototypes
int test_read_graph1();


//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
//----------------------------------------------------------------------------
// Test implemented functions. Specify filename of
//----------------------------------------------------------------------------
{
	if (argc < 2) {
		printf("Filename required. Provide 'all' to test all, else specify which file.\n");
		exit(0);
	}

	int passed_tests=0;
	int total_tests;

	if (strcmp(argv[1], "read_graph_from_file1.c") == 0)
	{
		passed_tests = test_read_graph1();
		total_tests = 3;
	}
	else if (strcmp(argv[1], "read_graph_from_file2.c") == 0)
	{
		//execute your code
		total_tests = 3; //????
	}
	else if (strcmp(argv[1], "all") == 0) {
		test_read_graph1();
		total_tests = 3;
	}
	else
	{
		printf("Provided filename not valid. Provide one of the following:\n" );
		printf("'read_graph_from_file1.c'\n'read_graph_from_file2.c'\n");
		printf("'all' to test all\n");
		exit(0);
	}

	printf("\nMain() passed %d test(s) of %d total\n\n", passed_tests, total_tests);

	return 0;
}
//============================================================================


//=============================================================================
int test_read_graph1()
//----------------------------------------------------------------------------
// Test function for 'read_graph_from_file1.c'
//----------------------------------------------------------------------------
{
	printf("\n------------------------------\n");
	printf("Test 'read_graph_from_file1.c'\n");
	printf("------------------------------\n");
	printf("Graph file: 'test_graph.txt' located in data folder\n");

	int passed_tests = 0;

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


	read_graph_from_file1("data/test_graph.txt", &N, &table2D);

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
		passed_tests += 1;
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
	int counter = 0;
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			if (table2D_expected[i][j] != table2D[i][j]) {
				printf("Failed test 'Compare table2D'. Entries don't match expectation.\n");
				counter = 1;
			}
		}
	}
	if (counter == 0) {
		printf("Passed test 'Compare table2D'. Entries matched expectation.\n");
		passed_tests += 1;
	}
	printf("Read table:\n");
	printmat(table2D, N, N);

	return passed_tests;
}
//=============================================================================
