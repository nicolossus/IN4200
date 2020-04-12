clang -fopenmp omp_test.c -o omp_test.x
export OMP_NUM_THREADS=1
./omp_test.x
rm -f omp_test.x
