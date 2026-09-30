#include <stdio.h>
#include <stdlib.h>
#include <process.h>

#include "../include/dataset.h"
#include "../include/sorting.h"
#include "../include/benchmark.h"
#include "../include/file_manager.h"
#include "../include/system_info.h"
#include "../include/analysis.h"


/* ============================================================
   GET DISTRIBUTION NAME
   ============================================================ */

const char* get_distribution_name(
    Distribution distribution
)
{
    switch (distribution)
    {
        case RANDOM:
            return "Random";

        case SORTED:
            return "Sorted";

        case REVERSE_SORTED:
            return "Reverse Sorted";

        case NEARLY_SORTED:
            return "Nearly Sorted";

        case DUPLICATES:
            return "Duplicates";

        default:
            return "Unknown";
    }
}


/* ============================================================
   CHECK ALGORITHM SIZE LIMIT
   ============================================================ */

int is_algorithm_allowed(
    SortingAlgorithm algorithm,
    int size
)
{
    /*
       Quadratic algorithms:
       Bubble, Selection, Insertion

       Maximum size:
       100000
    */

    if (
        algorithm == BUBBLE_SORT ||
        algorithm == SELECTION_SORT ||
        algorithm == INSERTION_SORT
    )
    {
        if (size > 100000)
        {
            return 0;
        }
    }


    /*
       Efficient algorithms:
       Merge, Quick, Heap

       Maximum size:
       500000
    */

    if (
        algorithm == MERGE_SORT ||
        algorithm == QUICK_SORT ||
        algorithm == HEAP_SORT
    )
    {
        if (size > 500000)
        {
            return 0;
        }
    }


    return 1;
}


/* ============================================================
   RUN ONE EXPERIMENT
   ============================================================ */

int run_experiment(
    const char *results_file,
    int size,
    DataType type,
    Distribution distribution,
    SortingAlgorithm algorithm
)
{
    /*
       Check algorithm size limit.
    */

    if (
        !is_algorithm_allowed(
            algorithm,
            size
        )
    )
    {
        printf(
            "%-20s | SKIPPED (size limit)\n",
            get_algorithm_name(algorithm)
        );

        return 0;
    }


    /*
       ========================================================
       RESUME SYSTEM
       ========================================================
    */

    BenchmarkResult existing_result;

    existing_result.algorithm =
        algorithm;

    existing_result.size =
        size;

    existing_result.type =
        type;

    existing_result.distribution =
        distribution;


    if (
        benchmark_result_exists(
            results_file,
            &existing_result
        )
    )
    {
        printf(
            "%-20s | SKIPPED (already exists)\n",
            get_algorithm_name(algorithm)
        );

        return 0;
    }


    /*
       ========================================================
       CREATE ORIGINAL DATASET
       ========================================================
    */

    Dataset *original =
        create_dataset(
            size,
            type,
            distribution
        );


    if (original == NULL)
    {
        printf(
            "Failed to create dataset!\n"
        );

        return 0;
    }


    /*
       ========================================================
       RUN BENCHMARK
       ========================================================
    */

    BenchmarkResult result =
        benchmark_sort(
            original,
            algorithm
        );


    /*
       ========================================================
       SAVE RESULT
       ========================================================
    */

    if (
        !save_benchmark_result(
            results_file,
            &result
        )
    )
    {
        printf(
            "Failed to save benchmark result!\n"
        );
    }


    /*
       ========================================================
       DISPLAY RESULT
       ========================================================
    */

    printf(
        "%-20s | "
        "Avg: %.6f s | "
        "Min: %.6f s | "
        "Max: %.6f s | "
        "Comparisons: %lld | "
        "Movements: %lld | "
        "%s\n",

        get_algorithm_name(algorithm),

        result.average_time,

        result.min_time,

        result.max_time,

        result.comparisons,

        result.movements,

        result.sorted
            ? "SUCCESS"
            : "FAILED"
    );


    /*
       ========================================================
       FREE DATASET
       ========================================================
    */

    destroy_dataset(original);


    return 1;
}


