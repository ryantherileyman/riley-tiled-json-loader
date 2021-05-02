
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(
	CustomPropertyDefnUtilsTests
	CustomPropertyDefnUtilsTests-main.cpp
 )
target_link_libraries(
	CustomPropertyDefnUtilsTests PRIVATE
	r3-TiledJsonLoader-lib
)
target_include_directories(CustomPropertyDefnUtilsTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(
	JsonCustomPropertyLoaderTests
	JsonCustomPropertyLoaderTests-main.cpp
)
target_link_libraries(
	JsonCustomPropertyLoaderTests PRIVATE
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonCustomPropertyLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(
	JsonTilesetImageLoaderTests
	JsonTilesetImageLoaderTests-main.cpp
)
target_link_libraries(
	JsonTilesetImageLoaderTests
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonTilesetImageLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(
	JsonTilesetTileLoaderTests
	JsonTilesetTileLoaderTests-main.cpp
)
target_link_libraries(
	JsonTilesetTileLoaderTests
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonTilesetTileLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(
	JsonTilesetLoaderTests
	JsonTilesetLoaderTests-main.cpp
)
target_link_libraries(
	JsonTilesetLoaderTests
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonTilesetLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_custom_command(
	TARGET JsonTilesetLoaderTests
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/src/test-resources/r3/tiled/JsonTilesetLoader
		$<TARGET_FILE_DIR:JsonTilesetLoaderTests>/test-resources/r3/tiled/JsonTilesetLoader
)

add_executable(
	JsonMapLayerObjectPointLoaderTests
	JsonMapLayerObjectPointLoaderTests-main.cpp
)
target_link_libraries(
	JsonMapLayerObjectPointLoaderTests
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonMapLayerObjectPointLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(
	JsonMapLayerObjectLoaderTests
	JsonMapLayerObjectLoaderTests-main.cpp
)
target_link_libraries(
	JsonMapLayerObjectLoaderTests
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonMapLayerObjectLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(
	JsonMapLayerLoaderTests
	JsonMapLayerLoaderTests-main.cpp
)
target_link_libraries(
	JsonMapLayerLoaderTests
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonMapLayerLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(
	JsonMapTilesetLoaderTests
	JsonMapTilesetLoaderTests-main.cpp
)
target_link_libraries(
	JsonMapTilesetLoaderTests
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonMapTilesetLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(
	JsonMapLoaderTests
	JsonMapLoaderTests-main.cpp
)
target_link_libraries(
	JsonMapLoaderTests
	jsoncpp_static
	r3-TiledJsonLoader-lib
)
target_include_directories(JsonMapLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_custom_command(
	TARGET JsonMapLoaderTests
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/src/test-resources/r3/tiled/JsonMapLoader
		$<TARGET_FILE_DIR:JsonTilesetLoaderTests>/test-resources/r3/tiled/JsonMapLoader
)

add_test(NAME CustomPropertyDefnUtils COMMAND CustomPropertyDefnUtilsTests)
add_test(NAME JsonCustomPropertyLoader COMMAND JsonCustomPropertyLoaderTests)
add_test(NAME JsonTilesetImageLoader COMMAND JsonTilesetImageLoaderTests)
add_test(NAME JsonTilesetTileLoader COMMAND JsonTilesetTileLoaderTests)
add_test(NAME JsonTilesetLoader COMMAND JsonTilesetLoaderTests)
add_test(NAME JsonMapLayerObjectPointLoader COMMAND JsonMapLayerObjectPointLoaderTests)
add_test(NAME JsonMapLayerObjectLoader COMMAND JsonMapLayerObjectLoaderTests)
add_test(NAME JsonMapLayerLoader COMMAND JsonMapLayerLoaderTests)
add_test(NAME JsonMapTilesetLoader COMMAND JsonMapTilesetLoaderTests)
add_test(NAME JsonMapLoader COMMAND JsonMapLoaderTests)
