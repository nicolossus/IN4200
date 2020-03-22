/*
   Write a simple C program that illustrates the speed advantages of reading
   and writing binary data files, compared with using ASCII data files.

   fwrite(addressData, sizeData, numbersData, pointerToFile);

   size_t fread(void *ptr, size_t size_of_elements,
             size_t number_of_elements, FILE *a_file);

   size_t fwrite(const void *ptr, size_t size_of_elements,
              size_t number_of_elements, FILE *a_file);
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void write_binary(double*, int, char*);
void write_ascii(double*, int, char*);
void read_binary(double*, int, char*);
void read_ascii(double*, int, char*);

//=======================================================
int main(){
	clock_t t_wb, t_wa, t_rb, t_ra;
	int n=100000;
	double arr_write[n];
	double arr_readbin[n];
	double arr_readasc[n];


	for (int i=0; i<n; i++) {
		arr_write[i] = (rand() % 100) + 1;
	}

	// Write to binary
	t_wb = clock();
	write_binary(arr_write, n, "binfile.bin");  // function call
	t_wb = clock() - t_wb;
	double time_taken_wb= ((double)t_wb)/CLOCKS_PER_SEC*1000;
	printf("write_binary() took %f milliseconds to execute \n", time_taken_wb);

	// Write to ascii
	t_wa = clock();
	write_ascii(arr_write, n, "asciifile.txt");  // function call
	t_wa = clock() - t_wa;
	double time_taken_wa= ((double)t_wa)/CLOCKS_PER_SEC*1000;
	printf("write_ascii() took %f milliseconds to execute \n", time_taken_wa);

	// Read from binary
	t_rb = clock();
	read_binary(arr_readbin, n, "binfile.bin");  // function call
	t_rb = clock() - t_rb;
	double time_taken_rb = ((double)t_rb)/CLOCKS_PER_SEC*1000;
	printf("read_binary() took %f milliseconds to execute \n", time_taken_rb);

	// Read from ascii
	t_ra = clock();
	read_ascii(arr_readasc, n, "asciifile.txt");  // function call
	t_ra = clock() - t_ra;
	double time_taken_ra = ((double)t_ra)/CLOCKS_PER_SEC*1000;
	printf("read_ascii() took %f milliseconds to execute \n", time_taken_ra);

	// Sanity check (uncomment only with small n)
	/*
	      printf("Binary read:\n");
	      for (int i=0; i<n; i++) {
	              printf("%lf ", arr_readbin[i]);
	      }
	      printf("\n");

	      printf("Ascii read:\n");
	      for (int i=0; i<n; i++) {
	              printf("%lf ", arr_readasc[i]);
	      }
	      printf("\n");
	 */
	return 0;
}
//=======================================================


//=======================================================
void write_binary(double *arr, int n, char *filename){
	FILE *binfile;
	binfile = fopen(filename, "wb");

	if (binfile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	fwrite(arr, sizeof(double), n, binfile);

	fclose(binfile);
}
//=======================================================


//=======================================================
void write_ascii(double *arr, int n, char *filename){
	FILE *asciifile;
	asciifile = fopen(filename, "w");

	if (asciifile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	for (int i=0; i<n; i++) {
		fprintf(asciifile,"%f ", arr[i]);
	}

	fclose(asciifile);
}
//=======================================================


//=======================================================
void read_binary(double *arr, int n, char *filename){
	FILE *binfile;
	binfile = fopen(filename, "rb");

	if (binfile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	fread(arr, sizeof(int), n, binfile);

	fclose(binfile);
}
//=======================================================


//=======================================================
void read_ascii(double *arr, int n, char *filename){
	FILE *asciifile;
	asciifile = fopen(filename, "r");

	if (asciifile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	for (int i=0; i<n; i++) {
		fscanf(asciifile,"%lf", &arr[i]);
	}

	fclose(asciifile);
}
//=======================================================
