#include <stdio.h>
#include <string.h>

#include "../include/file_manager.h"


/* ==============================
   GET DISTRIBUTION NAME
   ============================== */

static const char* get_distribution_name(
    Distribution distribution
) {

    switch (distribution) {

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


/* ==============================
   GET DATA TYPE NAME
   ============================== */

static const char* get_type_name(
    DataType type
) {

    if (type == DATA_INT) {
        return "INT";
    }

    return "FLOAT";
}


/* ==============================
   INITIALIZE RESULTS FILE
   ============================== */

int initialize_results_file(
    const char *filename
) {

    FILE *file =
        fopen(
            filename,
            "r"
        );


    /*
       If the file already exists,
       keep all existing results.
    */

    if (file != NULL) {

        fclose(file);

        return 1;
    }


    /*
       File does not exist.
       Create a new CSV file.
    */

    file =
        fopen(
            filename,
            "w"
        );


    if (file == NULL) {

        printf(
            "Error: Cannot create results file!\n"
        );

        return 0;
    }


    fprintf(
        file,

        "Algorithm,"
        "Size,"
        "Type,"
        "Distribution,"
        "AverageTime,"
        "MinTime,"
        "MaxTime,"
        "Comparisons,"
        "Movements,"
        "Sorted\n"
    );


    fclose(file);

    return 1;
}


/* ==============================
   CHECK IF RESULT ALREADY EXISTS
   ============================== */

int benchmark_result_exists(
    const char *filename,
    BenchmarkResult *result
) {

    FILE *file =
        fopen(
            filename,
            "r"
        );


    /*
       If the file cannot be opened,
       assume the result does not exist.
    */

    if (file == NULL) {
        return 0;
    }


    char line[1024];


    /*
       Skip CSV header.
    */

    if (fgets(line, sizeof(line), file) == NULL) {

        fclose(file);

        return 0;
    }


    const char *algorithm =
        get_algorithm_name(
            result->algorithm
        );

    const char *type =
        get_type_name(
            result->type
        );

    const char *distribution =
        get_distribution_name(
            result->distribution
        );


    /*
       Read every existing row.
    */

    while (
        fgets(
            line,
            sizeof(line),
            file
        ) != NULL
    ) {

        char existing_algorithm[100];
        int existing_size;
        char existing_type[20];
        char existing_distribution[100];


        /*
           Read only the fields needed
           to identify an experiment.

           We do NOT compare execution
           times or metrics.
        */

        int fields =
            sscanf(
                line,

                "%99[^,],%d,%19[^,],%99[^,]",

                existing_algorithm,

                &existing_size,

                existing_type,

                existing_distribution
            );


        if (fields != 4) {
            continue;
        }


        /*
           Compare:

           Algorithm
           Size
           Type
           Distribution
        */

        if (
            strcmp(
                existing_algorithm,
                algorithm
            ) == 0

            &&

            existing_size ==
            result->size

            &&

            strcmp(
                existing_type,
                type
            ) == 0

            &&

            strcmp(
                existing_distribution,
                distribution
            ) == 0
        ) {

            fclose(file);

            return 1;
        }
    }


    fclose(file);

    return 0;
}


/* ==============================
   SAVE BENCHMARK RESULT
   ============================== */

int save_benchmark_result(
    const char *filename,
    BenchmarkResult *result
) {

    FILE *file =
        fopen(
            filename,
            "a"
        );


    if (file == NULL) {

        printf(
            "Error: Cannot open results file!\n"
        );

        return 0;
    }


    const char *algorithm =
        get_algorithm_name(
            result->algorithm
        );


    const char *type =
        get_type_name(
            result->type
        );


    const char *distribution =
        get_distribution_name(
            result->distribution
        );


    fprintf(
        file,

        "%s,%d,%s,%s,"
        "%.9f,%.9f,%.9f,"
        "%lld,%lld,%d\n",

        algorithm,

        result->size,

        type,

        distribution,

        result->average_time,

        result->min_time,

        result->max_time,

        result->comparisons,

        result->movements,

        result->sorted
    );


    fclose(file);

    return 1;
}