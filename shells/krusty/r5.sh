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

work_cholesky=/mnt/beegfs/workdir/roch.smets
shell_dir=$HOME/far/farJunk/shells/krusty

source ${shell_dir}/paths.txt

rsync -av --exclude="checks" --exclude=".log" --exclude=".phare" roch.smets@cholesky:${work_cholesky}/${run_dir}/ $HOME/${run_dir}/
