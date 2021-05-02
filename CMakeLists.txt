
cmake_minimum_required(VERSION 3.19)

project(RileyTiledJsonLoader VERSION 0.2)

add_subdirectory(dependencies/riley-cpp-utils)
add_subdirectory(dependencies/json-cpp)
add_subdirectory(dependencies/riley-json-cpp-utils)

option(RILEY_TILED_JSON_LOADER_WITH_TESTS "Build and run RileyTiledJsonLoader text executables" ON)

add_subdirectory(src/main/r3/tiled)

if (${RILEY_TILED_JSON_LOADER_WITH_TESTS})
	enable_testing()
	add_subdirectory(src/test/r3/tiled)
endif()
