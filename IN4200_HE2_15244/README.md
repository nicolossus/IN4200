# IN4200: Home Exam 2, Spring 2020

**Finding Triple-friends of 10**

**Candidate: 15244**

In this project, the goal was to develop code for "counting triple-friends of 10", that is, counting which three neighboring numbers (in the horizontal, vertical, or diagonal directions) that sum up to 10, in a matrix with M rows and N columns of non-negative integers. The implementation is done as both serial and MPI-parallelized code.    

**Disclaimer:**
This project was embarked on in collaboration with candidate 15224. Hence, our individual programs have a strong resemblance in both presentation and content.

### Contents

- The **``src``** folder contains:
  - **``count_friends_of_ten.c``**
    - Serial function that that returns the total number of “triple-friends of 10” inside the input 2D array of dimension M x N.
  - **``count_friends_of_ten.h``**
    - Header file for ``count_friends_of_ten.c``.  
  - **``mpi_count_friends_of_ten.c``**
    - Read and store web graph in CRS format.
  - **``mpi_count_friends_of_ten.h``**
    - Header file for ``mpi_count_friends_of_ten.c``.    
  - **``helperfunc.h``**
    - Header file containing helper functions for allocating, freeing and printing arrays

- **``serial_main.c``**:
  - Main program. Contains procedures for ranking the top n webpages for a given web graph, and lets the user choose which storage format to use.
