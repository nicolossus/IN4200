//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "src/read_graph_from_file1.h"
#include "src/read_graph_from_file2.h"
#include "src/count_mutual_links1.h"
#include "src/count_mutual_links2.h"
#include "src/top_n_webpages.h"
#include "src/helperfunc.h"

//============================================================================
//-------------------------------- MAIN --------------------------------------
//============================================================================
int main(int argc, char *argv[])
//----------------------------------------------------------------------------
// Count mutual web linkage occurrences and rank top n webpages of web graphs.
// Two methods for storing the web graph are deployed:
// 			1. 2D table as storage format
//      2. Compressed row storage (CRS) as storage format
//
// Arguments given on command line
// --------------------------------
// webgraph.txt: filename of web graph as str
// Method: 1 or 2 as int
// n: the number of webpages to rank as int
//----------------------------------------------------------------------------
{

	if (argc < 4) {
		printf("Web graph filename, method (1 or 2) and how many n webpages to rank is required.\n");
		exit(0);
	}

	int flag = atoi(argv[2]);
	int n = atoi(argv[3]);

	if (flag == 1) {
		// Method 1 with 2D table as storage format
		printf("\nMethod 1 with 2D table as storage format\nWeb graph: '%s'\n", argv[1]);

		char **table2D;
		int N, mutual_links;

		read_graph_from_file1(argv[1], &N, &table2D);
		int *num_involvements = calloc((N), sizeof(*num_involvements));
		mutual_links = count_mutual_links1(N, table2D, num_involvements);
		printf("Total number of mutual links: %d\n", mutual_links);
		top_n_webpages(N, num_involvements, n);
		//top_n_webpages_serial_faster(N, num_involvements, n); // this is the fastest

		freetable(table2D);
		free(num_involvements);
	}
	else if (flag==2) {
		// Method 2 with CRS as storage format
		printf("\nMethod 2 with CRS as storage format\nWeb graph: '%s'\n", argv[1]);

		int *row_ptr;
		int *col_idx;
		int N, N_links, mutual_links;

		read_graph_from_file2(argv[1], &N, &N_links, &row_ptr, &col_idx);
		int *num_involvements = calloc((N), sizeof(*num_involvements));
		mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
		printf("Total number of mutual links: %d\n", mutual_links);
		//top_n_webpages(N, num_involvements, n);
		top_n_webpages_serial_faster(N, num_involvements, n);    // this is the fastest

		free(row_ptr);
		free(col_idx);
		free(num_involvements);
	}
	else{
		printf("Please supply which method by 1 or 2 as int on command line");
		exit(0);
	}

	return 0;
}
//============================================================================
