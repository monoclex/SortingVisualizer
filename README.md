# Sorting Visualizer [![Nightly Build](https://github.com/SirJosh3917/SortingVisualizer/workflows/Nightly%20Build/badge.svg)](https://github.com/SirJosh3917/SortingVisualizer/actions)

<p align=center>
    <img src="./assets/sorting.gif"/>
</p>

This sorting visualizer was a simple project to introduce myself to

- How a modern C++ project is architected
- How to use CMake
- How to organize a project
- How to setup CI/CD for a C++ project
- How to write C++20 code

and it was a successful learning project. Overall, the take-away feeling I have from this project is that Rust is just C++, but if designed properly without baggage.

## Download

To download, please [download the build artifacts from the latest CI/CD run](https://github.com/SirJosh3917/SortingVisualizer/actions). After clicking the name of the latest run, scroll down and you should see an "Artifacts" section.

## About

This project, which is primarily a learning experiment to figure out the proper way to structure a C++ program, can hopefully be used to help others design and structure their own C++ SFML projects. As such, this project tries to be as simple as possible in that regard so that the reader can understand the concepts and introduce their own abstractions or bloat around the core process.

- This project is written in C++ 20. [SFML](https://www.sfml-dev.org/) was chosen to create the sorting display with.

- The resulting binary is statically linked to SFML so that there is no need for the user to install it, and on Windows builds, the standard C++ library is statically linked to as well so that users do not have to install the VC++ runtime.

- A `.clang-format` file, and the accompanying [Clang-Format VSCode extension](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) is used to ensure style consistency across the codebase.

- CMake is used to automatically generate and build the project for each platform.

- Github Actions is used to build and create artifacts of the program on every new commit.

## Building

Because this project statically links SFML, SFML needs to be built from source with static linking in mind. Please [check out the Github Actions file](https://github.com/SirJosh3917/SortingVisualizer/blob/main/.github/workflows/nightly_build.yml) for the most up-to-date steps to build the project.

1. Install SFML dependencies

On Ubuntu flavors of Linux, this involves installing `libxcursor-dev mesa-common-dev libfreetype6-dev libxrandr-dev libudev-dev libogg-dev libflac-dev libvorbis-dev libopenal-dev`.

No dependencies are needed on Windows.

2. Build SFML from source

Clone the SFML github repository, enable flags for static linking, and build. On Linux, build with the `-DBUILD_SHARED_LIBS=FALSE` flag only to statically link SFML. On Windows, build with the `-DSFML_USE_STATIC_STD_LIBS=TRUE -DBUILD_SHARED_LIBS=FALSE` flags to statically link SFML and the VC++ runtime.

```bash
# Linux
git clone https://github.com/SFML/SFML --depth 1
pushd SFML
  cmake -B build -DBUILD_SHARED_LIBS=FALSE
  cmake --build build --config Release
  sudo cmake --install build --config Release
popd

# Windows
git clone https://github.com/SFML/SFML --depth 1
pushd SFML
  cmake -B build -DSFML_USE_STATIC_STD_LIBS=TRUE -DBUILD_SHARED_LIBS=FALSE
  cmake --build build --config Release
  cmake --install build --config Release
popd
rm -Recurse -Force SFML
```

3. Build Sorting Visualizer

Finally, use CMake to build Sorting Visualizer. Make sure you've ran `cmake --install` when building SFML in the previous step, otherwise it won't be installed in your path.

```shell
cmake -B build
cmake --build build --config Release
cmake --install build --config Release
```
