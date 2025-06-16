#!/bin/bash

## ___ sbatch directives
#SBATCH --job-name=compile_phare
#SBATCH --output=%x-%j.log
#
#SBATCH --nodes=1
#SBATCH --ntasks=40
#SBATCH --time=00:30:00
#SBATCH --partition=cpu_test
#SBATCH --account=phare
#SBATCH --mail-type=ALL
#SBATCH --mail-user=roch.smets@lpp.polytechnique.fr

shell_dir=${WORKDIR}/far/farJunk/shells/cholesky

## ___ load modules
source ${shell_dir}/module.sh

## ___ use conda for phare env... created with mamba !
conda activate phare

## ___ set the PYTHONPATH
source ${shell_dir}/paths.txt
export PYTHONPATH="${python_path}"

## ___ compile phare
cd $build_dir
cmake -DCMAKE_CXX_FLAGS="-g3 -O3 -march=native -mtune=native -DPHARE_DIAG_DOUBLES=1" \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
      -DwithCaliper=OFF \
      -DtestMPI=OFF \
      -Dasan=OFF \
      -DdevMode=OFF \
      "$src_dir"
make -j40
