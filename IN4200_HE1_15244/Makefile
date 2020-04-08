
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CC := clang
endif

ifeq ($(UNAME), Linux)
CC := gcc
endif

#CFLAGS := -Wall -std=c11 -O3
CFLAGS := -O3
PROFILE := -pg

DEP = $(wildcard src/*.h)
OBJ = $(wildcard src/*.c)

.PHONY : all clean

main_serial.x : main.c $(DEP)
	$(CC) $< -o $@ $(OBJ) $(CFLAGS)

main_omp.x : main.c $(DEP)
	$(CC) -fopenmp $< -o $@ $(OBJ) $(CFLAGS)

test.x : test.c $(DEP)
	$(CC) $< -o $@ $(OBJ) $(CFLAGS)

benchmark_serial.x : benchmark.c $(DEP)
	$(CC) $< -o $@ $(OBJ) $(CFLAGS)

benchmark_omp.x : benchmark.c $(DEP)
	$(CC) -fopenmp $< -o $@ $(OBJ) $(CFLAGS)

clean:
	rm -f *.o *.x

print-%  : ; @echo $* = $($*)
