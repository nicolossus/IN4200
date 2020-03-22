#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


//==================================================
int main(){

	int n=10;
	int arr[n];
	int perm[n];
	for (int i=0; i<n; i++) {
		arr[i] = (rand() % 100) + 1;
		perm[i] = i;
	}

	printf("Original array: ");
	for (int i=0; i<n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	// Permutation sort
	perm_sort(arr, perm, 0, n);
	printf("Perm sorted array: ");
	for (int i=0; i<n; i++) {
		printf("%d ", arr[perm[i]]);
	}
	printf("\n");

	// Regular sort
	sort(arr, 0, n);
	printf("Regular sorted array: ");
	for (int i=0; i<n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
//==================================================