/* ============================================================
   RUN ONE DISTRIBUTION
   ============================================================ */

void run_distribution(
    const char *results_file,
    Distribution distribution
)
{
    int sizes[] = {

        1000,

        10000,

        50000,

        100000,

        250000,

        500000
    };


    SortingAlgorithm algorithms[] = {

        BUBBLE_SORT,

        SELECTION_SORT,

        INSERTION_SORT,

        MERGE_SORT,

        QUICK_SORT,

        HEAP_SORT
    };


    printf("\n");

    printf(
        "########################################\n"
    );

    printf(
        "Distribution: %s\n",
        get_distribution_name(distribution)
    );

    printf(
        "########################################\n"
    );


    for (
        int s = 0;
        s < 6;
        s++
    )
    {
        int n =
            sizes[s];


        printf("\n");

        printf(
            "----------------------------------------\n"
        );

        printf(
            "Dataset size: %d\n",
            n
        );

        printf(
            "----------------------------------------\n"
        );


        for (
            int a = 0;
            a < 6;
            a++
        )
        {
            run_experiment(
                results_file,
                n,
                DATA_INT,
                distribution,
                algorithms[a]
            );
        }
    }
}


/* ============================================================
   RUN ONE DATASET SIZE
   ============================================================ */

void run_one_size(
    const char *results_file,
    int size
)
{
    Distribution distributions[] = {

        RANDOM,

        SORTED,

        REVERSE_SORTED,

        NEARLY_SORTED,

        DUPLICATES
    };


    SortingAlgorithm algorithms[] = {

        BUBBLE_SORT,

        SELECTION_SORT,

        INSERTION_SORT,

        MERGE_SORT,

        QUICK_SORT,

        HEAP_SORT
    };


    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "Benchmarking size: %d\n",
        size
    );

    printf(
        "========================================\n"
    );


    for (
        int d = 0;
        d < 5;
        d++
    )
    {
        printf("\n");

        printf(
            "Distribution: %s\n",
            get_distribution_name(
                distributions[d]
            )
        );

        printf(
            "----------------------------------------\n"
        );


        for (
            int a = 0;
            a < 6;
            a++
        )
        {
            run_experiment(
                results_file,
                size,
                DATA_INT,
                distributions[d],
                algorithms[a]
            );
        }
    }
}


/* ============================================================
   GENERATE GRAPHS USING PIPE
   ============================================================ */

