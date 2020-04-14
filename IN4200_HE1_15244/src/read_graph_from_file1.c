#include "read_graph_from_file1.h"

//=============================================================================
void read_graph_from_file1 (char *filename, int *N, char ***table2D)
//----------------------------------------------------------------------------
// Read web graph and store data as a 2D table. The web graph text file is
// assumed to have the following format:
//     - Line 1 and 2 both start with # and contain free text
//     - Line 3 is of the form "# Nodes: integer1 Edges: integer2", where
//       integer1 is the total number of webpages, denoted N, and integer 2 is
//       the total number of links
//     - Line 4 is of the form "# FromNodeId ToNodeId"
//     - Remaining file consists of a number of lines where each line contains
//       two integers; the index of the outbound webpage and the index of the
//       inbound webpage
//
// About 2D table
// --------------
// A 2D table of dimension NxN is a convenient storage format for a web graph.
// The values in the table are either "0" or "1". If the value in row i and
// column j is "1", it indicates a direct link from webpage j (outbound) to
// webpage i (inbound).
//
// Arguments
// ---------
// *filename: filename of web graph as str
// *N: Address of declared int N
// ***table2D: Address of declared char **table2D
//----------------------------------------------------------------------------
{
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

	// Set table element as 1 if there is a direct link from webpage j (outbound)
	// to webpage i (inbound)
	for (size_t k=0; k<nedges; k++) {
		fscanf(datafile, "%d %d", &j, &i);
		if ((i != j) && (i < (*N)) && (j < (*N)))  {  // Exclude self- and illegal links
			(*table2D)[i][j] = 1;
		}
	}

	fclose(datafile);
}
//=============================================================================
