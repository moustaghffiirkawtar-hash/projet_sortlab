#ifndef SORTING_H
#define SORTING_H

#include "dataset.h"

/* ==============================
   SORTING ALGORITHM IDENTIFIERS
   ============================== */

typedef enum {

    BUBBLE_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
    MERGE_SORT,
    QUICK_SORT,
    HEAP_SORT

} SortingAlgorithm;


/* ==============================
   SORTING RESULT METRICS
   ============================== */

typedef struct {

    long long comparisons;

    long long movements;

} SortMetrics;


/* ==============================
   SORTING FUNCTIONS
   ============================== */

void bubble_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
);

void selection_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
);

void insertion_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
);

void merge_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
);

void quick_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
);

void heap_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
);


/* ==============================
   GENERIC INTEGER SORTER
   ============================== */

void sort_int(
    int *array,
    int n,
    SortingAlgorithm algorithm,
    SortMetrics *metrics
);


/* ==============================
   UTILITY FUNCTIONS
   ============================== */

const char* get_algorithm_name(
    SortingAlgorithm algorithm
);

#endif