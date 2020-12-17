cmake_minimum_required(VERSION 3.16.3)

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
if(WIN32)
	set(SFML_USE_STATIC_STD_LIBS TRUE)
endif()
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(${PROJECT_NAME})

if(MSVC)
	set_property(TARGET ${PROJECT_NAME} PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_sources(${PROJECT_NAME} PUBLIC
	"src/SortingVisualizer/main.cpp"
	"src/SortingVisualizer/Collection.cpp"
	"src/SortingVisualizer/Display.cpp"
	"src/SortingVisualizer/Algorithms/BubbleSort.cpp"
)

target_link_libraries(${PROJECT_NAME} sfml-graphics)
