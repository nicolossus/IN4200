#include "read_graph_from_file2.h"

//=============================================================================
void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx)
//----------------------------------------------------------------------------
// Read web graph and store data in compressed row storage (CRS) format.
// The web graph text file is assumed to have the following format:
//     - Line 1 and 2 both start with # and contain free text
//     - Line 3 is of the form "# Nodes: integer1 Edges: integer2", where
//       integer1 is the total number of webpages, denoted N, and integer 2 is
//       the total number of links, denoted N_links.
//     - Line 4 is of the form "# FromNodeId ToNodeId"
//     - Remaining file consists of a number of lines where each line contains
//       two integers; the index of the outbound webpage and the index of the
//       inbound webpage
//
// About CRS
// ---------
// A 2D table element is only set to 1 if there is a direct link. In most cases
// N_links is relatively small compared to N, which means that most of the
// values in the 2D will be zero. This can result in a huge waste of storage.
// By adopting the compressed row storage (CRS) format, the waste is avoided.
// The idea is that two 1D arrays of integer values are enough to store the
// data. The col_idx array of length N_links stores, row by row, the column
// indices corresponding to all the direct links. The row_ptr array of length
// N+1 contains the indices at which new rows start in col_idx. Usually there
// is also a val array of length N_links which contains the values, but since
// values are 1 if there is a direct link and zero else it is not needed.
//
// Arguments
// ---------
// *filename: filename of web graph as str
// *N: Address of declared int N
// *N_links: Address of declared int N_links
// **row_ptr: Address of declared int *row_ptr
// **col_idx: Address of declared int *col_idx
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

	// Allocate col_idx and row_ptr initialized with zeros
	*col_idx = calloc((*N_links), sizeof(*col_idx));
	*row_ptr = calloc((*N)+1, sizeof(*row_ptr));

	// Allocate ToNode and FromNode initialized with zeros. These arrays are for
	// storing the the indices of inbound and outbound webpages
	int *ToNode = calloc((*N_links), sizeof(*ToNode));
	int *FromNode = calloc((*N_links), sizeof(*FromNode));

	// Allocate counter initialized with zeros. This array is for ensuring
	// correct index offset when row_ptr is used to access col_idx in the
	// creation of the latter
	int *counter = calloc((*N), sizeof(*counter));

	for(size_t k = 0; k < *N_links; k++) {
		fscanf(datafile, "%d %d", &j, &i);
		(*row_ptr)[i+1]++;  // count the number of direct links
		ToNode[k] = i;
		FromNode[k] = j;
	}

	// Cumulative summation yielding the indices at which new rows start in col_idx
	for (int i = 1; i < (*N)+1; i++) {
		(*row_ptr)[i] += (*row_ptr)[i-1];
	}

	// Use row_ptr to access the row corresponding to a direct link. The counter
	// ensures that no values in col_idx is overwritten by offsetting the row
	// indices if already accessed.
	for (size_t i=0; i<*N_links; i++) {
		printf("ToNode[i] = %d\n", ToNode[i]);
		printf("counter[ToNode[i]] = %d\n", counter[ToNode[i]]);
		printf("row_ptr = %d\n", (*row_ptr)[ToNode[i]] + counter[ToNode[i]]);
		(*col_idx)[(*row_ptr)[ToNode[i]] + counter[ToNode[i]]] = FromNode[i];
		counter[ToNode[i]]++;
	}

	fclose(datafile);
	// Deallocate helper arrays
	free(ToNode);
	free(FromNode);
	free(counter);

}
//=============================================================================
