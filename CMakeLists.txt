cmake_minimum_required(VERSION 3.17.4)

project(
	SortingVisualizer

	VERSION 0.1.0
	DESCRIPTION "SortingVisualizer - A sorting visualizer, made in C++, primarily made for the purpose of learning about the build tooling surrounding C++."
	HOMEPAGE_URL "https://github.com/SirJosh3917/SortingVisualizer"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_sources(${PROJECT_NAME} PUBLIC
	"src/SortingVisualizer/main.cpp"
	"src/SortingVisualizer/Display.cpp"
)

target_link_libraries(${PROJECT_NAME} sfml-graphics)
