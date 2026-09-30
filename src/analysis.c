#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/analysis.h"


/* ============================================================
   CONSTANTS
   ============================================================ */

#define RESULTS_FILE "results/benchmark_results.csv"
#define REPORT_FILE  "results/analysis_report.txt"

#define MAX_ALGORITHMS 6
#define MAX_DISTRIBUTIONS 5
#define MAX_SIZES 6
#define MAX_RESULTS 1000

#define ANALYSIS_SIZE 100000


/* ============================================================
   DATA STRUCTURE
   ============================================================ */

typedef struct
{
    char algorithm[50];

    int size;

    char type[20];

    char distribution[50];

    double average_time;

    double min_time;

    double max_time;

    long long comparisons;

    long long movements;

    int sorted;

} AnalysisResult;


/* ============================================================
   ALGORITHM NAMES
   ============================================================ */

const char* analysis_algorithms[MAX_ALGORITHMS] =
{
    "Bubble Sort",
    "Selection Sort",
    "Insertion Sort",
    "Merge Sort",
    "Quick Sort",
    "Heap Sort"
};


/* ============================================================
   DISTRIBUTION NAMES
   ============================================================ */

const char* analysis_distributions[MAX_DISTRIBUTIONS] =
{
    "Random",
    "Sorted",
    "Reverse Sorted",
    "Nearly Sorted",
    "Duplicates"
};


/* ============================================================
   DATASET SIZES
   ============================================================ */

int analysis_sizes[MAX_SIZES] =
{
    1000,
    10000,
    50000,
    100000,
    250000,
    500000
};


/* ============================================================
   FIND RESULT
   ============================================================ */

int find_result(
    AnalysisResult results[],
    int count,
    const char *algorithm,
    int size,
    const char *distribution
)
{
    for (int i = 0; i < count; i++)
    {
        if (
            strcmp(
                results[i].algorithm,
                algorithm
            ) == 0
            &&
            results[i].size == size
            &&
            strcmp(
                results[i].distribution,
                distribution
            ) == 0
        )
        {
            return i;
        }
    }

    return -1;
}


/* ============================================================
   FIND FASTEST RESULT
   ============================================================ */

int find_fastest_result(
    AnalysisResult results[],
    int count
)
{
    if (count <= 0)
    {
        return -1;
    }

    int fastest = 0;

    for (int i = 1; i < count; i++)
    {
        if (
            results[i].average_time
            <
            results[fastest].average_time
        )
        {
            fastest = i;
        }
    }

    return fastest;
}


/* ============================================================
   FIND SLOWEST RESULT
   ============================================================ */

int find_slowest_result(
    AnalysisResult results[],
    int count
)
{
    if (count <= 0)
    {
        return -1;
    }

    int slowest = 0;

    for (int i = 1; i < count; i++)
    {
        if (
            results[i].average_time
            >
            results[slowest].average_time
        )
        {
            slowest = i;
        }
    }

    return slowest;
}


/* ============================================================
   GLOBAL SUMMARY
   ============================================================ */

void display_global_summary(
    AnalysisResult results[],
    int count
)
{
    int successful = 0;

    int failed = 0;

    double total_time = 0.0;


    for (int i = 0; i < count; i++)
    {
        if (results[i].sorted)
        {
            successful++;
        }
        else
        {
            failed++;
        }

        total_time +=
            results[i].average_time;
    }


    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "          GLOBAL BENCHMARK SUMMARY      \n"
    );

    printf(
        "========================================\n"
    );

    printf(
        "Total experiments : %d\n",
        count
    );

    printf(
        "Successful        : %d\n",
        successful
    );

    printf(
        "Failed            : %d\n",
        failed
    );


    if (count > 0)
    {
        printf(
            "Average time      : %.6f seconds\n",
            total_time / count
        );
    }


    printf(
        "========================================\n"
    );
}


/* ============================================================
   GLOBAL PERFORMANCE EXTREMES
   ============================================================ */

