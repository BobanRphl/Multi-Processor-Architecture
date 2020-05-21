#!/bin/bash
#SBATCH -J histogram.%u
#SBATCH -o histogram.%u.o%j
#SBATCH -e histogram.%u.e%j
#SBATCH -n 64
#SBATCH --exclusive
#SBATCH -p normal # normal queue; use development or serial if queue wait time is too long
#SBATCH -t 01:00:00 # 1 hour

#module load mpi/mpich-x86_64

for i in 1 2 4 8 16 32 64
do
    echo "running histogram using $i processes ..."
    mpiexec -n $i ./histogram 100 0 100 1000000
done
