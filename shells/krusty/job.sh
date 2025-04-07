## ___ set the PYTHONPATH
source ./paths.txt
export PYTHONPATH="${python_path}"

## ___ run phare with python
cd $run_dir
mpirun -n 12 python $job_name
