export PMIX_MCA_gds=hash
make mpi_main.x
#mpirun -np 3 --use-hwthread-cpus mpi_main.x 4 5
mpirun -np 2 mpi_main.x 4 5
make clean
