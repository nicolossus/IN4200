#include "read_graph_from_file2.h"

void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){

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

	int pos = 0;
	for (size_t i=0; i<*N; i++) {
		for (size_t j=0; j<*N_links; j++) {
			if (ToNode[j] == i) {
				(*col_idx)[pos] = FromNode[j];
				pos++;
			}
		}
	}

	free(ToNode);
	free(FromNode);

}


//==================================================
void swap(int *a, int *b)
{
	int t=*a; *a=*b; *b=t;
}
//==================================================


//==================================================
void sort(int arr[], int beg, int end)
{
	if (end > beg + 1) {
		int piv = arr[beg], l = beg + 1, r = end;
		while (l < r) {
			if (arr[l] <= piv)
				l++;
			else
				swap(&arr[l], &arr[--r]);
		}
		swap(&arr[--l], &arr[beg]);
		sort(arr, beg, l);
		sort(arr, r, end);
	}
}
//==================================================

void perm_sort(int arr[], int perm[], int beg, int end)
{
	if (end > beg + 1) {
		int piv = arr[perm[beg]], l = beg + 1, r = end;
		while (l < r) {
			if (arr[perm[l]] <= piv)
				l++;
			else
				swap(&perm[l], &perm[--r]);
		}
		swap(&perm[--l], &perm[beg]);
		perm_sort(arr, perm, beg, l);
		perm_sort(arr, perm, r, end);
	}
}
