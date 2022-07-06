#!/bin/bash
#SBATCH --job-name user_instrumentation_example
#SBATCH --time=0:02:0
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=2
#SBATCH -o user_instrumentation_example.out
#SBATCH -e user_instrumentation_example.err
#SBATCH -p test

module load oneapi intelmpi itac

mpiicpc -I/apps/developers/tools/itac/2021.4/1/default/itac/2021.4.0/include -L/apps/developers/tools/itac/2021.4/1/default/itac/2021.4.0/slib -lVTnull itac_test.cpp -o itac_test

mpirun -trace -np 2 ./itac_test

# To view profile run:
#     traceanalyzer itac_test.stf