void display_extreme_results(
    AnalysisResult results[],
    int count
)
{
    int fastest =
        find_fastest_result(
            results,
            count
        );

    int slowest =
        find_slowest_result(
            results,
            count
        );


    if (
        fastest == -1 ||
        slowest == -1
    )
    {
        return;
    }


    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "        GLOBAL PERFORMANCE EXTREMES     \n"
    );

    printf(
        "========================================\n"
    );


    printf(
        "\nFastest experiment\n"
    );

    printf(
        "----------------------------------------\n"
    );

    printf(
        "Algorithm    : %s\n",
        results[fastest].algorithm
    );

    printf(
        "Size         : %d\n",
        results[fastest].size
    );

    printf(
        "Distribution : %s\n",
        results[fastest].distribution
    );

    printf(
        "Time         : %.6f seconds\n",
        results[fastest].average_time
    );


    printf(
        "\nSlowest experiment\n"
    );

    printf(
        "----------------------------------------\n"
    );

    printf(
        "Algorithm    : %s\n",
        results[slowest].algorithm
    );

    printf(
        "Size         : %d\n",
        results[slowest].size
    );

    printf(
        "Distribution : %s\n",
        results[slowest].distribution
    );

    printf(
        "Time         : %.6f seconds\n",
        results[slowest].average_time
    );
}


/* ============================================================
   DISTRIBUTION ANALYSIS
   ============================================================ */

void display_distribution_analysis(
    AnalysisResult results[],
    int count
)
{
    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        " DISTRIBUTION ANALYSIS - SIZE %d       \n",
        ANALYSIS_SIZE
    );

    printf(
        "========================================\n"
    );


    printf("\n");

    printf(
        "%-18s %-18s %s\n",
        "Distribution",
        "Fastest Algorithm",
        "Time"
    );

    printf(
        "--------------------------------------------------------\n"
    );


    for (
        int d = 0;
        d < MAX_DISTRIBUTIONS;
        d++
    )
    {
        int best_index = -1;


        for (
            int a = 0;
            a < MAX_ALGORITHMS;
            a++
        )
        {
            int index =
                find_result(
                    results,
                    count,
                    analysis_algorithms[a],
                    ANALYSIS_SIZE,
                    analysis_distributions[d]
                );


            if (index != -1)
            {
                if (
                    best_index == -1 ||
                    results[index].average_time
                    <
                    results[best_index].average_time
                )
                {
                    best_index = index;
                }
            }
        }


        if (best_index != -1)
        {
            printf(
                "%-18s %-18s %.6f s\n",
                analysis_distributions[d],
                results[best_index].algorithm,
                results[best_index].average_time
            );
        }

        else
        {
            printf(
                "%-18s %-18s %s\n",
                analysis_distributions[d],
                "N/A",
                "N/A"
            );
        }
    }


    printf(
        "\nNote: all distributions are compared using the same dataset size (%d).\n",
        ANALYSIS_SIZE
    );
}


/* ============================================================
   ALGORITHM STATISTICS
   ============================================================ */

void display_algorithm_statistics(
    AnalysisResult results[],
    int count
)
{
    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "       ALGORITHM STATISTICS             \n"
    );

    printf(
        "========================================\n"
    );


    for (
        int a = 0;
        a < MAX_ALGORITHMS;
        a++
    )
    {
        int algorithm_count = 0;

        double total_time = 0.0;

        long long total_comparisons = 0;

        long long total_movements = 0;


        for (int i = 0; i < count; i++)
        {
            if (
                strcmp(
                    results[i].algorithm,
                    analysis_algorithms[a]
                ) == 0
            )
            {
                algorithm_count++;

                total_time +=
                    results[i].average_time;

                total_comparisons +=
                    results[i].comparisons;

                total_movements +=
                    results[i].movements;
            }
        }


        if (algorithm_count > 0)
        {
            printf("\n");

            printf(
                "%s\n",
                analysis_algorithms[a]
            );

            printf(
                "----------------------------------------\n"
            );

            printf(
                "Experiments        : %d\n",
                algorithm_count
            );

            printf(
                "Average time       : %.6f s\n",
                total_time /
                algorithm_count
            );

            printf(
                "Average comparisons: %.0f\n",
                (double)total_comparisons /
                algorithm_count
            );

            printf(
                "Average movements  : %.0f\n",
                (double)total_movements /
                algorithm_count
            );
        }
    }
}


