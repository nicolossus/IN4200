make benchmark.x
./benchmark.x "read_graph_from_file1.c" "data/8-webpages.txt" 10000
./benchmark.x "read_graph_from_file1.c" "data/100nodes_graph.txt" 10000
./benchmark.x "read_graph_from_file2.c" "data/8-webpages.txt" 10000
./benchmark.x "read_graph_from_file2.c" "data/100nodes_graph.txt" 10000
./benchmark.x "read_graph_from_file2.c" "data/web-NotreDame.txt" 20
./benchmark.x "read_graph_from_file2.c" "data/web-Stanford.txt" 20
./benchmark.x "read_graph_from_file2.c" "data/web-BerkStan.txt" 10
make clean
rm -f time.txt
