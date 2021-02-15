# IN4200: Home Exam 2, Spring 2020

**Finding Triple-friends of 10**

**Candidate: 15244**

In this project, the goal was to develop code for “counting triple-friends of 10”, that is, counting which three neighboring numbers (in the horizontal, vertical, or diagonal directions) that sum up to 10, in a matrix with M rows and N columns of non-negative integers. The implementation is done as both serial and MPI-parallelized code.    

**Disclaimer:**
This project was embarked on in collaboration with candidate 15224. Hence, our individual programs have a strong resemblance in both presentation and content.

### Contents

- The **``src``** folder contains:
  - **``count_friends_of_ten.c``**
    - Serial function that returns the total number of “triple-friends of 10” inside the input 2D array of dimension M x N.
  - **``count_friends_of_ten.h``**
    - Header file for ``count_friends_of_ten.c``.  
  - **``mpi_count_friends_of_ten.c``**
    - MPI-parallelized function that returns the number of “triple-friends of 10” inside a partition of the input 2D array assigned to worker by the master task.
  - **``mpi_count_friends_of_ten.h``**
    - Header file for ``mpi_count_friends_of_ten.c``.    
  - **``helperfunc.h``**
    - Header file containing helper functions for allocating, freeing and printing arrays.

- **``serial_main.c``**:
  - Serial main program. Allocates a 2D array of dimension M x N, assigned with appropriate integer values, and then calls the ``count_friends_of_ten`` to count the number of “triple-friends of 10” in the 2D array.   

- **``mpi_main.c``**:
  - MPI-parallelized main program. Master task allocates a 2D array of dimension M x N, assigned with appropriate integer values, and then calls the ``mpi_count_friends_of_ten`` to distribute array partitions to workers which counts and returns the number of “triple-friends of 10” in their respective partition. The total number of “triple-friends of 10” is found by sum reduction in the main program.

- **``Makefile``**:
  - Compile instructions for both the ``gcc`` (serial code) and ``mpicc`` (parallelized code) compiler.

- **``run_serial_main.sh``**:
  - Instructions for compiling and running the serial main program. Run with ``bash run_serial_main.sh``.

- **``run_mpi_main_macos.sh``**:
  - Instructions for compiling and running the MPI-parallelized main program on macOS. Run with ``bash run_mpi_main_macos.sh``.  

- **``run_mpi_main_ifilinux.sh``**:
  - Instructions for compiling and running the MPI-parallelized main program on IFI's standard Linux server. Run with ``bash run_mpi_main_ifilinux.sh``.   


### Compilation and Usage

- **SERIAL MAIN PROGRAM**
  - Compile:
    - ``make serial_main.x``
  - Run:
    - ``./serial_main.x M N``
  - Example: A 11 x 7 matrix.
    - ``./serial_main.x 11 7``
  - Test: Matrix with known number of friends:  
    - ``./serial_main.x "test"``

- **MPI-PARALLELIZED MAIN PROGRAM**
  - Compile:
    - ``make mpi_main.x``
  - Run:
    - ``mpirun -np <numprocs> mpi_main.x M N``
  - Example: A 11 x 7 input matrix with 1 master and 3 workers
    - ``mpirun -np 4 mpi_main.x 11 7``
  - Test: Matrix with known number of friends:  
    - ``mpirun -np 3 mpi_main.x "test"``  

The MPI capable compiler on IFI's Linux server is ``/usr/lib64/openmpi/bin/mpicc``, and the command for executing a compiled MPI program is ``/usr/lib64/openmpi/bin/mpirun``.    
