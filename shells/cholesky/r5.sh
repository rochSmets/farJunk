#!/bin/bash

## ___ sbatch directives
#SBATCH --job-name=r5
#SBATCH --output=%x-%j.log
#
#SBATCH --ntasks=1
#SBATCH --time=06:00:00
#SBATCH --partition=cpu_seq
#SBATCH --account=phare
#SBATCH --mail-type=ALL
#SBATCH --mail-user=roch.smets@lpp.polytechnique.fr

kaa=( smets@129.104.27.86 )

source ./paths.txt

rsync -av --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" $run_dir "$kaa":"$run_dir"
