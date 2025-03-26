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


rsync -av --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run01/ smets@129.104.27.86:/DATA/phare/harris/lbm/run01/
rsync -av --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run02/ smets@129.104.27.86:/DATA/phare/harris/lbm/run02/
rsync -av --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run03/ smets@129.104.27.86:/DATA/phare/harris/lbm/run03/
rsync -av --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run04/ smets@129.104.27.86:/DATA/phare/harris/lbm/run04/
rsync -av --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run05/ smets@129.104.27.86:/DATA/phare/harris/lbm/run05/
# rsync -av --exclude=".log" --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run01/ smets@129.104.27.86:/DATA/phare/harris/lbm/run01/
# rsync -av --exclude=".log" --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run02/ smets@129.104.27.86:/DATA/phare/harris/lbm/run02/
# rsync -av --exclude=".log" --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run03/ smets@129.104.27.86:/DATA/phare/harris/lbm/run03/
# rsync -av --exclude=".log" --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run04/ smets@129.104.27.86:/DATA/phare/harris/lbm/run04/
# rsync -av --exclude=".log" --exclude="checks" -e "ssh -A smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/run05/ smets@129.104.27.86:/DATA/phare/harris/lbm/run05/

# rsync -v --rsh "ssh smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/lbm/readme smets@129.104.27.86:/DATA/phare/harris/lbm/ # kaa
# rsync -v --rsh "ssh smets@129.104.27.3 ssh" /mnt/beegfs/workdir/roch.smets/sherpa/far/harris/tiny/harris.py smets@129.104.27.94:/home/smets/sherpa/far/harris/tiny # pharmacist
~
