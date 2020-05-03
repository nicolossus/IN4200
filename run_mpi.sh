mpicc -o mpi_test ./mpi_test.c
mpirun -np 2 ./mpi_test
rm -f mpi_test
