
cmake_minimum_required(VERSION 3.19)

project(RileyTiledJsonLoader VERSION 0.1)

include(FetchContent)

set(RILEY_CPP_UTILS_WITH_TESTS OFF)
FetchContent_Declare(
	RileyCppUtils
	GIT_REPOSITORY https://github.com/ryantherileyman/riley-cpp-utils.git
	GIT_TAG 1.1.0
)

FetchContent_MakeAvailable(RileyCppUtils)

set(JSONCPP_WITH_TESTS OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
FetchContent_Declare(
	JsonCpp
	GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
	GIT_TAG 1.9.4
)

FetchContent_MakeAvailable(JsonCpp)

unset(CMAKE_ARCHIVE_OUTPUT_DIRECTORY CACHE)
unset(CMAKE_LIBRARY_OUTPUT_DIRECTORY CACHE)
unset(CMAKE_PDB_OUTPUT_DIRECTORY CACHE)
unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY CACHE)

set(RILEY_JSONCPP_UTILS_WITH_TESTS OFF)
FetchContent_Declare(
	RileyJsonCppUtils
	GIT_REPOSITORY https://github.com/ryantherileyman/riley-jsoncpp-utils.git
	GIT_TAG 1.0.0
)

FetchContent_MakeAvailable(RileyJsonCppUtils)

add_subdirectory(src/main/r3/tiled)
