
#include <assert.h>
#include <iostream>
#include <json/json.h>
#include <r3/tiled/r3-tiled-JsonLoader.hpp>

using namespace r3::tiled;

Json::Value createValidCustomPropertyJsonValue() {
	Json::Value result;
	result[JsonPropertyName::NAME] = "someProperty";
	result[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
	result[JsonPropertyName::VALUE] = "a value";
	return result;
}

Json::Value createValidTilesetTileJsonValue() {
	Json::Value result;
	result[JsonPropertyName::ID] = 5;
	result[JsonPropertyName::Tileset::IMAGE_PATH] = "../path/tileset.png";
	result[JsonPropertyName::Tileset::IMAGE_WIDTH] = 256;
	result[JsonPropertyName::Tileset::IMAGE_HEIGHT] = 128;
	return result;
}

bool testValidate_Valid_NoPropertyList() {
	Json::Value jsonValue = createValidTilesetTileJsonValue();

	JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

	bool result = validationResult.isValid();
	return result;
}

bool testValidate_Valid_WithPropertyList() {
	Json::Value propertyListJsonValue;
	propertyListJsonValue[0] = createValidCustomPropertyJsonValue();

	Json::Value jsonValue = createValidTilesetTileJsonValue();
	jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

	JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

	bool result = validationResult.isValid();
	return result;
}

bool testValidate_InvalidRoot() {
	Json::Value jsonValue = "should be an object";

	JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

	bool result =
		!validationResult.rootValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_MissingId() {
	Json::Value jsonValue = createValidTilesetTileJsonValue();
	jsonValue.removeMember(JsonPropertyName::ID);

	JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

	bool result =
		!validationResult.idValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_InvalidId() {
	Json::Value jsonValue = createValidTilesetTileJsonValue();
	jsonValue[JsonPropertyName::ID] = "no strings allowed";

	JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

	bool result =
		!validationResult.idValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_InvalidImage() {
	Json::Value jsonValue = createValidTilesetTileJsonValue();
	jsonValue.removeMember(JsonPropertyName::Tileset::IMAGE_PATH);

	JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

	bool result =
		!validationResult.imageValidationResult.isValid() &&
		!validationResult.isValid();
	return result;
}

bool testValidate_InvalidPropertyList() {
	Json::Value propertyJsonValue = createValidCustomPropertyJsonValue();
	propertyJsonValue.removeMember(JsonPropertyName::NAME);

	Json::Value propertyListJsonValue;
	propertyListJsonValue[0] = propertyJsonValue;

	Json::Value jsonValue = createValidTilesetTileJsonValue();
	jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

	JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

	bool result =
		!validationResult.propertyValidationResultList.at(0).isValid() &&
		!validationResult.isValid();
	return result;
}

bool testLocalizeValidationResult_Valid() {
	JsonTilesetTileLoader::ValidationResult validationResult;

	std::vector<std::string> errorList = JsonTilesetTileLoader::localizeValidationResult(validationResult);

	bool result = errorList.empty();
	return result;
}

bool testLocalizeValidationResult_IdInvalid() {
	JsonTilesetTileLoader::ValidationResult validationResult;
	validationResult.idValid = false;

	std::vector<std::string> errorList = JsonTilesetTileLoader::localizeValidationResult(validationResult);

	bool result =
		(errorList.size() == 1) &&
		(errorList.at(0).find("The \"id\" is invalid") != std::string::npos);
	return result;
}

bool testLocalizeValidationResult_ImageInvalid() {
	JsonTilesetTileLoader::ValidationResult validationResult;
	validationResult.imageValidationResult.imageHeightValid = false;

	std::vector<std::string> errorList = JsonTilesetTileLoader::localizeValidationResult(validationResult);

	bool result =
		(errorList.size() == 1) &&
		(errorList.at(0).find("The \"imageheight\" is invalid") != std::string::npos);
	return result;
}

bool testLocalizeValidationResult_PropertyInvalid() {
	JsonCustomPropertyLoader::ValidationResult propertyValidationResult;
	propertyValidationResult.valueValid = false;

	JsonTilesetTileLoader::ValidationResult validationResult;
	validationResult.propertyValidationResultList.push_back(propertyValidationResult);

	std::vector<std::string> errorList = JsonTilesetTileLoader::localizeValidationResult(validationResult);

	bool result =
		(errorList.size() == 2) &&
		(errorList.at(0).find("Entry 1 within the \"properties\" array is invalid") != std::string::npos) &&
		(errorList.at(1).find("The \"value\" is invalid") != std::string::npos);
	return result;
}

bool testConvertToDefn_EmptyPropertyList() {
	Json::Value jsonValue = createValidTilesetTileJsonValue();

	TilesetTileDefn defn = JsonTilesetTileLoader::convertToDefn(jsonValue);

	bool result =
		(defn.id == 5) &&
		(defn.imageDefn.imagePath.compare("../path/tileset.png") == 0) &&
		(defn.imageDefn.imageWidth == 256) &&
		(defn.imageDefn.imageHeight == 128) &&
		(defn.propertyDefnList.empty());
	return result;
}

bool testConvertToDefn_WithPropertyList() {
	Json::Value propertyListJsonValue;
	propertyListJsonValue[0] = createValidCustomPropertyJsonValue();

	Json::Value jsonValue = createValidTilesetTileJsonValue();
	jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

	TilesetTileDefn defn = JsonTilesetTileLoader::convertToDefn(jsonValue);

	bool result =
		(defn.id == 5) &&
		(defn.imageDefn.imagePath.compare("../path/tileset.png") == 0) &&
		(defn.imageDefn.imageWidth == 256) &&
		(defn.imageDefn.imageHeight == 128) &&
		(defn.propertyDefnList.at(0).name.compare("someProperty") == 0);
	return result;
}

int main() {
	assert(testValidate_Valid_NoPropertyList());
	assert(testValidate_Valid_WithPropertyList());

	assert(testValidate_InvalidRoot());

	assert(testValidate_MissingId());
	assert(testValidate_InvalidId());

	assert(testValidate_InvalidImage());

	assert(testValidate_InvalidPropertyList());

	assert(testLocalizeValidationResult_Valid());
	assert(testLocalizeValidationResult_IdInvalid());
	assert(testLocalizeValidationResult_ImageInvalid());
	assert(testLocalizeValidationResult_PropertyInvalid());

	assert(testConvertToDefn_EmptyPropertyList());
	assert(testConvertToDefn_WithPropertyList());

	std::cout << "All tests passed!\n";
	return 0;
}
