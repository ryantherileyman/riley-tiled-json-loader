
#include <regex>
#include <stdio.h>
#include <r3/validation/r3-validation-utils.hpp>
#include <r3/jsoncpp/r3-jsoncpp-utils.hpp>
#include <r3/tiled/r3-tiled-JsonLoader.hpp>

namespace r3 {

	namespace tiled {

		namespace JsonCustomPropertyLoader {

			bool typeValueValid(const Json::Value& jsonValue) {
				std::string typeString = jsonValue.asString();
				
				bool result =
					(typeString.compare(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN) == 0) ||
					(typeString.compare(JsonPropertyValue::CustomPropertyTypeValue::COLOR) == 0) ||
					(typeString.compare(JsonPropertyValue::CustomPropertyTypeValue::FLOAT) == 0) ||
					(typeString.compare(JsonPropertyValue::CustomPropertyTypeValue::FILE) == 0) ||
					(typeString.compare(JsonPropertyValue::CustomPropertyTypeValue::INTEGER) == 0) ||
					(typeString.compare(JsonPropertyValue::CustomPropertyTypeValue::OBJECT) == 0) ||
					(typeString.compare(JsonPropertyValue::CustomPropertyTypeValue::STRING) == 0);

				return result;
			}

			bool customPropertyTypeValid(const Json::Value& jsonValue) {
				bool result =
					JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::TYPE) &&
					typeValueValid(jsonValue[JsonPropertyName::TYPE]);
				return result;
			}

			CustomPropertyType convertToCustomPropertyType(const Json::Value& jsonValue) {
				CustomPropertyType result = CustomPropertyType::UNKNOWN;

				std::string jsonValueStr = jsonValue.asCString();
				if (jsonValueStr.compare(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN) == 0) {
					result = CustomPropertyType::BOOLEAN;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::CustomPropertyTypeValue::COLOR) == 0) {
					result = CustomPropertyType::COLOR;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::CustomPropertyTypeValue::FLOAT) == 0) {
					result = CustomPropertyType::FLOAT;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::CustomPropertyTypeValue::FILE) == 0) {
					result = CustomPropertyType::FILE;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::CustomPropertyTypeValue::INTEGER) == 0) {
					result = CustomPropertyType::INTEGER;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::CustomPropertyTypeValue::OBJECT) == 0) {
					result = CustomPropertyType::OBJECT;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::CustomPropertyTypeValue::STRING) == 0) {
					result = CustomPropertyType::STRING;
				}

				return result;
			}

			bool customPropertyValueValid(const Json::Value& jsonValue, CustomPropertyType propertyType) {
				bool result = jsonValue.isMember(JsonPropertyName::VALUE);

				switch (propertyType) {
				case CustomPropertyType::BOOLEAN:
					result = result && jsonValue[JsonPropertyName::VALUE].isBool();
					break;
				case CustomPropertyType::COLOR:
					result = result && jsonValue[JsonPropertyName::VALUE].isString();
					if (result) {
						result = JsonTiledValidationUtils::colorValueValid(jsonValue, JsonPropertyName::VALUE);
					}
					break;
				case CustomPropertyType::FLOAT:
					result = result && jsonValue[JsonPropertyName::VALUE].isDouble();
					break;
				case CustomPropertyType::FILE:
					result = result && jsonValue[JsonPropertyName::VALUE].isString();
					break;
				case CustomPropertyType::INTEGER:
					result = result && jsonValue[JsonPropertyName::VALUE].isInt();
					break;
				case CustomPropertyType::OBJECT:
					result = result && jsonValue[JsonPropertyName::VALUE].isInt();
					if (result) {
						result = JsonValidationUtils::intInRange(jsonValue, JsonPropertyName::VALUE, r3::validation::IntRange::createMin(0));
					}
					break;
				case CustomPropertyType::STRING:
					result = result && jsonValue[JsonPropertyName::VALUE].isString();
					break;
				}

				return result;
			}

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.rootValid = jsonValue.isObject();

				if (result.rootValid) {
					result.nameValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::NAME);
					result.typeValid = customPropertyTypeValid(jsonValue);

					if (result.typeValid) {
						CustomPropertyType propertyType = convertToCustomPropertyType(jsonValue[JsonPropertyName::TYPE]);
						result.valueValid = customPropertyValueValid(jsonValue, propertyType);
					}
				}

				return result;
			}

			std::string localizePropertyListError(int index) {
				char resultStr[128];
				snprintf(resultStr, 128, "Entry %d within the \"properties\" array is invalid.  Individual error messages follow...", index);

				std::string result(resultStr);
				return result;
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				if (!validationResult.nameValid) {
					result.push_back("The \"name\" is invalid.  It must be a non-empty string.");
				}

				if (!validationResult.typeValid) {
					result.push_back("The \"type\" is invalid.  It must be one of \"bool\", \"color\", \"float\", \"file\", \"int\", \"object\", or \"string\".");
				}

				if (!validationResult.valueValid) {
					result.push_back("The \"value\" is invalid.  It must match the data type specified by the \"type\" property.");
				}

				return result;
			}

			CustomPropertyDefn convertToDefn(const Json::Value& jsonValue) {
				CustomPropertyDefn result;

				result.name = jsonValue[JsonPropertyName::NAME].asString();
				result.type = convertToCustomPropertyType(jsonValue[JsonPropertyName::TYPE]);

				switch (result.type) {
				case CustomPropertyType::BOOLEAN:
					result.boolValue = jsonValue[JsonPropertyName::VALUE].asBool();
					break;
				case CustomPropertyType::COLOR:
					result.stringValue = jsonValue[JsonPropertyName::VALUE].asString();
					break;
				case CustomPropertyType::FLOAT:
					result.decimalValue = jsonValue[JsonPropertyName::VALUE].asFloat();
					break;
				case CustomPropertyType::FILE:
					result.stringValue = jsonValue[JsonPropertyName::VALUE].asString();
					break;
				case CustomPropertyType::INTEGER:
					result.intValue = jsonValue[JsonPropertyName::VALUE].asInt();
					break;
				case CustomPropertyType::OBJECT:
					result.intValue = jsonValue[JsonPropertyName::VALUE].asInt();
					break;
				case CustomPropertyType::STRING:
					result.stringValue = jsonValue[JsonPropertyName::VALUE].asString();
					break;
				}

				return result;
			}

		}

	}

}
