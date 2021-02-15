gcc -std=c11 -Xpreprocessor -fopenmp -lomp main.c -o main.x -O3
export OMP_NUM_THREADS=4
./main.x
rm -f main.x
