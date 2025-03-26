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

## ___ load modules
module load cmake/3.19.7
module load gcc/10.2.0
module load openmpi/4.1.0
module load hdf5/1.12.1
module load mambaforge/22.11.1-4

#use conda for phare env... created with mamba !
conda activate phare

## ___ set the PYTHONPATH
export PYTHONPATH=/mnt/beegfs/workdir/roch.smets/builds/master:/mnt/beegfs/home/LPP/roch.smets/codes/far/PHARE/pyphare

## ___ compile phare
cd $WORKDIR/builds/master
cmake -DCMAKE_CXX_FLAGS="-g3 -O3 -march=native -mtune=native -DPHARE_DIAG_DOUBLES=1" \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
      -DwithCaliper=OFF \
      -DtestMPI=OFF \
      -Dasan=OFF \
      -DdevMode=OFF \
      "$HOME"/codes/far/PHARE
make -j40
