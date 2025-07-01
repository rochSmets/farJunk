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

shell_dir=${WORKDIR}/far/farJunk/shells/cholesky

source ${shell_dir}/paths.txt

myself_kaa=( smets@129.104.27.86 )

rsync -av --exclude="checks" $WORKDIR/{$run_dir} "$myself_kaa":$HOME/{$run_dir}
