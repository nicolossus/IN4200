#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "minmax.h"

typedef struct {
	int n;
	char *times;
	double *temps;
}temperature_data;

int find_maxidx(double*, int);
int find_minidx(double*, int);
double average(double*, int);
double stddev(double*, int, double);
void readfile(char*, temperature_data*);
void read_from_file(char*, temperature_data*);


//============================================================================
int main(){

	temperature_data *data;
	data = (temperature_data *)malloc(sizeof(temperature_data));
	int maxidx, minidx;
	double avg, dev;

	readfile("temperature.txt", data);
	//read_from_file("temperature.txt", data);

	maxidx = find_maxidx(data->temps, data->n);
	minidx = find_minidx(data->temps, data->n);
	avg = average(data->temps, data->n);
	dev = stddev(data->temps, data->n, avg);


	printf("Maxidx: %d\n", maxidx);
	printf("Max Time: %.5s\n", &data->times[5*maxidx]);
	printf("Max Temp: %f\n", data->temps[maxidx]);

	printf("Minidx: %d\n", minidx);
	printf("Min Time: %.5s\n", &data->times[5*minidx]);
	printf("Min Temp: %f\n", data->temps[minidx]);

	printf("Average: %f\n", avg);
	printf("Standard Deviation: %f\n", dev);

	free(data->times);
	free(data->temps);
	free(data);

	return 0;
}
//============================================================================


//============================================================================
void readfile(char *filename, temperature_data *data) {

	int err;
	FILE *datafile;

	datafile = fopen(filename, "r");

	if (datafile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	err = fscanf(datafile, "%d", &data->n);

	data->times = (char *)malloc(5 * data->n * sizeof(char));
	data->temps = (double *)malloc(data->n * sizeof(double));

	for (int i = 0; i < data->n; i++) {
		err = fscanf(datafile, "%5s %lf", &data->times[5 * i], &data->temps[i]);
	}

	fclose(datafile);
}
//============================================================================


//============================================================================
void read_from_file(char *filename, temperature_data *data){

	int datacontent;
	FILE *infile = fopen(filename, "r");

	if (infile == NULL) {
		printf("OH DAMN CANT open file %s\n", filename);
		exit(0);
	}

	datacontent = fscanf(infile, "%d", &data->n);

	data->times = (char *)malloc(5 * data->n * sizeof(char));
	data->temps = (double *)malloc(data->n * sizeof(double));

	for (int i = 0; i < data->n; i++) {
		datacontent = fscanf(infile, "%5s %lf", &data->times[5*i], &data->temps[i]);
	}

}
//============================================================================


//============================================================================
int find_maxidx(double *arr, int n){
	int maxidx = 0;
	for (int i=0; i<n; i++) {
		maxidx = MAXIDX(maxidx, i, arr);
	}
	return maxidx;
}
//============================================================================


//============================================================================
int find_minidx(double *arr, int n){
	int minidx = 0;
	for (int i = 0; i < n; i++) {
		minidx = MINIDX(minidx, i, arr);
	}
	return minidx;
}
//============================================================================


//============================================================================
double average(double *arr, int n){
	double sum = 0;
	for (int i=0; i<n; i++) {
		sum += arr[i];
	}
	return ((double)sum)/n;
}
//============================================================================


//============================================================================
double stddev(double *arr, int n, double avg){
	double dev = 0;
	double nom;
	for (int i = 0; i < n; i++) {
		nom = arr[i] - avg;
		dev += nom * nom;
	}
	dev = sqrt(((double)dev)/(n - 1));
	return dev;
}
//============================================================================
