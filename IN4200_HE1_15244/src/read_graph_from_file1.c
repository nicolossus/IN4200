#include "read_graph_from_file1.h"

void read_graph_from_file1 (char *filename, int *N, char ***table2D){

	FILE *datafile;
	int nedges, i, j;

	datafile = fopen(filename, "r");

	if (datafile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	fscanf(datafile, "%*[^\n]\n");                   // Skip 1st line
	fscanf(datafile, "%*[^\n]\n");                   // Skip 2nd line
	fscanf(datafile, "%*s %*s %d %*s %d \n", &*N, &nedges);  // Read 3rd line
	fscanf(datafile, "%*[^\n]\n");                   // Skip 4th line

	// Allocate 2D table initialized with zeros
	*table2D = (char **)calloc((*N), sizeof(char*));
	*table2D[0] = (char *)calloc((*N), (*N)*sizeof(char));

	for(size_t i = 0; i<(*N); i++) {
		(*table2D)[i] = &((*table2D)[0][(*N)*i]);
	}

	// Fill table with 1 if direct link from webpage j (outbound) to webpage i (inbound)
	for (size_t k=0; k<nedges; k++) {
		fscanf(datafile, "%d %d", &j, &i);
		(*table2D)[i][j] = 1;
	}

	fclose(datafile);
}
