#include <stdio.h>
#include <stdlib.h>

#include "../include/dataset.h"


/* ==============================
   RANDOM INTEGER DATASET
   ============================== */

int* generate_random_ints(int n) {

    int *array = malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = rand() % 1000;
    }

    return array;
}


/* ==============================
   SORTED INTEGER DATASET
   ============================== */

int* generate_sorted_ints(int n) {

    int *array = malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = i;
    }

    return array;
}


/* ==============================
   REVERSE SORTED DATASET
   ============================== */

int* generate_reverse_ints(int n) {

    int *array = malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = n - i;
    }

    return array;
}


/* ==============================
   NEARLY SORTED DATASET
   ============================== */

int* generate_nearly_sorted_ints(int n) {

    int *array = malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    /* Start with a sorted array */
    for (int i = 0; i < n; i++) {
        array[i] = i;
    }

    /* Introduce a few random disturbances */
    int disturbances = n / 100;

    if (disturbances < 1) {
        disturbances = 1;
    }

    for (int i = 0; i < disturbances; i++) {

        int a = rand() % n;
        int b = rand() % n;

        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    return array;
}


/* ==============================
   MANY DUPLICATES DATASET
   ============================== */

int* generate_duplicate_ints(int n) {

    int *array = malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = rand() % 10;
    }

    return array;
}


/* ==============================
   PRINT DATASET PREVIEW
   ============================== */

void print_array(int *array, int n) {

    int limit = n < 10 ? n : 10;

    printf("First %d elements:\n", limit);

    for (int i = 0; i < limit; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    if (n > 10) {

        printf("...\n");

        printf("Last 10 elements:\n");

        for (int i = n - 10; i < n; i++) {
            printf("%d ", array[i]);
        }

        printf("\n");
    }
}


/* ==============================
   FREE MEMORY
   ============================== */

void free_array(int *array) {
    free(array);
}

/* ==============================
   UNIFIED DATASET GENERATOR
   ============================== */

int* generate_dataset(int n, Distribution distribution) {

    switch (distribution) {

        case RANDOM:
            return generate_random_ints(n);

        case SORTED:
            return generate_sorted_ints(n);

        case REVERSE_SORTED:
            return generate_reverse_ints(n);

        case NEARLY_SORTED:
            return generate_nearly_sorted_ints(n);

        case DUPLICATES:
            return generate_duplicate_ints(n);

        default:
            printf("Unknown distribution!\n");
            return NULL;
    }
}

/* ==============================
   RANDOM FLOAT DATASET
   ============================== */

float* generate_random_floats(int n) {

    float *array = malloc(n * sizeof(float));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = ((float)rand() / RAND_MAX) * 1000.0f;
    }

    return array;
}


/* ==============================
   SORTED FLOAT DATASET
   ============================== */

float* generate_sorted_floats(int n) {

    float *array = malloc(n * sizeof(float));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = (float)i;
    }

    return array;
}


/* ==============================
   REVERSE SORTED FLOAT DATASET
   ============================== */

float* generate_reverse_floats(int n) {

    float *array = malloc(n * sizeof(float));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = (float)(n - i);
    }

    return array;
}


/* ==============================
   NEARLY SORTED FLOAT DATASET
   ============================== */

float* generate_nearly_sorted_floats(int n) {

    float *array = malloc(n * sizeof(float));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = (float)i;
    }

    int disturbances = n / 100;

    if (disturbances < 1) {
        disturbances = 1;
    }

    for (int i = 0; i < disturbances; i++) {

        int a = rand() % n;
        int b = rand() % n;

        float temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    return array;
}


/* ==============================
   FLOAT DATASET WITH DUPLICATES
   ============================== */

float* generate_duplicate_floats(int n) {

    float *array = malloc(n * sizeof(float));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = (float)(rand() % 10);
    }

    return array;
}

/* ==============================
   CREATE DATASET OBJECT
   ============================== */

Dataset* create_dataset(
    int n,
    DataType type,
    Distribution distribution
) {

    Dataset *dataset = malloc(sizeof(Dataset));

    if (dataset == NULL) {
        printf("Dataset structure allocation failed!\n");
        return NULL;
    }


    dataset->data = NULL;

    dataset->size = n;

    dataset->type = type;

    dataset->distribution = distribution;


    /* ==============================
       INTEGER DATASET
       ============================== */

    if (type == DATA_INT) {

        dataset->data = generate_dataset(
            n,
            distribution
        );
    }


    /* ==============================
       FLOAT DATASET
       ============================== */

    else if (type == DATA_FLOAT) {

        switch (distribution) {

            case RANDOM:
                dataset->data = generate_random_floats(n);
                break;

            case SORTED:
                dataset->data = generate_sorted_floats(n);
                break;

            case REVERSE_SORTED:
                dataset->data = generate_reverse_floats(n);
                break;

            case NEARLY_SORTED:
                dataset->data = generate_nearly_sorted_floats(n);
                break;

            case DUPLICATES:
                dataset->data = generate_duplicate_floats(n);
                break;

            default:
                dataset->data = NULL;
        }
    }


    if (dataset->data == NULL) {

        printf("Dataset generation failed!\n");

        free(dataset);

        return NULL;
    }


    return dataset;
}
/* ==============================
   DESTROY DATASET OBJECT
   ============================== */

void destroy_dataset(Dataset *dataset) {

    if (dataset == NULL) {
        return;
    }

    free(dataset->data);

    free(dataset);
}
/* ==============================
   COPY DATASET
   ============================== */

Dataset* copy_dataset(Dataset *source) {

    if (source == NULL) {
        return NULL;
    }


    Dataset *copy = malloc(sizeof(Dataset));

    if (copy == NULL) {
        printf("Dataset copy allocation failed!\n");
        return NULL;
    }


    copy->size = source->size;

    copy->type = source->type;

    copy->distribution = source->distribution;


    /* ==============================
       COPY INTEGER DATA
       ============================== */

    if (source->type == DATA_INT) {

        copy->data =
            malloc(source->size * sizeof(int));


        if (copy->data == NULL) {

            free(copy);

            return NULL;
        }


        int *source_data = (int *)source->data;

        int *copy_data = (int *)copy->data;


        for (int i = 0; i < source->size; i++) {

            copy_data[i] = source_data[i];
        }
    }


    /* ==============================
       COPY FLOAT DATA
       ============================== */

    else if (source->type == DATA_FLOAT) {

        copy->data =
            malloc(source->size * sizeof(float));


        if (copy->data == NULL) {

            free(copy);

            return NULL;
        }


        float *source_data = (float *)source->data;

        float *copy_data = (float *)copy->data;


        for (int i = 0; i < source->size; i++) {

            copy_data[i] = source_data[i];
        }
    }


    return copy;
}