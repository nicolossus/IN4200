make benchmark.x
#./benchmark.x "read_graph_from_file1.c" "data/8-webpages.txt" 100
#./benchmark.x "read_graph_from_file1.c" "data/100nodes_graph.txt" 100
#./benchmark.x "read_graph_from_file2.c" "data/8-webpages.txt" 100
#./benchmark.x "read_graph_from_file2.c" "data/100nodes_graph.txt" 100
#./benchmark.x "read_graph_from_file2.c" "data/web-NotreDame.txt" 20
#./benchmark.x "count_mutual_links1.c" "data/8-webpages.txt" 100
#./benchmark.x "count_mutual_links1.c" "data/100nodes_graph.txt" 100
#./benchmark.x "count_mutual_links2.c" "data/8-webpages.txt" 100
#./benchmark.x "count_mutual_links2.c" "data/100nodes_graph.txt" 100
#./benchmark.x "count_mutual_links2.c" "data/web-NotreDame.txt" 100
#./benchmark.x "top_n_webpages.c" "data/8-webpages.txt" 50
#./benchmark.x "top_n_webpages.c" "data/100nodes_graph.txt" 50
./benchmark.x "method1" "data/8-webpages.txt" 100
./benchmark.x "method1" "data/100nodes_graph.txt" 100
./benchmark.x "method2" "data/8-webpages.txt" 100
./benchmark.x "method2" "data/100nodes_graph.txt" 100
./benchmark.x "method2" "data/web-NotreDame.txt" 20
make clean
