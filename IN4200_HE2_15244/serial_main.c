//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "src/count_friends_of_ten.h"
#include "src/helperfunc.h"

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
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

	if (strcmp(argv[1], "test") == 0) {
		printf("\n------------------------------\n");
		int **v_test, friends_test;
		test_matrix(&v_test);
		printf("Test matrix with 7 friends of 10:\n");
		print_testmat(v_test);
		friends_test = count_friends_of_ten2(4, 5, v_test);
		printf("Computed total friends in test matrix: %d\n", friends_test);
		free2D(v_test);
		printf("------------------------------\n\n");
	}
	else{
		if (argc < 3) {
			printf("Provide matrix dimensions M (rows) and N (cols) on command line.\n");
			exit(0);
		}
		printf("\n------------------------------\n");
		int M = atoi(argv[1]);
		int N = atoi(argv[2]);
		int **v, friends;
		random_matrix(&v, M, N);
		if ((M*N) < 100) {
			printf("Random %d x %d matrix:\n", M, N);
			printmat(v, M, N);
		}
		else
		{
			printf("Generating a %d x %d random matrix\n", M, N);
		}
		friends = count_friends_of_ten(M, N, v);
		printf("Computed total friends in random matrix: %d\n", friends);
		free2D(v);
		printf("------------------------------\n\n");
	}

	return 0;
}