/* ============================================================
   DATASET SIZE ANALYSIS
   ============================================================ */

void display_size_analysis(
    AnalysisResult results[],
    int count
)
{
    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "       DATASET SIZE ANALYSIS - RANDOM   \n"
    );

    printf(
        "========================================\n"
    );


    printf("\n");

    printf(
        "%-12s",
        "Size"
    );


    for (
        int a = 0;
        a < MAX_ALGORITHMS;
        a++
    )
    {
        printf(
            "%18s",
            analysis_algorithms[a]
        );
    }


    printf("\n");


    printf(
        "----------------------------------------------------------------------------------------------------------------\n"
    );


    for (
        int s = 0;
        s < MAX_SIZES;
        s++
    )
    {
        int size =
            analysis_sizes[s];


        printf(
            "%-12d",
            size
        );


        for (
            int a = 0;
            a < MAX_ALGORITHMS;
            a++
        )
        {
            int index =
                find_result(
                    results,
                    count,
                    analysis_algorithms[a],
                    size,
                    "Random"
                );


            if (index != -1)
            {
                printf(
                    "%18.6f",
                    results[index].average_time
                );
            }

            else
            {
                printf(
                    "%18s",
                    "N/A"
                );
            }
        }


        printf("\n");
    }


    printf(
        "\nExecution time is measured in seconds.\n"
    );

    printf(
        "Distribution used: Random.\n"
    );

    printf(
        "Quadratic algorithms are intentionally unavailable above 100000 elements.\n"
    );
}


/* ============================================================
   SCALING ANALYSIS
   ============================================================ */

void display_scaling_analysis(
    AnalysisResult results[],
    int count
)
{
    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "          SCALING ANALYSIS              \n"
    );

    printf(
        "========================================\n"
    );


    printf(
        "\nGrowth of execution time with dataset size\n"
    );

    printf(
        "(Using the Random distribution)\n"
    );


    printf("\n");

    printf(
        "%-18s",
        "Algorithm"
    );


    for (
        int s = 0;
        s < MAX_SIZES;
        s++
    )
    {
        printf(
            "%12d",
            analysis_sizes[s]
        );
    }


    printf("\n");


    printf(
        "--------------------------------------------------------------------------------\n"
    );


    for (
        int a = 0;
        a < MAX_ALGORITHMS;
        a++
    )
    {
        printf(
            "%-18s",
            analysis_algorithms[a]
        );


        for (
            int s = 0;
            s < MAX_SIZES;
            s++
        )
        {
            int index =
                find_result(
                    results,
                    count,
                    analysis_algorithms[a],
                    analysis_sizes[s],
                    "Random"
                );


            if (index != -1)
            {
                printf(
                    "%12.4f",
                    results[index].average_time
                );
            }

            else
            {
                printf(
                    "%12s",
                    "N/A"
                );
            }
        }


        printf("\n");
    }


    printf(
        "\nQuadratic algorithms are not available for sizes above 100000.\n"
    );
}


/* ============================================================
   COMPLEXITY GROUPS
   ============================================================ */

void display_complexity_groups(void)
{
    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "          COMPLEXITY GROUPS              \n"
    );

    printf(
        "========================================\n"
    );


    printf("\n");

    printf(
        "Quadratic Algorithms - O(n^2)\n"
    );

    printf(
        "----------------------------------------\n"
    );

    printf(
        "Bubble Sort\n"
    );

    printf(
        "Selection Sort\n"
    );

    printf(
        "Insertion Sort\n"
    );


    printf("\n");

    printf(
        "Efficient Algorithms - O(n log n)\n"
    );

    printf(
        "----------------------------------------\n"
    );

    printf(
        "Merge Sort\n"
    );

    printf(
        "Quick Sort\n"
    );

    printf(
        "Heap Sort\n"
    );
}


