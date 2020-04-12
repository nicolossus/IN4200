# IN4200: Home Exam 1, Spring 2020

*Counting Mutual Web Linkage Occurences*

**Candidate: 15244**

**Disclaimer**
This project was embarked on in collaboration with candidate 15224. Hence, our individual  have a strong resemblance in both presentation and content. In particular, figures and tables with corresponding captions are nearly, or in some cases entirely, identical.

### Contents




MAIN PROGRAM
main.c contains procedures for reading a web graph and ranking the top n webpages.
The storage of the web graph data is done by one of two methods:
Method 1 stores the web graph in a 2D table format
Method 2 stores the web graph in the compressed row storage (CRS) format
See the program for further documentation.

Compile: make main
Run: ./main.x webgraph_filename method n
Example run: ./main.x "data/8-webpages.txt" 2 8

TEST PROGRAM
test.c contains procedures for unit testing the functions implemented in the src
folder. See the program for further documentation.

Compile: make test
Run: ./test.x program_filename
Example run: ./test.x "count_mutual_links1.c"
Run all tests: ./test.x "all"

BENCHMARK PROGRAM
benchmark.c contains procedures for benchmarking the performance of the functions
implemented in the src folder. The performance metric is the runtime, which is
averaged from Nrep number of function call repetitions. See the program for
further documentation.

Compile: make benchmark.x
Run: ./benchmark.x program_filename webgraph_filename Nrep
Example run: ./benchmark.x "read_graph_from_file1.c" "data/8-webpages.txt" 100
Run all benchmarks:
Note: With "all", the number of repetitions is hardcoded in the program.

CLEAN DIRECTORY
To clean directory for object files and executables, run make clean
