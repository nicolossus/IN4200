make benchmark.x
./benchmark.x "read_graph_from_file1.c" "data/8-webpages.txt" 50
./benchmark.x "read_graph_from_file1.c" "data/100nodes_graph.txt" 50
./benchmark.x "read_graph_from_file1.c" "data/web-NotreDame.txt" 1
./benchmark.x "read_graph_from_file2.c" "data/8-webpages.txt" 50
./benchmark.x "read_graph_from_file2.c" "data/100nodes_graph.txt" 50
./benchmark.x "read_graph_from_file2.c" "data/web-NotreDame.txt" 1
make clean
