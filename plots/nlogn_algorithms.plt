set datafile separator ","

set terminal pngcairo size 1400,800 enhanced font "Arial,12"
set output "results\\graphs\\nlogn_algorithms.png"

set title "SORTLAB - O(n log n) Sorting Algorithms (Random Data)"
set xlabel "Dataset Size"
set ylabel "Average Execution Time (seconds)"

set grid
set key outside right
set logscale x
set logscale y

plot \
    'results/benchmark_results.csv' using ($2):(strcol(1) eq "Merge Sort" && strcol(4) eq "Random" ? $5 : 1/0) with linespoints title "Merge Sort", \
    'results/benchmark_results.csv' using ($2):(strcol(1) eq "Quick Sort" && strcol(4) eq "Random" ? $5 : 1/0) with linespoints title "Quick Sort", \
    'results/benchmark_results.csv' using ($2):(strcol(1) eq "Heap Sort" && strcol(4) eq "Random" ? $5 : 1/0) with linespoints title "Heap Sort"

unset output