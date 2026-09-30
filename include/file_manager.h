#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "benchmark.h"

int initialize_results_file(
    const char *filename
);

int save_benchmark_result(
    const char *filename,
    BenchmarkResult *result
);

int benchmark_result_exists(
    const char *filename,
    BenchmarkResult *result
);

#endif