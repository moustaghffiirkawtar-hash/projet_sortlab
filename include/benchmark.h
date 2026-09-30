#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "dataset.h"
#include "sorting.h"


/* ==============================
   BENCHMARK CONFIGURATION
   ============================== */

#define BENCHMARK_RUNS 5


/* ==============================
   BENCHMARK RESULT
   ============================== */

typedef struct {

    SortingAlgorithm algorithm;

    int size;

    DataType type;

    Distribution distribution;

    double average_time;

    double min_time;

    double max_time;

    long long comparisons;

    long long movements;

    int sorted;

} BenchmarkResult;


/* ==============================
   BENCHMARK FUNCTION
   ============================== */

BenchmarkResult benchmark_sort(
    Dataset *dataset,
    SortingAlgorithm algorithm
);


#endif