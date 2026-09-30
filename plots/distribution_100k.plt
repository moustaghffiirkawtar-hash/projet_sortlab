# ============================================================
# SORTLAB - Data Distribution Analysis
# N = 100000
# ============================================================

set datafile separator ","

set terminal pngcairo size 1500,850 enhanced font "Arial,12"
set output "results\\graphs\\distribution_100k.png"

set title "SORTLAB - Effect of Data Distribution at N = 100000"
set xlabel "Data Distribution"
set ylabel "Average Execution Time (seconds)"

set grid
set key outside right

# ------------------------------------------------------------
# X-axis labels
# ------------------------------------------------------------

set xtics ("Sorted" 1, \
           "Random" 2, \
           "Reverse Sorted" 3, \
           "Nearly Sorted" 4, \
           "Duplicates" 5)

set xrange [0.5:5.5]

# ------------------------------------------------------------
# Logarithmic Y-axis
# ------------------------------------------------------------

set logscale y

# ------------------------------------------------------------
# Bar configuration
# ------------------------------------------------------------

set style fill solid 0.85
set boxwidth 0.13

# ------------------------------------------------------------
# Distribution -> X position
#
# Sorted          = 1
# Random          = 2
# Reverse Sorted  = 3
# Nearly Sorted   = 4
# Duplicates      = 5
# ------------------------------------------------------------

# ------------------------------------------------------------
# Plot
# ------------------------------------------------------------

plot \
    'results/benchmark_results.csv' \
    using (strcol(2) eq "100000" && strcol(1) eq "Bubble Sort" ? \
          (strcol(4) eq "Sorted" ? 0.70 : \
           strcol(4) eq "Random" ? 1.70 : \
           strcol(4) eq "Reverse Sorted" ? 2.70 : \
           strcol(4) eq "Nearly Sorted" ? 3.70 : \
           strcol(4) eq "Duplicates" ? 4.70 : 1/0) : 1/0):5 \
    with boxes title "Bubble Sort", \
\
    '' using (strcol(2) eq "100000" && strcol(1) eq "Selection Sort" ? \
          (strcol(4) eq "Sorted" ? 0.82 : \
           strcol(4) eq "Random" ? 1.82 : \
           strcol(4) eq "Reverse Sorted" ? 2.82 : \
           strcol(4) eq "Nearly Sorted" ? 3.82 : \
           strcol(4) eq "Duplicates" ? 4.82 : 1/0) : 1/0):5 \
    with boxes title "Selection Sort", \
\
    '' using (strcol(2) eq "100000" && strcol(1) eq "Insertion Sort" ? \
          (strcol(4) eq "Sorted" ? 0.94 : \
           strcol(4) eq "Random" ? 1.94 : \
           strcol(4) eq "Reverse Sorted" ? 2.94 : \
           strcol(4) eq "Nearly Sorted" ? 3.94 : \
           strcol(4) eq "Duplicates" ? 4.94 : 1/0) : 1/0):5 \
    with boxes title "Insertion Sort", \
\
    '' using (strcol(2) eq "100000" && strcol(1) eq "Merge Sort" ? \
          (strcol(4) eq "Sorted" ? 1.06 : \
           strcol(4) eq "Random" ? 2.06 : \
           strcol(4) eq "Reverse Sorted" ? 3.06 : \
           strcol(4) eq "Nearly Sorted" ? 4.06 : \
           strcol(4) eq "Duplicates" ? 5.06 : 1/0) : 1/0):5 \
    with boxes title "Merge Sort", \
\
    '' using (strcol(2) eq "100000" && strcol(1) eq "Quick Sort" ? \
          (strcol(4) eq "Sorted" ? 1.18 : \
           strcol(4) eq "Random" ? 2.18 : \
           strcol(4) eq "Reverse Sorted" ? 3.18 : \
           strcol(4) eq "Nearly Sorted" ? 4.18 : \
           strcol(4) eq "Duplicates" ? 5.18 : 1/0) : 1/0):5 \
    with boxes title "Quick Sort", \
\
    '' using (strcol(2) eq "100000" && strcol(1) eq "Heap Sort" ? \
          (strcol(4) eq "Sorted" ? 1.30 : \
           strcol(4) eq "Random" ? 2.30 : \
           strcol(4) eq "Reverse Sorted" ? 3.30 : \
           strcol(4) eq "Nearly Sorted" ? 4.30 : \
           strcol(4) eq "Duplicates" ? 5.30 : 1/0) : 1/0):5 \
    with boxes title "Heap Sort"

unset logscale y
unset output