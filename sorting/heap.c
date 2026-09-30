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
   HEAPIFY
   ============================== */

static void heapify(
    int *array,
    int n,
    int root,
    SortMetrics *metrics
) {

    int largest = root;

    int left = 2 * root + 1;

    int right = 2 * root + 2;


    /* ====================================
       CHECK LEFT CHILD
       ==================================== */

    if (left < n) {

        metrics->comparisons++;

        if (array[left] > array[largest]) {

            largest = left;
        }
    }


    /* ====================================
       CHECK RIGHT CHILD
       ==================================== */

    if (right < n) {

        metrics->comparisons++;

        if (array[right] > array[largest]) {

            largest = right;
        }
    }


    /* ====================================
       MOVE LARGEST TO ROOT
       ==================================== */

    if (largest != root) {

        swap_int(
            &array[root],
            &array[largest],
            metrics
        );


        heapify(
            array,
            n,
            largest,
            metrics
        );
    }
}


/* ==============================
   PUBLIC HEAP SORT
   ============================== */

void heap_sort_int(
    int *array,
    int n,
    SortMetrics *metrics
) {

    metrics->comparisons = 0;
    metrics->movements = 0;


    if (n <= 1) {
        return;
    }


    /* ====================================
       BUILD MAX HEAP
       ==================================== */

    for (int i = n / 2 - 1;
         i >= 0;
         i--) {

        heapify(
            array,
            n,
            i,
            metrics
        );
    }


    /* ====================================
       EXTRACT ELEMENTS
       ==================================== */

    for (int i = n - 1;
         i > 0;
         i--) {

        swap_int(
            &array[0],
            &array[i],
            metrics
        );


        heapify(
            array,
            i,
            0,
            metrics
        );
    }
}