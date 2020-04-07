//=================================
// Include guard
#ifndef TOP_N_WEBPAGES_H
#define TOP_N_WEBPAGES_H

#define MAXIDX(oldidx, i, arr) (((arr[oldidx]) > (arr[i])) ? (oldidx) : (i))

//=================================
// Include dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <omp.h>

//=================================
// Function prototypes
void top_n_webpages(int num_webpages, int *num_involvements, int n);
void calc_top_n_webpages(int num_webpages, int *num_involvements, int *top_results, int n);
void top_n_webpages_faster(int num_webpages, int *num_involvements, int n);

#endif // __TOP_N_WEBPAGES_H_INCLUDED__
