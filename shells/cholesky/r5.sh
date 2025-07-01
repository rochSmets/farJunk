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

home_kaa=/home/smets

# rsync -av --exclude="checks" $WORKDIR/far/farMe/ionBeam/yao/run/yao-01a smets@kaa:/home/smets/

rsync -av --exclude="checks" --exclude=".log" --exclude=".phare" $WORKDIR/${run_dir} smets@kaa:${home_kaa}/${run_dir}
