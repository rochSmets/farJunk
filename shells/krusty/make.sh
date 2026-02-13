current_dir=$PWD
source ${HOME}/far/farJunk/shells/krusty/paths.txt
cd ${build_dir}
if [[ $build_type == debug ]]; then
    cmake -DCMAKE_BUILD_TYPE=Debug \
          -DCMAKE_CXX_FLAGS="-g3 -O0 -DPHARE_DIAG_DOUBLES=1" \
          -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
          -DwithCaliper=OFF \
          -DtestMPI=OFF \
          -Dasan=OFF \
          -DdevMode=ON \
          "$src_dir"
else
    cmake -DCMAKE_CXX_FLAGS="-g3 -O3 -march=native -mtune=native -DPHARE_DIAG_DOUBLES=1" \
          -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
          -DwithCaliper=OFF \
          -DtestMPI=OFF \
          -Dasan=OFF \
          -DdevMode=ON \
          "$src_dir"
fi
make -j4
cd $current_dir
