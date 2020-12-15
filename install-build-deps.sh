echo "Please run this script with `sudo`."

git clone https://github.com/SFML/SFML --depth 1
pushd SFML

cmake -B build -DBUILD_SHARED_LIBS=FALSE
cmake --build build --config Release
cmake --install build --config Release

popd

rm -rf SFML
