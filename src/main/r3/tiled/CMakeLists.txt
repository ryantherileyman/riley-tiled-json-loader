
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(R3_TILED_JSON_LOADER_EXPORT_ALL_SYMBOLS ${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

set(R3_TILED_JSON_LOADER_SOURCES
	r3-tiled-CustomPropertyDefnUtils.cpp
	r3-tiled-MapLayerObjectTypeUtils.cpp
	r3-tiled-JsonLoader.cpp
	r3-tiled-JsonCustomPropertyLoader.cpp
	r3-tiled-JsonTilesetImageLoader.cpp
	r3-tiled-JsonTilesetTileLoader.cpp
	r3-tiled-JsonTilesetLoader.cpp
	r3-tiled-JsonMapLayerObjectPointLoader.cpp
	r3-tiled-JsonMapLayerObjectLoader.cpp
	r3-tiled-JsonMapLayerLoader.cpp
	r3-tiled-JsonMapTilesetLoader.cpp
	r3-tiled-JsonMapLoader.cpp
)

add_library(
	r3-TiledJsonLoader-lib STATIC
	${R3_TILED_JSON_LOADER_SOURCES}
)
target_link_libraries(
	r3-TiledJsonLoader-lib PRIVATE
	r3-ValidationUtils-lib
	jsoncpp_static
	r3-JsonCppUtils-lib
)
target_include_directories(r3-TiledJsonLoader-lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_library(
	r3-TiledJsonLoader-shared SHARED
	${R3_TILED_JSON_LOADER_SOURCES}
)
target_link_libraries(
	r3-TiledJsonLoader-shared PRIVATE
	r3-ValidationUtils-shared
	jsoncpp_lib
	r3-JsonCppUtils-shared
)
target_include_directories(r3-TiledJsonLoader-shared PUBLIC "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ${R3_TILED_JSON_LOADER_EXPORT_ALL_SYMBOLS})
