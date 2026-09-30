set datafile separator ","

set terminal pngcairo size 1400,800 enhanced font "Arial,12"
set output "results\\graphs\\movements.png"

set title "SORTLAB - Number of Movements vs Dataset Size (Random Data)"
set xlabel "Dataset Size"
set ylabel "Number of Movements"

set grid
set key outside right
set logscale x
set logscale y

plot \
    'results/benchmark_results.csv' using (strcol(1) eq "Bubble Sort" && strcol(4) eq "Random" ? $2 : 1/0):9 with linespoints title "Bubble Sort", \
    'results/benchmark_results.csv' using (strcol(1) eq "Selection Sort" && strcol(4) eq "Random" ? $2 : 1/0):9 with linespoints title "Selection Sort", \
    'results/benchmark_results.csv' using (strcol(1) eq "Insertion Sort" && strcol(4) eq "Random" ? $2 : 1/0):9 with linespoints title "Insertion Sort", \
    'results/benchmark_results.csv' using (strcol(1) eq "Merge Sort" && strcol(4) eq "Random" ? $2 : 1/0):9 with linespoints title "Merge Sort", \
    'results/benchmark_results.csv' using (strcol(1) eq "Quick Sort" && strcol(4) eq "Random" ? $2 : 1/0):9 with linespoints title "Quick Sort", \
    'results/benchmark_results.csv' using (strcol(1) eq "Heap Sort" && strcol(4) eq "Random" ? $2 : 1/0):9 with linespoints title "Heap Sort"