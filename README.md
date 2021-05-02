# Riley Tiled Json Loader
The Riley Tiled Json Loader C++ library is used to load [Tiled](https://www.mapeditor.org/) map and tileset files into a Json::Value in memory.

This project makes use of the public domain [JsonCpp library](https://github.com/open-source-parsers/jsoncpp).

This project is currently considered to be in a pre-release phase.  It currently only supports the sub-set of features from Tiled that are being used for my game [The Colon Case](https://rileyentertainment.itch.io/the-colon-case).  At some point in the future, my plan is to sweep back to support all features from the most recent version of Tiled, and make this library publicly available.

## r3-TiledJsonLoader

This library provides two main functions:
* `r3::tiled::JsonTilesetLoader::loadFromJsonFile` loads and validates a Tiled tileset file in JSON format
* `r3::tiled::JsonMapLoader::loadFromJsonFile` loads and validates a Tiled map file in JSON format

## Notes about the author

If you like my work, or use this library in your own projects, please consider subscribing to my YouTube channels, or following me on itch.io:

[Riley Entertainment Games](https://www.youtube.com/channel/UCBIc5YUGLv1NvjkbSqETY7Q) - for some of my past game development work.  This includes videos on the wonderful [Tiled map editor](https://www.mapeditor.org/), and learning about the [CMake build system](https://cmake.org/).

[Riley Entertainment](https://www.youtube.com/channel/UCHvoItS_0Nmueb0IuZoLSKg) - for lots of Eve Online content, and a few old animated films.

[Riley Entertainment on itch.io](https://rileyentertainment.itch.io/) - to follow the progress on my game development.
