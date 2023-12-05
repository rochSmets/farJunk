## Project referee/coordinator

*Firstname* : Roch
*Lastname* : Smets
*Email* : roch.smets@lpp.polytechnique.fr
*Laboratory* : LPP


## Project description

*Project acronym or project nickname* : phare
*Describe scientific goals that you are planning to address with the computing time on cholesky.*
Le projet PHARE (Parallel Hybrid PIC code with Adaptive mesh REfinement) a pour objectif de développer un code plasma-électromagnétique dans lequel une partie du plasma est traité comme des particules (les protons) et l'autre comme un fluide (les électrons). Ce code (https://github.com/PHAREHUB/PHARE) est en développement et pour le moment, seule la version 1D est fonctionnelle. Nous avons comme objectif de développer un code de très haute performance, ce qui en l'état va nécessiter un effort en accélération GPU.
D'un point de vue scientifique, ce code va permettre d'étudier l'interaction entre un vent stellaire et un corps magnétisé, de simuler le développeent des arches coronnales à la surface d'une étoile, ou encore l'étude d'experiences d'astrophysique de laboratoire. L'aspect "maillage adaptatif" se justifie en premier lieu par l'étude de sujets ou objets pour lequel la microphysique à petite échelle doit s'étudier en prenant aussi en compte les grandes échelles.


## Resources required

*Indicate the job profile targeted for this project (number of cores, memory per job, storage needed...) and the softwares/libraries required (example: FFTW, HDF5...).*
Il y aura une grande partie des calculs dédiée à des jobs très court à visée de validation de développements (sur un nombre très limité de coeurs, typiquement 16). Il y aura aussi des jobs, tout aussi court, sur un plus grand nombre de noeuds (256) pour s'assurer d'un bon passage à l'échelle. Ces runs de développement concerneront autant la queue GPU que la queue CPU. Etant lié au développement et non à la production, il est important que les runs courts s'executent sur les noeuds sans attente.
Ces jobs peuvent être très gourmand en RAM dès lors que les systèmes sont grand et donc le nombre de particules important. Les plus gros calculs (~100 millions de particules) utilisent de l'ordre de 100 G en RAM, et par dump sur le disque.
Les fichiers produits pour les plus gros runs ne dépasseront pas 1TB par job. Mais là encore, s'agissant d'une activité de développement, la durée de vie de ces fichiers sera courte (max quelques mois).
Le code PHARE est écrit en C++17 et nécessite la disponibilité des outils/bibliothèqes HDF5 (parallèle), Python3 (ddt, mpi4py, h5py, pyyaml, numpy, scipy, matplotlib, seaborn), MPI, cmake 3.1x, compilateur c++ (gcc, clang), fortran, support openmp, openacc, git (avec accès réseau vers l'extérieur pour git clone)


## Support

*If the project receives support (ANR, ERC), indicate requested funds for CPU hours.*
Pas pour le moment.




-- 

roch smets
infrastructure donnees & calcul scientifique
ecole polytechnique, route de saclay
91128 palaiseau - france
tel : +33 1 6933 5899