/* ============================================================
   LOAD CSV RESULTS
   ============================================================ */

int load_analysis_results(
    AnalysisResult results[]
)
{
    FILE *file =
        fopen(
            RESULTS_FILE,
            "r"
        );


    if (file == NULL)
    {
        printf(
            "\n[ERROR] Could not open:\n"
        );

        printf(
            "       %s\n",
            RESULTS_FILE
        );

        return 0;
    }


    char line[512];

    int count = 0;


    /*
       Skip CSV header.
    */

    if (
        fgets(
            line,
            sizeof(line),
            file
        ) == NULL
    )
    {
        fclose(file);

        return 0;
    }


    while (
        fgets(
            line,
            sizeof(line),
            file
        ) != NULL
    )
    {
        if (count >= MAX_RESULTS)
        {
            break;
        }


        AnalysisResult *result =
            &results[count];


        /*
           CSV format:

           Algorithm,
           Size,
           Type,
           Distribution,
           AverageTime,
           MinTime,
           MaxTime,
           Comparisons,
           Movements,
           Sorted
        */

        int fields =
            sscanf(
                line,

                " %49[^,],"
                "%d,"
                " %19[^,],"
                " %49[^,],"
                "%lf,"
                "%lf,"
                "%lf,"
                "%lld,"
                "%lld,"
                "%d",

                result->algorithm,

                &result->size,

                result->type,

                result->distribution,

                &result->average_time,

                &result->min_time,

                &result->max_time,

                &result->comparisons,

                &result->movements,

                &result->sorted
            );


        if (fields == 10)
        {
            count++;
        }
    }


    fclose(file);


    return count;
}


/* ============================================================
   WRITE REPORT HEADER
   ============================================================ */

void write_report_header(
    FILE *report
)
{
    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "        SORTLAB EXPERIMENTAL REPORT     \n"
    );

    fprintf(
        report,
        "========================================\n\n"
    );


    fprintf(
        report,
        "Benchmark configuration\n"
    );

    fprintf(
        report,
        "----------------------------------------\n"
    );

    fprintf(
        report,
        "Data type              : Integer\n"
    );

    fprintf(
        report,
        "Dataset sizes          : 1000, 10000, 50000, 100000, 250000, 500000\n"
    );

    fprintf(
        report,
        "Distributions          : Random, Sorted, Reverse Sorted, Nearly Sorted, Duplicates\n"
    );

    fprintf(
        report,
        "Benchmark runs         : 5\n"
    );

    fprintf(
        report,
        "Quadratic limit        : 100000 elements\n"
    );

    fprintf(
        report,
        "Efficient algorithm limit: 500000 elements\n"
    );

    fprintf(
        report,
        "Metrics                : Execution time, comparisons, movements, validation\n\n"
    );
}


/* ============================================================
   WRITE GLOBAL SUMMARY
   ============================================================ */

void write_global_summary(
    FILE *report,
    AnalysisResult results[],
    int count
)
{
    int successful = 0;

    int failed = 0;

    double total_time = 0.0;


    for (int i = 0; i < count; i++)
    {
        if (results[i].sorted)
        {
            successful++;
        }
        else
        {
            failed++;
        }

        total_time +=
            results[i].average_time;
    }


    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "        GLOBAL BENCHMARK SUMMARY        \n"
    );

    fprintf(
        report,
        "========================================\n"
    );


    fprintf(
        report,
        "Total experiments : %d\n",
        count
    );

    fprintf(
        report,
        "Successful        : %d\n",
        successful
    );

    fprintf(
        report,
        "Failed            : %d\n",
        failed
    );


    if (count > 0)
    {
        fprintf(
            report,
            "Average time      : %.6f seconds\n",
            total_time / count
        );
    }


    fprintf(
        report,
        "\n"
    );
}


