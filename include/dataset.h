#ifndef DATASET_H
#define DATASET_H

/* ==============================
   DATA DISTRIBUTIONS
   ============================== */

typedef enum {
    RANDOM,
    SORTED,
    REVERSE_SORTED,
    NEARLY_SORTED,
    DUPLICATES
} Distribution;


/* ==============================
   DATA TYPES
   ============================== */

typedef enum {
    DATA_INT,
    DATA_FLOAT
} DataType;


/* ==============================
   DATASET STRUCTURE
   ============================== */

typedef struct {

    void *data;

    int size;

    DataType type;

    Distribution distribution;

} Dataset;


/* ==============================
   INTEGER DATASETS
   ============================== */

int* generate_random_ints(int n);
int* generate_sorted_ints(int n);
int* generate_reverse_ints(int n);
int* generate_nearly_sorted_ints(int n);
int* generate_duplicate_ints(int n);


/* ==============================
   FLOAT DATASETS
   ============================== */

float* generate_random_floats(int n);
float* generate_sorted_floats(int n);
float* generate_reverse_floats(int n);
float* generate_nearly_sorted_floats(int n);
float* generate_duplicate_floats(int n);


/* ==============================
   UNIFIED INTEGER GENERATOR
   ============================== */

int* generate_dataset(int n, Distribution distribution);


/* ==============================
   DATASET MANAGEMENT
   ============================== */

Dataset* create_dataset(
    int n,
    DataType type,
    Distribution distribution
);

Dataset* copy_dataset(Dataset *source);

void destroy_dataset(Dataset *dataset);


/* ==============================
   UTILITIES
   ============================== */

void print_array(int *array, int n);
void free_array(int *array);

#endif