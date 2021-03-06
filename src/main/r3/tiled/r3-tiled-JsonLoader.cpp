
#include <regex>
#include <json/json.h>
#include <r3/validation/r3-validation-utils.hpp>
#include <r3/jsoncpp/r3-jsoncpp-utils.hpp>

namespace r3 {

	namespace tiled {

		namespace JsonPropertyName {

			const char* ID = "id";
			const char* NAME = "name";
			const char* TYPE = "type";
			const char* VERSION = "version";
			const char* X = "x";
			const char* Y = "y";
			const char* WIDTH = "width";
			const char* HEIGHT = "height";
			const char* PROPERTY_LIST = "properties";
			const char* VALUE = "value";

			namespace Tileset {

				const char* COLUMNS = "columns";
				const char* TILE_COUNT = "tilecount";
				const char* TILE_WIDTH = "tilewidth";
				const char* TILE_HEIGHT = "tileheight";
				const char* MARGIN = "margin";
				const char* SPACING = "spacing";
				const char* IMAGE_PATH = "image";
				const char* IMAGE_WIDTH = "imagewidth";
				const char* IMAGE_HEIGHT = "imageheight";
				const char* TILE_LIST = "tiles";

			}

			namespace Map {

				const char* ORIENTATION = "orientation";
				const char* INFINITE = "infinite";
				const char* BACKGROUND_COLOR = "backgroundcolor";
				const char* LAYER_LIST = "layers";

				const char* DATA = "data";
				const char* OBJECT_LIST = "objects";
				const char* TILESET_LIST = "tilesets";

				const char* POINT_FLAG = "point";
				const char* ELLIPSE_FLAG = "ellipse";
				const char* ROTATION = "rotation";
				const char* POLYLINE = "polyline";
				const char* POLYGON = "polygon";
				const char* TILE_GID = "gid";

				const char* FIRST_GID = "firstgid";
				const char* SOURCE_PATH = "source";

			}

		}

		namespace JsonPropertyValue {

			namespace FileTypeValue {

				const char* TILESET = "tileset";
				const char* MAP = "map";

			}

			namespace CustomPropertyTypeValue {

				const char* BOOLEAN = "bool";
				const char* COLOR = "color";
				const char* FLOAT = "float";
				const char* FILE = "file";
				const char* INTEGER = "int";
				const char* OBJECT = "object";
				const char* STRING = "string";

			}

			namespace MapLayerTypeValue {

				const char* TILE = "tilelayer";
				const char* OBJECT = "objectgroup";
				const char* GROUP = "group";

			}

			namespace MapOrientationValue {

				const char* ORTHOGONAL = "orthogonal";
				const char* ISOMETRIC = "isometric";
				const char* STAGGERED = "staggered";
				const char* HEXAGONAL = "hexagonal";

			}

		}

		namespace JsonTiledValidationUtils {

			bool dimensionValueValid(const Json::Value& jsonValue, const char* propertyName) {
				bool result =
					JsonValidationUtils::requiredInt(jsonValue, propertyName) &&
					JsonValidationUtils::intInRange(jsonValue, propertyName, r3::validation::IntRange::createMin(1));
				return result;
			}

			std::regex COLOR_REGEX("#[0-9a-f]{6}([0-9a-f]{2})?");

			bool colorValueValid(const Json::Value& jsonValue, const char* propertyName) {
				bool result = JsonValidationUtils::optionalString(jsonValue, propertyName);
				if (JsonValidationUtils::requiredString(jsonValue, propertyName)) {
					result = std::regex_match(jsonValue[propertyName].asString(), COLOR_REGEX);
				}
				return result;
			}

		}

	}

}
