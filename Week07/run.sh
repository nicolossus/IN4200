gcc -std=c11 -openmp ex3.c -o ex3.x
export OMP_NUM_THREADS=4
./ex3.x
rm -f ex3.x
