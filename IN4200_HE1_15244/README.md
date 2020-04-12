# IN4200: Home Exam 1, Spring 2020

**Counting Mutual Web Linkage Occurences**

**Candidate: 15244**

In this project, the goal was to develop code for reading and storing web graphs, as well as counting mutual web linkage occurrences and ranking the top n webpages. Functions for the two latter procedures are implemented as both serial and parallelized (with OpenMP) code.

**Disclaimer:**
This project was embarked on in collaboration with candidate 15224. Hence, our individual programs have a strong resemblance in both presentation and content.

### Contents

- The **``data``** folder contains:
  - **``8-webpages.txt``**
    - small and simple web graph used to test and verify the implementation.
  - **``100nodes_graph.txt``**
    - slightly larger web graph than the one above. Also used to verify the implementation.
  - **``web-NotreDame.txt``**
    - real-world web graph
  - **``webgraphs_download_instructions.txt``**
    - links to other, as well as the aforementioned, web graphs used in the benchmarking.

- The **``report``** folder contains:
  - **``in3200_in4200_home_exam1_v20.pdf``**
    - project description.
  - **``IN4200__Home_Exam_1.pdf``**
    - project report.

- The **``results``** folder contains:
  - **``test_results.txt``**
    - results from running the test program for all implemented functions. Reproduce output with ``bash run_test.sh``.
  - **``benchmark_read_graph.txt``**
    - benchmark results for the functions ``read_graph_from_file1`` and ``read_graph_from_file2``. Reproduce output with ``bash run_benchmark.sh``.
  - **``count1_test_set.png``**
    - Plot of benchmark results with varying number of threads for the function ``count_mutual_links1`` with web graphs ``8-webpages.txt`` and ``100nodes_graph.txt``.
  - **``count2_test_set.png``**
    - Plot of benchmark results with varying number of threads for the function ``count_mutual_links2`` with web graphs ``8-webpages.txt`` and ``100nodes_graph.txt``.
  - **``count2_real_set.png``**
    - Plot of benchmark results with varying number of threads for the function ``count_mutual_links2`` with web graphs ``web-NotreDame.txt``, ``web-Stanford`` and ``web-BerkStan.txt``.
  - **``top_n_test_set.png``**
    - Plot of benchmark results with varying number of threads for the function ``top_n_webpages`` with web graphs ``8-webpages.txt`` and ``100nodes_graph.txt``.
  - **``top_n_real_set.png``**
    - Plot of benchmark results with varying number of threads for the function ``top_n_webpages`` with web graphs ``web-NotreDame.txt``, ``web-Stanford.txt`` and ``web-BerkStan.txt``.
  - **``main_serial_output.txt``**
    - output from main when running the code in serial. Reproduce output with ``bash run_main_serial.sh``.
  - **``main_omp_output.txt``**
    - output from main when running the code in parallel. Reproduce output with ``bash run_main_omp.sh``.





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
