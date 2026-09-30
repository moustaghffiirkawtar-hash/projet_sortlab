#include "../include/sorting.h"

/* ==============================
   ALGORITHM NAMES
   ============================== */

const char* get_algorithm_name(
    SortingAlgorithm algorithm
) {

    switch (algorithm) {

        case BUBBLE_SORT:
            return "Bubble Sort";

        case SELECTION_SORT:
            return "Selection Sort";

        case INSERTION_SORT:
            return "Insertion Sort";

        case MERGE_SORT:
            return "Merge Sort";

        case QUICK_SORT:
            return "Quick Sort";

        case HEAP_SORT:
            return "Heap Sort";

        default:
            return "Unknown";
    }
}


/* ==============================
   GENERIC INTEGER SORTER
   ============================== */

void sort_int(
    int *array,
    int n,
    SortingAlgorithm algorithm,
    SortMetrics *metrics
) {

    switch (algorithm) {

        case BUBBLE_SORT:

            bubble_sort_int(
                array,
                n,
                metrics
            );

            break;


        case SELECTION_SORT:

            selection_sort_int(
                array,
                n,
                metrics
            );

            break;


        case INSERTION_SORT:

            insertion_sort_int(
                array,
                n,
                metrics
            );

            break;


        case MERGE_SORT:

            merge_sort_int(
                array,
                n,
                metrics
            );

            break;


        case QUICK_SORT:

            quick_sort_int(
                array,
                n,
                metrics
            );

            break;


        case HEAP_SORT:

            heap_sort_int(
                array,
                n,
                metrics
            );

            break;


        default:

            metrics->comparisons = 0;
            metrics->movements = 0;

            break;
    }
}