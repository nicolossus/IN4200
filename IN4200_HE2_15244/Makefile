CC := gcc

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
MPICC := mpicc
endif

ifeq ($(UNAME), Linux)
MPICC := /usr/lib64/openmpi/bin/mpicc
endif

CFLAGS := -O3 -std=c11

DEP_SERIAL = src/helperfunc.h src/count_friends_of_ten.h
OBJ_SERIAL = src/count_friends_of_ten.c

DEP_MPI = src/helperfunc.h src/mpi_count_friends_of_ten.h
#DEP_MPI = src/mpi_count_friends_of_ten.h
OBJ_MPI = src/mpi_count_friends_of_ten.c

#DEP = $(wildcard src/*.h)
#OBJ = $(wildcard src/*.c)

.PHONY : all clean

serial_main.x : serial_main.c $(DEP_SERIAL)
	$(CC) $< -o $@ $(OBJ_SERIAL) $(CFLAGS)

mpi_main.x : ./mpi_main.c $(DEP_MPI)
	$(MPICC) $< -o $@ $(OBJ_MPI) $(CFLAGS)

benchmark.x : ./benchmark.c $(DEP_SERIAL) $(DEP_MPI)
	$(MPICC) $< -o $@ $(OBJ_SERIAL) $(OBJ_MPI) $(CFLAGS)

clean:
	rm -f *.o *.x mpi_main
