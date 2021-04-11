
#include <assert.h>
#include <iostream>
#include <json/json.h>
#include <r3/tiled/r3-tiled-JsonLoader.hpp>

using namespace r3::tiled;

Json::Value createValidMapTilesetJsonValue() {
	Json::Value result;
	result[JsonPropertyName::Map::FIRST_GID] = 1;
	result[JsonPropertyName::Map::SOURCE_PATH] = "tilesets/floors.json";
	return result;
}

bool testValidate_Valid() {
	Json::Value jsonValue = createValidMapTilesetJsonValue();

	JsonMapTilesetLoader::ValidationResult validationResult = JsonMapTilesetLoader::validate(jsonValue);

	bool result = validationResult.isValid();
	return result;
}

bool testValidate_InvalidRoot() {
	Json::Value jsonValue = "should be an object";

	JsonMapTilesetLoader::ValidationResult validationResult = JsonMapTilesetLoader::validate(jsonValue);

	bool result =
		!validationResult.rootValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_MissingFirstGid() {
	Json::Value jsonValue = createValidMapTilesetJsonValue();
	jsonValue.removeMember(JsonPropertyName::Map::FIRST_GID);

	JsonMapTilesetLoader::ValidationResult validationResult = JsonMapTilesetLoader::validate(jsonValue);

	bool result =
		!validationResult.firstGidValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_FirstGid(const Json::Value& firstGidValue, bool expectedFirstGidValid) {
	Json::Value jsonValue = createValidMapTilesetJsonValue();
	jsonValue[JsonPropertyName::Map::FIRST_GID] = firstGidValue;

	JsonMapTilesetLoader::ValidationResult validationResult = JsonMapTilesetLoader::validate(jsonValue);

	bool result = (validationResult.firstGidValid == expectedFirstGidValid);
	return result;
}

bool testValidate_MissingSourcePath() {
	Json::Value jsonValue = createValidMapTilesetJsonValue();
	jsonValue.removeMember(JsonPropertyName::Map::SOURCE_PATH);

	JsonMapTilesetLoader::ValidationResult validationResult = JsonMapTilesetLoader::validate(jsonValue);

	bool result =
		!validationResult.sourcePathValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_SourcePath(const Json::Value& sourcePathValue, bool expectedSourcePathValid) {
	Json::Value jsonValue = createValidMapTilesetJsonValue();
	jsonValue[JsonPropertyName::Map::SOURCE_PATH] = sourcePathValue;

	JsonMapTilesetLoader::ValidationResult validationResult = JsonMapTilesetLoader::validate(jsonValue);

	bool result = (validationResult.sourcePathValid == expectedSourcePathValid);
	return result;
}

bool testLocalizeTilesetListError() {
	std::string error = JsonMapTilesetLoader::localizeTilesetListError(4);

	bool result = (error.find("Entry 4 within the \"tilesets\"") != std::string::npos);
	return result;
}

bool testLocalizeValidationResult_Valid() {
	JsonMapTilesetLoader::ValidationResult validationResult;

	std::vector<std::string> errorList = JsonMapTilesetLoader::localizeValidationResult(validationResult);

	bool result = (errorList.empty());
	return result;
}

bool testLocalizeValidationResult_FirstGidInvalid() {
	JsonMapTilesetLoader::ValidationResult validationResult;
	validationResult.firstGidValid = false;

	std::vector<std::string> errorList = JsonMapTilesetLoader::localizeValidationResult(validationResult);

	bool result =
		(errorList.size() == 1) &&
		(errorList.at(0).find("The \"firstgid\" is invalid") != std::string::npos);
	return result;
}

bool testLocalizeValidationResult_SourcePathInvalid() {
	JsonMapTilesetLoader::ValidationResult validationResult;
	validationResult.sourcePathValid = false;

	std::vector<std::string> errorList = JsonMapTilesetLoader::localizeValidationResult(validationResult);

	bool result =
		(errorList.size() == 1) &&
		(errorList.at(0).find("The \"source\"") != std::string::npos);
	return result;
}

bool testConvertToDefn() {
	Json::Value jsonValue = createValidMapTilesetJsonValue();

	MapTilesetDefn defn = JsonMapTilesetLoader::convertToDefn(jsonValue);

	bool result =
		(defn.firstGid == 1) &&
		(defn.sourcePath.compare("tilesets/floors.json") == 0);
	return result;
}

int main() {
	assert(testValidate_Valid());

	assert(testValidate_InvalidRoot());

	assert(testValidate_MissingFirstGid());
	assert(testValidate_FirstGid(1, true));
	assert(testValidate_FirstGid(0, false));
	assert(testValidate_FirstGid("nope", false));

	assert(testValidate_MissingSourcePath());
	assert(testValidate_SourcePath("tileset.json", true));
	assert(testValidate_SourcePath(1, false));

	assert(testLocalizeTilesetListError());

	assert(testLocalizeValidationResult_Valid());
	assert(testLocalizeValidationResult_FirstGidInvalid());
	assert(testLocalizeValidationResult_SourcePathInvalid());

	assert(testConvertToDefn());

	std::cout << "All tests passed!\n";
	return 0;
}
