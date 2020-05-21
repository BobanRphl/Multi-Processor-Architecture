#!/bin/bash
#SBATCH -J jacobi.%u
#SBATCH -o jacobi.%u.o%j
#SBATCH -e jacobi.%u.e%j
#SBATCH -n 16
#SBATCH -p normal # normal queue; use development or serial if queue wait time is too long
#SBATCH -t 01:00:00 # 1 hour

./jacobi 1 1000 10
