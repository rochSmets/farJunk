#!/bin/bash

## ___ sbatch directives
#SBATCH --job-name=harris
#SBATCH --output=%x-%j.log
#
#SBATCH --ntasks=20
#SBATCH --time=12:00:00
#SBATCH --partition=cpu_shared
#SBATCH --account=phare
#SBATCH --mail-type=ALL
#SBATCH --mail-user=roch.smets@lpp.polytechnique.fr

/mnt/beegfs/workdir/roch.smets/far/farJunk/shells/cholesky

shell_dir=${WORKDIR}/far/farJunk/shells/cholesky

## ___ load modules
source ${shell_dir}/module.sh

## ___ use conda for phare env... created with mamba !
conda activate phare

## ___ set the PYTHONPATH
source ${shell_dir}/paths.txt
export PYTHONPATH="${python_path}"

## ___ run phare with python
cd $run_dir
mpirun -n $SLURM_NTASKS python $job_name
