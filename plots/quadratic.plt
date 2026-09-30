set datafile separator ","

set terminal pngcairo size 1400,800 enhanced font "Arial,12"
set output "results\\graphs\\quadratic_algorithms.png"

set title "SORTLAB - Quadratic Sorting Algorithms (Random Data)"
set xlabel "Dataset Size"
set ylabel "Average Execution Time (seconds)"

set grid
set key outside right
set logscale x
set logscale y

plot \
    'results/benchmark_results.csv' using ($2):(strcol(1) eq "Bubble Sort" && strcol(4) eq "Random" ? $5 : 1/0) with linespoints title "Bubble Sort", \
    'results/benchmark_results.csv' using ($2):(strcol(1) eq "Selection Sort" && strcol(4) eq "Random" ? $5 : 1/0) with linespoints title "Selection Sort", \
    'results/benchmark_results.csv' using ($2):(strcol(1) eq "Insertion Sort" && strcol(4) eq "Random" ? $5 : 1/0) with linespoints title "Insertion Sort"

unset output