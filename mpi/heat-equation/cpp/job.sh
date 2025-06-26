#!/bin/bash
#SBATCH --job-name=heat-equation
#SBATCH --account=project_462000956
#SBATCH --partition=small
#SBATCH --nodes=1 
#SBATCH --ntasks-per-node=4
#SBATCH --time=00:10:00

srun ./heat_mpi
