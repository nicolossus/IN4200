//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/count_friends_of_ten.h"
#include "src/helperfunc.h"

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
//----------------------------------------------------------------------------
// Find the total number of "triple-friends of 10" in a 2D array (matrix) of
// dimension M x N.
//
// Arguments given on command line
// --------------------------------
// Standard use: M (number of matrix rows) and N (number of matrix columns)
// Test case: "test"
//----------------------------------------------------------------------------
{

	if (strcmp(argv[1], "test") == 0) {
		int **v_test, friends_test;
		test_matrix(&v_test);
		printf("\nTest matrix with 7 friends of 10:\n");
		print_testmat(v_test);
		friends_test = count_friends_of_ten(4, 5, v_test);
		printf("Total friends counted in test matrix: %d\n\n", friends_test);
		free2D(v_test);
	}
	else{
		if (argc < 3) {
			printf("Provide matrix dimensions M (rows) and N (cols) on command line.\n");
			exit(0);
		}
		int M = atoi(argv[1]);
		int N = atoi(argv[2]);
		int **v, friends;
		random_matrix(&v, M, N);
		if ((M*N) < 101) {
			printf("\nRandom %d x %d matrix:\n", M, N);
			printmat(v, M, N);
		}
		else
		{
			printf("\nGenerating a %d x %d random matrix\n", M, N);
		}
		friends = count_friends_of_ten(M, N, v);
		printf("Total friends counted in random matrix: %d\n\n", friends);
		free2D(v);
	}

	return 0;
}
