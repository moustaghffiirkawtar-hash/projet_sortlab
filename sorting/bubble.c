#include "../include/sorting.h"


void bubble_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
) {

    /* Initialize metrics */

    metrics->comparisons = 0;
    metrics->movements = 0;


    for (int i = 0; i < n - 1; i++) {

        int swapped = 0;


        for (int j = 0; j < n - i - 1; j++) {

            /* Count comparison */

            metrics->comparisons++;


            if (array[j] > array[j + 1]) {

                /* Swap */

                int temp = array[j];

                array[j] = array[j + 1];

                array[j + 1] = temp;


                /* Count movement */

                metrics->movements++;

                swapped = 1;
            }
        }


        /* Early termination */

        if (!swapped) {
            break;
        }
    }
}