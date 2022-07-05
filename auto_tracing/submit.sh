#!/bin/bash
#SBATCH --job-name itac_example
#SBATCH --time=0:02:0
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=2
#SBATCH -o itac_example.out
#SBATCH -e itac_example.err
#SBATCH -p test

export FLAVOUR_NOCONFLICT=1
module load gcc oneapi intelmpi itac

mpiicpc itac_test.cpp -o itac_test

mpirun -trace -np 2 ./itac_test

# To view profile run:
#     traceanalyzer itac_test.stf
