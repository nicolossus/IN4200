
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CC := clang
endif

ifeq ($(UNAME), Linux)
CC := gcc
endif

CFLAGS = -Wall -std=c11
PROFILE := -pg

DEP = src/helperfunc.h src/read_graph_from_file1.h src/read_graph_from_file2.h
OBJ = src/read_graph_from_file1.c src/read_graph_from_file2.c

.PHONY : all clean

main.x : main.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

test.x : test.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

benchmark.x : benchmark.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

clean:
	rm -f *.o *.x

print-%  : ; @echo $* = $($*)
