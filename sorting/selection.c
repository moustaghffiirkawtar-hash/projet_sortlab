#include "../include/sorting.h"


void selection_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
) {

    metrics->comparisons = 0;
    metrics->movements = 0;


    for (int i = 0; i < n - 1; i++) {

        int min_index = i;


        for (int j = i + 1; j < n; j++) {

            metrics->comparisons++;


            if (array[j] < array[min_index]) {

                min_index = j;
            }
        }


        if (min_index != i) {

            int temp = array[i];

            array[i] = array[min_index];

            array[min_index] = temp;

            metrics->movements++;
        }
    }
}