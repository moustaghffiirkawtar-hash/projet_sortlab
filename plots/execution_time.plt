set datafile separator ","

set terminal pngcairo size 1400,800 enhanced font "Arial,12"
set output "results\\graphs\\execution_time_sorted.png"

set title "SORTLAB - Execution Time on Sorted Data"
set xlabel "Dataset Size"
set ylabel "Average Execution Time (seconds)"

set grid
set key outside right

set logscale x
set logscale y

plot \
    'results/benchmark_results.csv' using (strcol(4) eq "Sorted" && strcol(1) eq "Bubble Sort" ? $2 : 1/0):5 with linespoints title "Bubble Sort", \
    'results/benchmark_results.csv' using (strcol(4) eq "Sorted" && strcol(1) eq "Selection Sort" ? $2 : 1/0):5 with linespoints title "Selection Sort", \
    'results/benchmark_results.csv' using (strcol(4) eq "Sorted" && strcol(1) eq "Insertion Sort" ? $2 : 1/0):5 with linespoints title "Insertion Sort", \
    'results/benchmark_results.csv' using (strcol(4) eq "Sorted" && strcol(1) eq "Merge Sort" ? $2 : 1/0):5 with linespoints title "Merge Sort", \
    'results/benchmark_results.csv' using (strcol(4) eq "Sorted" && strcol(1) eq "Quick Sort" ? $2 : 1/0):5 with linespoints title "Quick Sort", \
    'results/benchmark_results.csv' using (strcol(4) eq "Sorted" && strcol(1) eq "Heap Sort" ? $2 : 1/0):5 with linespoints title "Heap Sort"