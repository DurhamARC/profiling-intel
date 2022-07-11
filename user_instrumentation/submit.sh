#!/bin/bash
#SBATCH --time=0:02:0
#SBATCH --ntasks=2
#SBATCH --partition test

module load oneapi intelmpi itac

mpiicpc -I$ITAC_HOME/itac/latest/include -L$ITAC_HOME/itac/latest/slib -lVTnull itac_test.cpp -o itac_test

mpirun -trace ./itac_test

# To view profile run:
#     traceanalyzer itac_test.stf