/* ============================================================
   WRITE EXTREMES
   ============================================================ */

void write_extreme_results(
    FILE *report,
    AnalysisResult results[],
    int count
)
{
    int fastest =
        find_fastest_result(
            results,
            count
        );

    int slowest =
        find_slowest_result(
            results,
            count
        );


    if (
        fastest == -1 ||
        slowest == -1
    )
    {
        return;
    }


    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "        GLOBAL PERFORMANCE EXTREMES     \n"
    );

    fprintf(
        report,
        "========================================\n\n"
    );


    fprintf(
        report,
        "Fastest experiment\n"
    );

    fprintf(
        report,
        "----------------------------------------\n"
    );

    fprintf(
        report,
        "Algorithm    : %s\n",
        results[fastest].algorithm
    );

    fprintf(
        report,
        "Size         : %d\n",
        results[fastest].size
    );

    fprintf(
        report,
        "Distribution : %s\n",
        results[fastest].distribution
    );

    fprintf(
        report,
        "Time         : %.6f seconds\n\n",
        results[fastest].average_time
    );


    fprintf(
        report,
        "Slowest experiment\n"
    );

    fprintf(
        report,
        "----------------------------------------\n"
    );

    fprintf(
        report,
        "Algorithm    : %s\n",
        results[slowest].algorithm
    );

    fprintf(
        report,
        "Size         : %d\n",
        results[slowest].size
    );

    fprintf(
        report,
        "Distribution : %s\n",
        results[slowest].distribution
    );

    fprintf(
        report,
        "Time         : %.6f seconds\n\n",
        results[slowest].average_time
    );
}


/* ============================================================
   WRITE DISTRIBUTION ANALYSIS
   ============================================================ */

void write_distribution_analysis(
    FILE *report,
    AnalysisResult results[],
    int count
)
{
    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "       DISTRIBUTION ANALYSIS            \n"
    );

    fprintf(
        report,
        "========================================\n\n"
    );


    fprintf(
        report,
        "Dataset size: %d\n\n",
        ANALYSIS_SIZE
    );


    fprintf(
        report,
        "%-18s %-18s %s\n",
        "Distribution",
        "Fastest Algorithm",
        "Time"
    );

    fprintf(
        report,
        "--------------------------------------------------------\n"
    );


    for (
        int d = 0;
        d < MAX_DISTRIBUTIONS;
        d++
    )
    {
        int best_index = -1;


        for (
            int a = 0;
            a < MAX_ALGORITHMS;
            a++
        )
        {
            int index =
                find_result(
                    results,
                    count,
                    analysis_algorithms[a],
                    ANALYSIS_SIZE,
                    analysis_distributions[d]
                );


            if (index != -1)
            {
                if (
                    best_index == -1 ||
                    results[index].average_time
                    <
                    results[best_index].average_time
                )
                {
                    best_index = index;
                }
            }
        }


        if (best_index != -1)
        {
            fprintf(
                report,
                "%-18s %-18s %.6f s\n",
                analysis_distributions[d],
                results[best_index].algorithm,
                results[best_index].average_time
            );
        }

        else
        {
            fprintf(
                report,
                "%-18s %-18s %s\n",
                analysis_distributions[d],
                "N/A",
                "N/A"
            );
        }
    }


    fprintf(
        report,
        "\n"
    );
}


/* ============================================================
   WRITE ALGORITHM STATISTICS
   ============================================================ */

