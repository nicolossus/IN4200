make main_omp.x
export OMP_NUM_THREADS=4
#./main_omp.x "data/8-webpages.txt" 1 8
#./main_omp.x "data/100nodes_graph.txt" 1 10
#./main_omp.x "data/8-webpages.txt" 2 8
#./main_omp.x "data/100nodes_graph.txt" 2 10
./main_omp.x "data/web-NotreDame.txt" 2 10
make clean