void generate_graphs(void)
{
    /*
       ========================================================
       GNUplot executable
       ========================================================
    */

    const char *gnuplot_command =
        "\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"";


    /*
       ========================================================
       OPEN GNUplot THROUGH PIPE
       ========================================================
    */

    FILE *pipe =
        _popen(
            gnuplot_command,
            "w"
        );


    if (pipe == NULL)
    {
        printf(
            "[PIPE] ERROR: Could not connect to GNUplot.\n"
        );

        printf(
            "[PIPE] Check that GNUplot is installed at:\n"
        );

        printf(
            "       C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\n"
        );

        return;
    }


    /*
       ========================================================
       CONNECTION SUCCESS
       ========================================================
    */

    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "       GRAPH GENERATION USING PIPE      \n"
    );

    printf(
        "========================================\n\n"
    );

    printf(
        "[PIPE] Connection with GNUplot established.\n"
    );


    /*
       ========================================================
       GNUplot scripts
       ========================================================
    */

    const char *scripts[] = {

        "plots/execution_time.plt",

        "plots/execution_time_all.plt",

        "plots/comparisons.plt",

        "plots/movements.plt",

        "plots/distribution_100k.plt",

        "plots/quadratic.plt",

        "plots/nlogn_algorithms.plt",

        "plots/scaling_analysis.plt"
    };


    /*
       ========================================================
       HUMAN-READABLE GRAPH NAMES
       ========================================================
    */

    const char *names[] = {

        "Execution Time",

        "Execution Time - All Data",

        "Comparisons",

        "Movements",

        "Distribution Analysis",

        "Quadratic Algorithms",

        "O(n log n) Algorithms",

        "Scaling Analysis"
    };


    int number_of_scripts =
        sizeof(scripts) /
        sizeof(scripts[0]);


    /*
       ========================================================
       LOAD EVERY GNUplot SCRIPT
       ========================================================
    */

    for (
        int i = 0;
        i < number_of_scripts;
        i++
    )
    {
        printf(
            "[%d/%d] Sending %s to GNUplot...\n",
            i + 1,
            number_of_scripts,
            names[i]
        );


        /*
           Reset GNUplot state before every script.
        */

        fprintf(
            pipe,
            "reset\n"
        );

        fflush(pipe);


        /*
           Load graph script.
        */

        fprintf(
            pipe,
            "load '%s'\n",
            scripts[i]
        );

        fflush(pipe);


        fprintf(
            pipe,
            "\n"
        );

        fflush(pipe);


        printf(
            "      [PIPE] Script sent successfully.\n"
        );
    }


    /*
       ========================================================
       CLOSE GNUplot
       ========================================================
    */

    fprintf(
        pipe,
        "exit\n"
    );

    fflush(pipe);


    int result =
        _pclose(pipe);


    /*
       ========================================================
       CHECK GNUplot PROCESS STATUS
       ========================================================
    */

    if (result == 0)
    {
        printf(
            "\n[PIPE] GNUplot process closed successfully.\n"
        );
    }

    else
    {
        printf(
            "\n[PIPE] GNUplot returned code: %d\n",
            result
        );

        printf(
            "[PIPE] Check GNUplot output above for details.\n"
        );
    }


    /*
       ========================================================
       FINAL MESSAGE
       ========================================================
    */

    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "       GRAPH GENERATION COMPLETED       \n"
    );

    printf(
        "========================================\n\n"
    );


    printf(
        "Communication method : PIPE\n"
    );

    printf(
        "Visualization engine : GNUplot\n"
    );

    printf(
        "Output directory     : results/graphs/\n"
    );
}


/* ============================================================
   MAIN
   ============================================================ */

