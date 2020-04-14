//=================================
// Include guard
#ifndef READ_GRAPH_FROM_FILE2_H
#define READ_GRAPH_FROM_FILE2_H

//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <string.h>

//=================================
// Function prototypes
void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx);

#endif // __READ_GRAPH_FROM_FILE2_H_INCLUDED__
