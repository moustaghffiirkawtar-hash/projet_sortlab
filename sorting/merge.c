#include "../include/sorting.h"
#include <stdlib.h>

/* ==============================
   MERGE TWO SORTED HALVES
   ============================== */

static void merge(
    int *array,
    int *temp,
    int left,
    int middle,
    int right,
    SortMetrics *metrics
) {

    int i = left;
    int j = middle + 1;
    int k = left;


    /* ====================================
       COMPARE ELEMENTS FROM BOTH HALVES
       ==================================== */

    while (i <= middle && j <= right) {

        metrics->comparisons++;

        if (array[i] <= array[j]) {

            temp[k] = array[i];
            i++;

        } else {

            temp[k] = array[j];
            j++;
        }

        metrics->movements++;

        k++;
    }


    /* ====================================
       COPY REMAINING LEFT HALF
       ==================================== */

    while (i <= middle) {

        temp[k] = array[i];

        i++;
        k++;

        metrics->movements++;
    }


    /* ====================================
       COPY REMAINING RIGHT HALF
       ==================================== */

    while (j <= right) {

        temp[k] = array[j];

        j++;
        k++;

        metrics->movements++;
    }


    /* ====================================
       COPY BACK INTO ORIGINAL ARRAY
       ==================================== */

    for (i = left; i <= right; i++) {

        array[i] = temp[i];

        metrics->movements++;
    }
}


/* ==============================
   MERGE SORT RECURSIVE FUNCTION
   ============================== */

static void merge_sort_recursive(
    int *array,
    int *temp,
    int left,
    int right,
    SortMetrics *metrics
) {

    if (left >= right) {
        return;
    }


    int middle =
        left + (right - left) / 2;


    /* Sort left half */

    merge_sort_recursive(
        array,
        temp,
        left,
        middle,
        metrics
    );


    /* Sort right half */

    merge_sort_recursive(
        array,
        temp,
        middle + 1,
        right,
        metrics
    );


    /* Merge both halves */

    merge(
        array,
        temp,
        left,
        middle,
        right,
        metrics
    );
}


/* ==============================
   PUBLIC MERGE SORT
   ============================== */

void merge_sort_int(
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
       TEMPORARY MEMORY
       ==================================== */

    int *temp =
        malloc(n * sizeof(int));


    if (temp == NULL) {
        return;
    }


    /* ====================================
       START RECURSIVE MERGE SORT
       ==================================== */

    merge_sort_recursive(
        array,
        temp,
        0,
        n - 1,
        metrics
    );


    /* ====================================
       FREE TEMPORARY MEMORY
       ==================================== */

    free(temp);
}