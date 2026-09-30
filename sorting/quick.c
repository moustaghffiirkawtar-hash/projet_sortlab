#include "../include/sorting.h"

/* ==============================
   SWAP
   ============================== */

static void swap_int(
    int *a,
    int *b,
    SortMetrics *metrics
) {

    int temp = *a;

    *a = *b;
    *b = temp;

    metrics->movements++;
}


/* ==============================
   PARTITION
   ============================== */

static int partition(
    int *array,
    int low,
    int high,
    SortMetrics *metrics
) {

    /*
       Median-of-three pivot selection.
       This helps avoid poor pivots on
       already sorted or reverse-sorted data.
    */

    int middle =
        low + (high - low) / 2;


    int a = array[low];
    int b = array[middle];
    int c = array[high];

    int pivot;


    if ((a <= b && b <= c) ||
        (c <= b && b <= a)) {

        pivot = b;

    }
    else if ((b <= a && a <= c) ||
             (c <= a && a <= b)) {

        pivot = a;

    }
    else {

        pivot = c;
    }


    int i = low - 1;
    int j = high + 1;


    /*
       Hoare partition scheme.
    */

    while (1) {

        do {

            i++;

            metrics->comparisons++;

        } while (array[i] < pivot);


        do {

            j--;

            metrics->comparisons++;

        } while (array[j] > pivot);


        if (i >= j) {

            return j;
        }


        swap_int(
            &array[i],
            &array[j],
            metrics
        );
    }
}


/* ==============================
   RECURSIVE QUICK SORT
   ============================== */

static void quick_sort_recursive(
    int *array,
    int low,
    int high,
    SortMetrics *metrics
) {

    if (low >= high) {
        return;
    }


    int split =
        partition(
            array,
            low,
            high,
            metrics
        );


    quick_sort_recursive(
        array,
        low,
        split,
        metrics
    );


    quick_sort_recursive(
        array,
        split + 1,
        high,
        metrics
    );
}


/* ==============================
   PUBLIC QUICK SORT
   ============================== */

void quick_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
) {

    metrics->comparisons = 0;
    metrics->movements = 0;


    if (n <= 1) {
        return;
    }


    quick_sort_recursive(
        array,
        0,
        n - 1,
        metrics
    );
}