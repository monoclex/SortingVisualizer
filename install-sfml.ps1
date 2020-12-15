git clone https://github.com/SFML/SFML --depth 1

pushd SFML

cmake -B build
cmake --build build --config Release
cmake --install build --config Release

echo "You may need to run this script as administrator for cmake to install SFML"

popd

rm -Recurse -Force SFML
