#!/bin/sh
# Generating random networks
# Parallelization: https://unix.stackexchange.com/a/216475

proc=8  # run in parallel

for n in 100000 # 1000000
do
  for seed in {1..40}
  do
    ((i=i%proc)); ((i++==0)) && wait
    (./network.exe -o out/network_n${n}_s$(printf %02d $seed).out -n $n -s $seed) &
  done
done
wait
