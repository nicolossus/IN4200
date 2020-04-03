CC := gcc
CFLAGS = -Wall
PROFILE := -pg

DEP = src/helperfunc.h src/read_graph_from_file1.h
OBJ = src/read_graph_from_file1.c

.PHONY : all clean

main.x : main.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

test.x : test.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

clean:
	rm -f *.o *.x
