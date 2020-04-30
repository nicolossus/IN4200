
CC := gcc
MPICC := mpicc
CFLAGS := -O3 -std=c11

DEP = $(wildcard src/*.h)
OBJ = $(wildcard src/*.c)

.PHONY : all clean

serial_main.x : serial_main.c $(DEP)
	$(CC) $< -o $@ $(OBJ) $(CFLAGS)

mpi_main.x : mpi_main.c $(DEP)
	$(CC) -fopenmp $< -o $@ $(OBJ) $(CFLAGS)

benchmark.x : benchmark.c $(DEP)
	$(MPICC) $< -o $@ $(OBJ) $(CFLAGS)

clean:
	rm -f *.o *.x