int main(void)
{
    /*
       ========================================================
       FIXED RANDOM SEED
       ========================================================
    */

    srand(42);


    /*
       ========================================================
       RESULTS FILE
       ========================================================
    */

    const char *results_file =
        "results/benchmark_results.csv";


    /*
       ========================================================
       INITIALIZE RESULTS FILE
       ========================================================
    */

    if (
        !initialize_results_file(
            results_file
        )
    )
    {
        return 1;
    }


    /*
       ========================================================
       STARTUP MESSAGE
       ========================================================
    */

    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "          SORTLAB BENCHMARK             \n"
    );

    printf(
        "========================================\n\n"
    );


    printf(
        "Benchmark runs per experiment: %d\n",
        BENCHMARK_RUNS
    );

    printf(
        "Maximum dataset size: 500000\n"
    );

    printf(
        "Resume mode: ENABLED\n"
    );


    /*
       ========================================================
       MAIN MENU
       ========================================================
    */

    int choice;


    while (1)
    {
        printf("\n");

        printf(
            "========================================\n"
        );

        printf(
            "              MAIN MENU                 \n"
        );

        printf(
            "========================================\n"
        );


        printf(
            "1. Run full benchmark\n"
        );

        printf(
            "2. Benchmark one distribution\n"
        );

        printf(
            "3. Benchmark one dataset size\n"
        );

        printf(
            "4. Generate graphs\n"
        );

        printf(
            "5. System information\n"
        );

        printf(
            "6. Benchmark analysis\n"
        );

        printf(
            "7. Exit\n"
        );


        printf(
            "\nChoose an option: "
        );


        /*
           Validate menu input.
        */

        if (
            scanf(
                "%d",
                &choice
            ) != 1
        )
        {
            printf(
                "Invalid input.\n"
            );


            while (
                getchar() != '\n'
            );


            continue;
        }


        /*
           =====================================================
           OPTION 1
           FULL BENCHMARK
           =====================================================
        */

        if (choice == 1)
        {
            Distribution distributions[] = {

                RANDOM,

                SORTED,

                REVERSE_SORTED,

                NEARLY_SORTED,

                DUPLICATES
            };


            printf("\n");

            printf(
                "Starting full benchmark...\n"
            );

            printf(
                "Existing experiments will be skipped.\n"
            );


            for (
                int d = 0;
                d < 5;
                d++
            )
            {
                run_distribution(
                    results_file,
                    distributions[d]
                );
            }


            printf("\n");

            printf(
                "========================================\n"
            );

            printf(
                "       FULL BENCHMARK COMPLETED         \n"
            );

            printf(
                "========================================\n"
            );
        }


        /*
           =====================================================
           OPTION 2
           ONE DISTRIBUTION
           =====================================================
        */

        else if (choice == 2)
        {
            int distribution_choice;


            printf("\n");

            printf(
                "1. Random\n"
            );

            printf(
                "2. Sorted\n"
            );

            printf(
                "3. Reverse Sorted\n"
            );

            printf(
                "4. Nearly Sorted\n"
            );

            printf(
                "5. Duplicates\n"
            );


            printf(
                "\nChoose distribution: "
            );


            if (
                scanf(
                    "%d",
                    &distribution_choice
                ) != 1
            )
            {
                printf(
                    "Invalid input.\n"
                );


                while (
                    getchar() != '\n'
                );


                continue;
            }


            if (
                distribution_choice >= 1 &&
                distribution_choice <= 5
            )
            {
                run_distribution(
                    results_file,

                    (Distribution)
                    (
                        distribution_choice - 1
                    )
                );
            }

            else
            {
                printf(
                    "Invalid distribution.\n"
                );
            }
        }


        /*
           =====================================================
           OPTION 3
           ONE DATASET SIZE
           =====================================================
        */

        else if (choice == 3)
        {
            int size;


            printf("\n");

            printf(
                "Available sizes:\n"
            );

            printf(
                "1000\n"
            );

            printf(
                "10000\n"
            );

            printf(
                "50000\n"
            );

            printf(
                "100000\n"
            );

            printf(
                "250000\n"
            );

            printf(
                "500000\n"
            );


            printf(
                "\nEnter dataset size: "
            );


            if (
                scanf(
                    "%d",
                    &size
                ) != 1
            )
            {
                printf(
                    "Invalid input.\n"
                );


                while (
                    getchar() != '\n'
                );


                continue;
            }


            if (
                size == 1000 ||

                size == 10000 ||

                size == 50000 ||

                size == 100000 ||

                size == 250000 ||

                size == 500000
            )
            {
                run_one_size(
                    results_file,
                    size
                );
            }

            else
            {
                printf(
                    "Invalid dataset size.\n"
                );
            }
        }


        /*
           =====================================================
           OPTION 4
           GENERATE GRAPHS
           =====================================================
        */

        else if (choice == 4)
        {
            generate_graphs();
        }


        /*
           =====================================================
           OPTION 5
           SYSTEM INFORMATION
           =====================================================
        */

        else if (choice == 5)
        {
            display_system_info();
        }


        /*
           =====================================================
           OPTION 6
           BENCHMARK ANALYSIS
           =====================================================
        */

        else if (choice == 6)
        {
            display_benchmark_analysis();
        }


        /*
           =====================================================
           OPTION 7
           EXIT
           =====================================================
        */

        else if (choice == 7)
        {
            printf("\n");

            printf(
                "Exiting SORTLAB...\n"
            );

            break;
        }


        /*
           =====================================================
           INVALID OPTION
           =====================================================
        */

        else
        {
            printf(
                "Invalid option.\n"
            );
        }
    }


    return 0;
}