#clang-9 -Xpreprocessor -fopenmp mpi_hw.c -o mpi_hw.x -lomp
#gcc -o mpi_hw.x -openmp mpi_hw.c
gcc -std=c11 -openmp mpi_hw.c -o mpi_hw.x
export OMP_NUM_THREADS=4
./mpi_hw.x
rm -f mpi_hw.x
