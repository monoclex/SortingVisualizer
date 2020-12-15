cmake_minimum_required(VERSION 3.17.0)

project(
	SfmlTest

	VERSION 0.1.0
	DESCRIPTION "SfmlTest project"
	HOMEPAGE_URL "https://github.com/SirJosh3917/SfmlTest"
	LANGUAGES CXX
)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(SfmlTest
	src/main.cpp
)

target_link_libraries(SfmlTest sfml-graphics)
