# IN4200: Home Exam 1, Spring 2020

**Counting Mutual Web Linkage Occurences**

**Candidate: 15244**

In this project, the goal was to develop code for reading and storing web graphs, as well as counting mutual web linkage occurrences and ranking the top n webpages. Functions for the two latter procedures are implemented as both serial and parallelized (with OpenMP) code. Two methods for storing the web graph are deployed:

	1. 2D table as storage format
  
  2. Compressed row storage (CRS) as storage format

**Disclaimer:**
This project was embarked on in collaboration with candidate 15224. Hence, our individual programs have a strong resemblance in both presentation and content.

**WARNING:** To run the parallelized code on IFI machines a change must be made in ``count_mutual_links2.c``. Array reduction is only possible with OpenMP 4.5, which is not installed on IFI's student server. The code runs with the pragma declaration without num_involvements[:N] in the reduction, but this does not always yield the correct results. To run on IFI machines, change which #pragma is commented out.

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

- The **``src``** folder contains:
  - **``read_graph_from_file1.c``**
    - Read and store web graph in 2D table format.
  - **``read_graph_from_file1.h``**
    - Header file for ``read_graph_from_file1.c``.  
  - **``read_graph_from_file2.c``**
    - Read and store web graph in CRS format.
  - **``read_graph_from_file2.h``**
    - Header file for ``read_graph_from_file2.c``.   
  - **``count_mutual_links1.c``**
    - Count number of mutual webpage linkages and the number of times that a webpage is involved as outbound for the mutual web linkages. The function in this program uses the web graph stored in the 2D table format and contains both serialized and parallelized version.
  - **``count_mutual_links1.h``**
    - Header file for ``count_mutual_links1.c``.  
  - **``count_mutual_links2.c``**
    - Count number of mutual webpage linkages and the number of times that a webpage is involved as outbound for the mutual web linkages. The function in this program uses the web graph stored in the CRS format and contains both serialized and parallelized version.
  - **``count_mutual_links2.h``**
    - Header file for ``count_mutual_links2.c``.
  - **``top_n_webpages.c``**
    - Find the top n webpages with respect to the number of involvements in mutual linkages. Results are printed to screen. The program contains both serialized and parallelized version.
  - **``top_n_webpages.h``**
    - Header file for ``top_n_webpages.c``.  
  - **``helperfunc.h``**
    - Header file containing helper functions for freeing 2D arrays and nicely printing both 1D and 2D arrays.  

- **``main.c``**:
  - Main program. Contains procedures for ranking the top n webpages for a given web graph, and lets the user choose which storage format to use.

- **``test.c``**:
  - Test program. Contains procedures for unit testing all implemented functions.

- **``benchmark.c``**:
  - Benchmark program. Contains procedures for benchmarking all implemented functions. The performance metric is the runtime, which is averaged over *Nrep* number of function call repetitions.

- **``benchmark_automation.py``**:
  - Program that automates the benchmarking and produces plots of the time usage as a function of varying number of threads for selected web graphs. Run with ``python3 benchmark_automation.py``.

- **``Makefile``**:
  - Compile instructions for both the ``gcc`` and ``clang`` compiler.

- **``run_main_serial.sh``**:
  - Instructions for compiling and running the main program with serial versions of the code. Run with ``bash run_main_serial.sh``.

- **``run_main_omp.sh``**:
  - Instructions for compiling and running the main program with parallelized versions of the code. Run with ``bash run_main_omp.sh``.  

- **``run_test.sh``**:
  - Instructions for compiling and running all unit tests. Run with ``bash run_test.sh``.  

- **``run_benchmark.sh``**:
  - Instructions for compiling and running all benchmarks of ``read_graph_from_file1`` and ``read_graph_from_file2``. Run with ``bash run_benchmark.sh``.    

### Compile and usage

- **MAIN PROGRAM - Serial version**
  - Compile:
    - ``make main_serial.x``
  - Run: ``./main.x webgraph_filename method n``
  - Example: Method 1 with 2D table as storage format for finding the top 8 webpages in ``8-webpages.txt``.
    - ``./main.x "data/8-webpages.txt" 1 8``
  - Example: Method 2 with CRS as storage format for finding the top 10 webpages in ``100nodes-graph.txt``.
    - ``./main.x "data/8-webpages.txt" 2 10``

- **MAIN PROGRAM - Parallelized version**
  - Compile:
    - ``make main_omp.x``
  - Run:
    - ``export OMP_NUM_THREADS=N``
    - ``./main.x webgraph_filename method n``
  - Example:
    - ``export OMP_NUM_THREADS=4``
    - ``./main.x "data/8-webpages.txt" 2 8``

- **TEST PROGRAM**  
  - Compile:
    - ``make test.x``
  - Run:
    - ``./test.x program_filename``
  - Example:
    - ``./test.x "count_mutual_links1.c"``
  - Run all tests:
    - ``./test.x "all"``

- **BENCHMARK PROGRAM**  
  - Compile:
    - ``make benchmark.x``
  - Run:
    - ``./benchmark.x program_filename webgraph_filename Nrep``
  - Example:
    - ``./benchmark.x "read_graph_from_file1.c" "data/8-webpages.txt" 100``

- **CLEAN DIRECTORY**  
  - To clean directory for object files, executables and output text files:
    - ``make clean``
