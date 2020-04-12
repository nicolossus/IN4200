#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
This program contains procedures for compiling and benchmarking all the
functions in this project
"""

import os

import numpy as np
import matplotlib.pyplot as plt

# Set fontsizes in figures
params = {'legend.fontsize': 'large',
          'axes.labelsize': 'large',
          'axes.titlesize': 'large',
          'xtick.labelsize': 'large',
          'ytick.labelsize': 'large'}
plt.rcParams.update(params)


# Set path to save the figures and data files
FIGURE_PATH = "./results"


def fig_path(fig_id):
    """
    Input name of figure to load or save with extension as dtype str
    """
    return os.path.join(FIGURE_PATH + "/", fig_id)


def benchmark(graphfiles, filename, Nrep, max_nthreads, fsave, show=False):
    """
    Benchmark all parallelized functions with varying number of threads
    """
    os.system('make benchmark.x')
    fig = plt.figure(figsize=(8, 6))
    for graphfile in graphfiles:
        times = np.zeros(max_nthreads)
        threads = np.linspace(1, max_nthreads, max_nthreads, dtype=np.int)
        for i in range(max_nthreads):
            if filename == "top_n_webpages.c" and i == 0:
                special_case = "top_n_webpages_serial.c"
                print(f"=> Run with {i+1} threads <=")
                os.system('export OMP_NUM_THREADS=' + str(i + 1))
                os.system('./benchmark_omp.x ' + special_case + " " +
                          graphfile + " " + str(Nrep))
                times[i] = np.loadtxt('time.txt')
            else:
                print(f"=> Run with {i+1} threads <=")
                os.system('export OMP_NUM_THREADS=' + str(i + 1))
                os.system('./benchmark_omp.x ' + filename + " " +
                          graphfile + " " + str(Nrep))
                times[i] = np.loadtxt('time.txt')

        plt.plot(threads, times, 'o:', label=graphfile[5:])
    plt.title("Benchmark of " + filename)
    plt.xlabel("Number of threads")
    plt.ylabel("Time [ms]")
    plt.legend(loc='best')
    if show:
        plt.show()
    fig.savefig(fig_path(fsave), dpi=300)

    os.system("rm -f time.txt")
    os.system("make clean")


if __name__ == "__main__":
    graphfiles1 = ["data/8-webpages.txt", "data/100nodes_graph.txt"]
    graphfiles2 = ["data/web-NotreDame.txt",
                   "data/web-Stanford.txt", "data/web-BerkStan.txt"]

    benchmark_read_graph(
        graphfiles1, "read_graph_from_file1.c", 10000, "read1_test_set.png")

    benchmark_read_graph(
        graphfiles1, "read_graph_from_file2.c", 10000, "read2_test_set.png")

    benchmark_read_graph(
        graphfiles2, "read_graph_from_file2.c", 20, "read2_real_set.png")

    benchmark(graphfiles1, "count_mutual_links1.c",
              10000, 4, "count1_test_set.png")

    benchmark(graphfiles1, "count_mutual_links2.c",
              10000, 4, "count2_test_set.png")

    benchmark(graphfiles2, "count_mutual_links2.c",
              10000, 4, "count2_real_set.png")

    benchmark(graphfiles1, "top_n_webpages.c", 10000, 4, "top_n_test_set.png")
    benchmark(graphfiles2, "top_n_webpages.c", 500, 4, "top_n_real_set.png")
