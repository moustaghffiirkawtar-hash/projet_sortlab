#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../include/benchmark.h"
#include "../include/validation.h"
#include "../include/timer.h"


/* ==============================
   GENERIC SORTING BENCHMARK
   ============================== */

BenchmarkResult benchmark_sort(
    Dataset *dataset,
    SortingAlgorithm algorithm
) {

    BenchmarkResult result;


    /* ==============================
       INITIALIZE RESULT
       ============================== */

    result.algorithm =
        algorithm;

    result.size =
        dataset->size;

    result.type =
        dataset->type;

    result.distribution =
        dataset->distribution;

    result.average_time =
        0.0;

    result.min_time =
        DBL_MAX;

    result.max_time =
        0.0;

    result.comparisons =
        0;

    result.movements =
        0;

    result.sorted =
        1;


    /* ==============================
       TIMING ACCUMULATOR
       ============================== */

    double total_time = 0.0;


    /* ==============================
       REPEATED RUNS
       ============================== */

    for (
        int run = 0;
        run < BENCHMARK_RUNS;
        run++
    ) {


        /* ==============================
           CREATE FRESH DATASET COPY
           ============================== */

        Dataset *copy =
            copy_dataset(dataset);


        if (copy == NULL) {

            printf(
                "Failed to copy dataset!\n"
            );

            result.sorted = 0;

            return result;
        }


        /* ==============================
           GET DATA
           ============================== */

        int *data =
            (int *)copy->data;


        /* ==============================
           INITIALIZE METRICS
           ============================== */

        SortMetrics metrics;

        metrics.comparisons =
            0;

        metrics.movements =
            0;


        /* ==============================
           START TIMER
           ============================== */

        double start_time =
            get_time_seconds();


        /* ==============================
           SORT
           ============================== */

        sort_int(
            data,
            copy->size,
            algorithm,
            &metrics
        );


        /* ==============================
           STOP TIMER
           ============================== */

        double end_time =
            get_time_seconds();


        /* ==============================
           RUN TIME
           ============================== */

        double run_time =
            end_time - start_time;


        /* ==============================
           UPDATE STATISTICS
           ============================== */

        total_time +=
            run_time;


        if (
            run_time <
            result.min_time
        ) {

            result.min_time =
                run_time;
        }


        if (
            run_time >
            result.max_time
        ) {

            result.max_time =
                run_time;
        }


        /* ==============================
           VALIDATE SORTING
           ============================== */

        int sorted =
            is_sorted_int(
                data,
                copy->size
            );


        if (!sorted) {

            result.sorted = 0;
        }


        /* ==============================
           STORE DETERMINISTIC METRICS
           ============================== */

        if (run == 0) {

            result.comparisons =
                metrics.comparisons;

            result.movements =
                metrics.movements;
        }


        /* ==============================
           FREE COPY
           ============================== */

        destroy_dataset(copy);
    }


    /* ==============================
       AVERAGE TIME
       ============================== */

    result.average_time =
        total_time
        / BENCHMARK_RUNS;


    return result;
}

