make mpi_main.x
/usr/lib64/openmpi/bin/mpirun -np 3 mpi_main.x "test"
/usr/lib64/openmpi/bin/mpirun -np 4 mpi_main.x 10 10
/usr/lib64/openmpi/bin/mpirun -np 8 mpi_main.x 200 200
make clean
