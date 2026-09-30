#include "../include/sorting.h"


void insertion_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
) {

    metrics->comparisons = 0;
    metrics->movements = 0;


    for (int i = 1; i < n; i++) {

        int key = array[i];

        int j = i - 1;


        while (j >= 0) {

            metrics->comparisons++;


            if (array[j] > key) {

                array[j + 1] = array[j];

                metrics->movements++;

                j--;
            }
            else {

                break;
            }
        }


        array[j + 1] = key;
    }
}