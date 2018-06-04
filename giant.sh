#!/bin/sh
# Generate random networks and calculate the giant component size at different thresholds
# Parallelization: https://unix.stackexchange.com/a/216475

n=100  # default value
if [[ $# -gt 0 ]]; then
  n=$1
fi

mkdir -p out
mkdir -p figs
proc=8  # run in parallel

for seed in {1..40}
do
  ((i=i%proc)); ((i++==0)) && wait
  (./giant.exe -o out/giant_n${n}_s$(printf %02d $seed).out -n $n -s $seed) &
done
wait

Rscript ./make_figures.R $n
