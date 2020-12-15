echo "You may need to run this script as administrator for cmake to install SFML"

git clone https://github.com/SFML/SFML --depth 1
pushd SFML

cmake -B build -DSFML_USE_STATIC_STD_LIBS=TRUE -DBUILD_SHARED_LIBS=FALSE
cmake --build build --config Release
cmake --install build --config Release

popd

rm -Recurse -Force SFML
