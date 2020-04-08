#include "read_graph_from_file2.h"

//=============================================================================
void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx)
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
{
	FILE *datafile;
	int i, j;

	datafile = fopen(filename, "r");

	if (datafile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	fscanf(datafile, "%*[^\n]\n");                   // Skip 1st line
	fscanf(datafile, "%*[^\n]\n");                   // Skip 2nd line
	fscanf(datafile, "%*s %*s %d %*s %d \n", &*N, &*N_links);  // Read 3rd line
	fscanf(datafile, "%*[^\n]\n");                   // Skip 4th line

	*col_idx = calloc((*N_links), sizeof(*col_idx));
	*row_ptr = calloc((*N)+1, sizeof(*row_ptr));

	int *ToNode = calloc((*N_links), sizeof(*ToNode));
	int *FromNode = calloc((*N_links), sizeof(*FromNode));

	for(size_t k = 0; k < *N_links; k++) {
		fscanf(datafile, "%d %d", &j, &i);
		(*row_ptr)[i+1]++;
		ToNode[k] = i;
		FromNode[k] = j;
	}

	for (int i = 1; i < (*N)+1; i++) {
		(*row_ptr)[i] += (*row_ptr)[i-1];
	}

	int *counter = calloc((*N), sizeof(*counter));
	for (size_t i=0; i<*N_links; i++) {
		(*col_idx)[(*row_ptr)[ToNode[i]] + counter[ToNode[i]]] = FromNode[i];
		counter[ToNode[i]]++;
	}

	fclose(datafile);
	free(ToNode);
	free(FromNode);
	free(counter);

}
//=============================================================================
