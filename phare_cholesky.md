## Project referee/coordinator

*Firstname* : Roch
*Lastname* : Smets
*Email* : roch.smets@lpp.polytechnique.fr
*Laboratory* : LPP


## Project description

*Project acronym or project nickname* : phare
*Describe scientific goals that you are planning to address with the computing time on cholesky.*
Le projet PHARE (Parallel Hybrid PIC code with Adaptive mesh REfinement) a pour objectif de d�velopper un code plasma-�lectromagn�tique dans lequel une partie du plasma est trait� comme des particules (les protons) et l'autre comme un fluide (les �lectrons). Ce code (https://github.com/PHAREHUB/PHARE) est en d�veloppement et pour le moment, seule la version 1D est fonctionnelle. Nous avons comme objectif de d�velopper un code de tr�s haute performance, ce qui en l'�tat va n�cessiter un effort en acc�l�ration GPU.
D'un point de vue scientifique, ce code va permettre d'�tudier l'interaction entre un vent stellaire et un corps magn�tis�, de simuler le d�veloppeent des arches coronnales � la surface d'une �toile, ou encore l'�tude d'experiences d'astrophysique de laboratoire. L'aspect "maillage adaptatif" se justifie en premier lieu par l'�tude de sujets ou objets pour lequel la microphysique � petite �chelle doit s'�tudier en prenant aussi en compte les grandes �chelles.


## Resources required

*Indicate the job profile targeted for this project (number of cores, memory per job, storage needed...) and the softwares/libraries required (example: FFTW, HDF5...).*
Il y aura une grande partie des calculs d�di�e � des jobs tr�s court � vis�e de validation de d�veloppements (sur un nombre tr�s limit� de coeurs, typiquement 16). Il y aura aussi des jobs, tout aussi court, sur un plus grand nombre de noeuds (256) pour s'assurer d'un bon passage � l'�chelle. Ces runs de d�veloppement concerneront autant la queue GPU que la queue CPU. Etant li� au d�veloppement et non � la production, il est important que les runs courts s'executent sur les noeuds sans attente.
Ces jobs peuvent �tre tr�s gourmand en RAM d�s lors que les syst�mes sont grand et donc le nombre de particules important. Les plus gros calculs (~100 millions de particules) utilisent de l'ordre de 100 G en RAM, et par dump sur le disque.
Les fichiers produits pour les plus gros runs ne d�passeront pas 1TB par job. Mais l� encore, s'agissant d'une activit� de d�veloppement, la dur�e de vie de ces fichiers sera courte (max quelques mois).
Le code PHARE est �crit en C++17 et n�cessite la disponibilit� des outils/biblioth�qes HDF5 (parall�le), Python3 (ddt, mpi4py, h5py, pyyaml, numpy, scipy, matplotlib, seaborn), MPI, cmake 3.1x, compilateur c++ (gcc, clang), fortran, support openmp, openacc, git (avec acc�s r�seau vers l'ext�rieur pour git clone)


## Support

*If the project receives support (ANR, ERC), indicate requested funds for CPU hours.*
Pas pour le moment.




-- 

roch smets
infrastructure donnees & calcul scientifique
ecole polytechnique, route de saclay
91128 palaiseau - france
tel : +33 1 6933 5899
