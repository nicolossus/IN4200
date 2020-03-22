#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void smooth (double **v_new, double **v, int n, int m, double c){
	for (int i=1; i<n-1; i++) {
		for (int j=1; j<m-1; j++) {
			v_new[i][j] = v[i][j] + c*(v[i-1][j] + v[i][j-1] - 4*v[i][j] + v[i][j+1] + v[i+1][j]);
		}
	}
}
