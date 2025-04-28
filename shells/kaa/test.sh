source ./paths.txt
if [[ $build_type == debug ]]; then
    echo "debug"
else
    echo "release"
fi
