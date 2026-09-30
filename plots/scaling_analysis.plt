# ============================================================
# SORTLAB - SCALING ANALYSIS
# ============================================================
#
# Execution time versus dataset size.
#
# Distribution : Random
# Data type    : INT
#
# ============================================================


# ------------------------------------------------------------
# SHARED SETTINGS
# ------------------------------------------------------------

set datafile separator ","

set terminal pngcairo size 1500,850 enhanced font "Arial,12"

set grid

set key outside right

set xrange [0:500000]
set format x "%.0f"


# ============================================================
# GRAPH 1 - THE BIG PICTURE
# ============================================================
#
# Shows all 6 algorithms.
# Y-axis: 0 to 90 seconds.
# The slow algorithms dominate.
#
# ============================================================

set output "results\\graphs\\scaling_analysis.png"

set title \
    "SORTLAB - Execution Time Scaling (Big Picture)" \
    font "Arial,18"

set xlabel "Dataset Size (n)" font "Arial,14"
set ylabel "Average Execution Time (seconds)" font "Arial,14"

set format y "%.0f"

plot \
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Bubble Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Bubble Sort" with linespoints, \
\
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Selection Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Selection Sort" with linespoints, \
\
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Insertion Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Insertion Sort" with linespoints, \
\
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Merge Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Merge Sort" with linespoints, \
\
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Quick Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Quick Sort" with linespoints, \
\
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Heap Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Heap Sort" with linespoints


# ============================================================
# GRAPH 2 - THE ZOOMED VIEW
# ============================================================
#
# Shows only the 3 fast algorithms.
# Y-axis: 0 to 0.5 seconds.
# Now you can clearly see Quick vs Merge vs Heap.
#
# ============================================================

set output "results\\graphs\\scaling_analysis_zoom.png"

set title \
    "SORTLAB - Execution Time Scaling (Zoom: O(n log n) Algorithms)" \
    font "Arial,18"

set xlabel "Dataset Size (n)" font "Arial,14"
set ylabel "Average Execution Time (seconds)" font "Arial,14"

set yrange [0:0.5]
set format y "%.2f"

plot \
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Merge Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Merge Sort" with linespoints, \
\
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Quick Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Quick Sort" with linespoints, \
\
    'results/benchmark_results.csv' \
    using (strcol(1) eq "Heap Sort" && strcol(4) eq "Random" ? $2 : 1/0):5 \
    title "Heap Sort" with linespoints


unset output