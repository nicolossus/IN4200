export PMIX_MCA_gds=hash
make mpi_main.x
mpirun -np 3 --use-hwthread-cpus mpi_main.x "test"
mpirun -np 3 --use-hwthread-cpus mpi_main.x 10 10
make clean