void write_algorithm_statistics(
    FILE *report,
    AnalysisResult results[],
    int count
)
{
    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "          ALGORITHM STATISTICS          \n"
    );

    fprintf(
        report,
        "========================================\n"
    );


    for (
        int a = 0;
        a < MAX_ALGORITHMS;
        a++
    )
    {
        int algorithm_count = 0;

        double total_time = 0.0;

        long long total_comparisons = 0;

        long long total_movements = 0;


        for (int i = 0; i < count; i++)
        {
            if (
                strcmp(
                    results[i].algorithm,
                    analysis_algorithms[a]
                ) == 0
            )
            {
                algorithm_count++;

                total_time +=
                    results[i].average_time;

                total_comparisons +=
                    results[i].comparisons;

                total_movements +=
                    results[i].movements;
            }
        }


        if (algorithm_count > 0)
        {
            fprintf(
                report,
                "\n%s\n",
                analysis_algorithms[a]
            );

            fprintf(
                report,
                "----------------------------------------\n"
            );

            fprintf(
                report,
                "Experiments         : %d\n",
                algorithm_count
            );

            fprintf(
                report,
                "Average time        : %.6f s\n",
                total_time /
                algorithm_count
            );

            fprintf(
                report,
                "Average comparisons : %.0f\n",
                (double)total_comparisons /
                algorithm_count
            );

            fprintf(
                report,
                "Average movements   : %.0f\n",
                (double)total_movements /
                algorithm_count
            );
        }
    }


    fprintf(
        report,
        "\n"
    );
}


/* ============================================================
   WRITE DATASET SIZE ANALYSIS
   ============================================================ */

void write_size_analysis(
    FILE *report,
    AnalysisResult results[],
    int count
)
{
    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "       DATASET SIZE ANALYSIS - RANDOM   \n"
    );

    fprintf(
        report,
        "========================================\n\n"
    );


    fprintf(
        report,
        "%-12s",
        "Size"
    );


    for (
        int a = 0;
        a < MAX_ALGORITHMS;
        a++
    )
    {
        fprintf(
            report,
            "%18s",
            analysis_algorithms[a]
        );
    }


    fprintf(
        report,
        "\n"
    );


    fprintf(
        report,
        "----------------------------------------------------------------------------------------------------------------\n"
    );


    for (
        int s = 0;
        s < MAX_SIZES;
        s++
    )
    {
        int size =
            analysis_sizes[s];


        fprintf(
            report,
            "%-12d",
            size
        );


        for (
            int a = 0;
            a < MAX_ALGORITHMS;
            a++
        )
        {
            int index =
                find_result(
                    results,
                    count,
                    analysis_algorithms[a],
                    size,
                    "Random"
                );


            if (index != -1)
            {
                fprintf(
                    report,
                    "%18.6f",
                    results[index].average_time
                );
            }

            else
            {
                fprintf(
                    report,
                    "%18s",
                    "N/A"
                );
            }
        }


        fprintf(
            report,
            "\n"
        );
    }


    fprintf(
        report,
        "\nExecution time is measured in seconds.\n"
    );

    fprintf(
        report,
        "Distribution used: Random.\n\n"
    );
}


/* ============================================================
   WRITE SCALING ANALYSIS
   ============================================================ */

void write_scaling_analysis(
    FILE *report,
    AnalysisResult results[],
    int count
)
{
    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "          SCALING ANALYSIS              \n"
    );

    fprintf(
        report,
        "========================================\n\n"
    );


    fprintf(
        report,
        "Growth of execution time with dataset size\n"
    );

    fprintf(
        report,
        "Distribution: Random\n\n"
    );


    fprintf(
        report,
        "%-18s",
        "Algorithm"
    );


    for (
        int s = 0;
        s < MAX_SIZES;
        s++
    )
    {
        fprintf(
            report,
            "%12d",
            analysis_sizes[s]
        );
    }


    fprintf(
        report,
        "\n"
    );


    fprintf(
        report,
        "--------------------------------------------------------------------------------\n"
    );


    for (
        int a = 0;
        a < MAX_ALGORITHMS;
        a++
    )
    {
        fprintf(
            report,
            "%-18s",
            analysis_algorithms[a]
        );


        for (
            int s = 0;
            s < MAX_SIZES;
            s++
        )
        {
            int index =
                find_result(
                    results,
                    count,
                    analysis_algorithms[a],
                    analysis_sizes[s],
                    "Random"
                );


            if (index != -1)
            {
                fprintf(
                    report,
                    "%12.4f",
                    results[index].average_time
                );
            }

            else
            {
                fprintf(
                    report,
                    "%12s",
                    "N/A"
                );
            }
        }


        fprintf(
            report,
            "\n"
        );
    }


    fprintf(
        report,
        "\n"
    );
}


