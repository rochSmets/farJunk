source ./make.txt
cd $build_dir
cmake -DCMAKE_CXX_FLAGS="-g3 -O3 -march=native -mtune=native -DPHARE_DIAG_DOUBLES=1" \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
      -DwithCaliper=OFF \
      -DtestMPI=OFF \
      -Dasan=OFF \
      -DdevMode=OFF \
      "$HOME"/codes/far/PHARE
