make benchmark_omp.x
export OMP_NUM_THREADS=4
#./benchmark_omp.x "read_graph_from_file1.c" "data/8-webpages.txt" 100
#./benchmark_omp.x "read_graph_from_file1.c" "data/100nodes_graph.txt" 100
#./benchmark_omp.x "read_graph_from_file2.c" "data/8-webpages.txt" 100
#./benchmark_omp.x "read_graph_from_file2.c" "data/100nodes_graph.txt" 100
#./benchmark_omp.x "read_graph_from_file2.c" "data/web-NotreDame.txt" 20
#./benchmark_omp.x "count_mutual_links1.c" "data/8-webpages.txt" 100
#./benchmark_omp.x "count_mutual_links1.c" "data/100nodes_graph.txt" 1000
#./benchmark_omp.x "count_mutual_links2.c" "data/8-webpages.txt" 100
#./benchmark_omp.x "count_mutual_links2.c" "data/100nodes_graph.txt" 100
#./benchmark_omp.x "count_mutual_links2.c" "data/web-NotreDame.txt" 100
#./benchmark_omp.x "count_mutual_links2.c" "data/web-BerkStan.txt" 100
./benchmark_omp.x "top_n_webpages.c" "data/8-webpages.txt" 50
#./benchmark_omp.x "top_n_webpages.c" "data/100nodes_graph.txt" 50
make clean