/* ============================================================
   WRITE COMPLEXITY GROUPS
   ============================================================ */

void write_complexity_groups(
    FILE *report
)
{
    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "          COMPLEXITY GROUPS              \n"
    );

    fprintf(
        report,
        "========================================\n\n"
    );


    fprintf(
        report,
        "Quadratic Algorithms - O(n^2)\n"
    );

    fprintf(
        report,
        "----------------------------------------\n"
    );

    fprintf(
        report,
        "Bubble Sort\n"
    );

    fprintf(
        report,
        "Selection Sort\n"
    );

    fprintf(
        report,
        "Insertion Sort\n\n"
    );


    fprintf(
        report,
        "Efficient Algorithms - O(n log n)\n"
    );

    fprintf(
        report,
        "----------------------------------------\n"
    );

    fprintf(
        report,
        "Merge Sort\n"
    );

    fprintf(
        report,
        "Quick Sort\n"
    );

    fprintf(
        report,
        "Heap Sort\n\n"
    );
}


/* ============================================================
   GENERATE ANALYSIS REPORT
   ============================================================ */

void generate_analysis_report(
    AnalysisResult results[],
    int count
)
{
    FILE *report =
        fopen(
            REPORT_FILE,
            "w"
        );


    if (report == NULL)
    {
        printf(
            "\n[REPORT] Could not create:\n"
        );

        printf(
            "         %s\n",
            REPORT_FILE
        );

        return;
    }


    write_report_header(
        report
    );


    write_global_summary(
        report,
        results,
        count
    );


    write_extreme_results(
        report,
        results,
        count
    );


    write_distribution_analysis(
        report,
        results,
        count
    );


    write_algorithm_statistics(
        report,
        results,
        count
    );


    write_size_analysis(
        report,
        results,
        count
    );


    write_scaling_analysis(
        report,
        results,
        count
    );


    write_complexity_groups(
        report
    );


    fprintf(
        report,
        "========================================\n"
    );

    fprintf(
        report,
        "          REPORT COMPLETED              \n"
    );

    fprintf(
        report,
        "========================================\n"
    );


    fclose(report);


    printf("\n");

    printf(
        "[REPORT] Analysis report generated successfully.\n"
    );

    printf(
        "[REPORT] File: %s\n",
        REPORT_FILE
    );
}


/* ============================================================
   MAIN ANALYSIS FUNCTION
   ============================================================ */

void display_benchmark_analysis(void)
{
    AnalysisResult results[MAX_RESULTS];


    int count =
        load_analysis_results(
            results
        );


    if (count <= 0)
    {
        printf(
            "\n[ANALYSIS] No benchmark results found.\n"
        );

        return;
    }


    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "          SORTLAB ANALYSIS              \n"
    );

    printf(
        "========================================\n"
    );


    printf(
        "\nLoaded %d benchmark results.\n",
        count
    );


    display_global_summary(
        results,
        count
    );


    display_extreme_results(
        results,
        count
    );


    display_distribution_analysis(
        results,
        count
    );


    display_algorithm_statistics(
        results,
        count
    );


    display_size_analysis(
        results,
        count
    );


    display_scaling_analysis(
        results,
        count
    );


    display_complexity_groups();


    /*
       Generate the permanent text report.
    */

    generate_analysis_report(
        results,
        count
    );


    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "        ANALYSIS COMPLETED              \n"
    );

    printf(
        "========================================\n"
    );
}