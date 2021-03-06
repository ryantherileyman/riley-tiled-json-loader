
#include <assert.h>
#include <iostream>
#include <json/json.h>
#include <r3/tiled/r3-tiled-defn.hpp>
#include <r3/tiled/r3-tiled-JsonLoader.hpp>

using namespace r3::tiled;

Json::Value createValidJsonValue() {
	Json::Value result;
	result[JsonPropertyName::NAME] = "someProperty";
	result[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
	result[JsonPropertyName::VALUE] = "testStringValue";
	return result;
}

bool testValidate_Valid() {
	Json::Value jsonValue = createValidJsonValue();

	JsonCustomPropertyLoader::ValidationResult validationResult = JsonCustomPropertyLoader::validate(jsonValue);

	bool result = validationResult.isValid();
	return result;
}

bool testValidate_InvalidRoot() {
	Json::Value jsonValue = "must be an object";

	JsonCustomPropertyLoader::ValidationResult validationResult = JsonCustomPropertyLoader::validate(jsonValue);

	bool result =
		!validationResult.rootValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_MissingName() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue.removeMember(JsonPropertyName::NAME);

	JsonCustomPropertyLoader::ValidationResult validationResult = JsonCustomPropertyLoader::validate(jsonValue);

	bool result =
		!validationResult.nameValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_InvalidName() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::NAME] = 3;

	JsonCustomPropertyLoader::ValidationResult validationResult = JsonCustomPropertyLoader::validate(jsonValue);

	bool result =
		!validationResult.nameValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_MissingType() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue.removeMember(JsonPropertyName::TYPE);

	JsonCustomPropertyLoader::ValidationResult validationResult = JsonCustomPropertyLoader::validate(jsonValue);

	bool result =
		!validationResult.typeValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_Type(const Json::Value& typeValue, bool expectedTypeValid) {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = typeValue;

	JsonCustomPropertyLoader::ValidationResult validationResult = JsonCustomPropertyLoader::validate(jsonValue);

	bool result = (validationResult.typeValid == expectedTypeValid);
	return result;
}

bool testValidate_MissingValue() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue.removeMember(JsonPropertyName::VALUE);

	JsonCustomPropertyLoader::ValidationResult validationResult = JsonCustomPropertyLoader::validate(jsonValue);

	bool result =
		!validationResult.valueValid &&
		!validationResult.isValid();
	return result;
}

bool testValidate_Value(const Json::Value& typeValue, const Json::Value& value, bool expectedValueValid) {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = typeValue;
	jsonValue[JsonPropertyName::VALUE] = value;

	JsonCustomPropertyLoader::ValidationResult validationResult = JsonCustomPropertyLoader::validate(jsonValue);

	bool result = (validationResult.valueValid == expectedValueValid);
	return result;
}

bool testLocalizeValidationResult_Valid() {
	JsonCustomPropertyLoader::ValidationResult validationResult;

	std::vector<std::string> errorList = JsonCustomPropertyLoader::localizeValidationResult(validationResult);

	bool result = errorList.empty();
	return result;
}

bool testLocalizeValidationResult_NameInvalid() {
	JsonCustomPropertyLoader::ValidationResult validationResult;
	validationResult.nameValid = false;

	std::vector<std::string> errorList = JsonCustomPropertyLoader::localizeValidationResult(validationResult);

	bool result =
		(errorList.size() == 1) &&
		(errorList.at(0).find("The \"name\" is invalid") != std::string::npos);
	return result;
}

bool testLocalizeValidationResult_TypeInvalid() {
	JsonCustomPropertyLoader::ValidationResult validationResult;
	validationResult.typeValid = false;

	std::vector<std::string> errorList = JsonCustomPropertyLoader::localizeValidationResult(validationResult);

	bool result =
		(errorList.size() == 1) &&
		(errorList.at(0).find("The \"type\" is invalid") != std::string::npos);
	return result;
}

bool testLocalizeValidationResult_ValueInvalid() {
	JsonCustomPropertyLoader::ValidationResult validationResult;
	validationResult.valueValid = false;

	std::vector<std::string> errorList = JsonCustomPropertyLoader::localizeValidationResult(validationResult);

	bool result =
		(errorList.size() == 1) &&
		(errorList.at(0).find("The \"value\" is invalid") != std::string::npos);
	return result;
}

bool testConvertToDefn_Boolean() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN;
	jsonValue[JsonPropertyName::VALUE] = true;

	CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToDefn(jsonValue);

	bool result =
		(defn.name.compare("someProperty") == 0) &&
		(defn.type == CustomPropertyType::BOOLEAN) &&
		(defn.boolValue);
	return result;
}

bool testConvertToDefn_Color() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::COLOR;
	jsonValue[JsonPropertyName::VALUE] = "#ffc06060";

	CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToDefn(jsonValue);

	bool result =
		(defn.name.compare("someProperty") == 0) &&
		(defn.type == CustomPropertyType::COLOR) &&
		(defn.stringValue.compare("#ffc06060") == 0);
	return result;
}

bool testConvertToDefn_Float() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::FLOAT;
	jsonValue[JsonPropertyName::VALUE] = 3.6;

	CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToDefn(jsonValue);

	bool result =
		(defn.name.compare("someProperty") == 0) &&
		(defn.type == CustomPropertyType::FLOAT) &&
		(defn.decimalValue == jsonValue[JsonPropertyName::VALUE].asFloat());
	return result;
}

bool testConvertToDefn_File() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::FILE;
	jsonValue[JsonPropertyName::VALUE] = "../path/image.png";

	CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToDefn(jsonValue);

	bool result =
		(defn.name.compare("someProperty") == 0) &&
		(defn.type == CustomPropertyType::FILE) &&
		(defn.stringValue.compare("../path/image.png") == 0);
	return result;
}

bool testConvertToDefn_Integer() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::INTEGER;
	jsonValue[JsonPropertyName::VALUE] = 3;

	CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToDefn(jsonValue);

	bool result =
		(defn.name.compare("someProperty") == 0) &&
		(defn.type == CustomPropertyType::INTEGER) &&
		(defn.intValue == 3);
	return result;
}

bool testConvertToDefn_Object() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::OBJECT;
	jsonValue[JsonPropertyName::VALUE] = 3;

	CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToDefn(jsonValue);

	bool result =
		(defn.name.compare("someProperty") == 0) &&
		(defn.type == CustomPropertyType::OBJECT) &&
		(defn.intValue == 3);
	return result;
}

bool testConvertToDefn_String() {
	Json::Value jsonValue = createValidJsonValue();
	jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
	jsonValue[JsonPropertyName::VALUE] = "some value";

	CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToDefn(jsonValue);

	bool result =
		(defn.name.compare("someProperty") == 0) &&
		(defn.type == CustomPropertyType::STRING) &&
		(defn.stringValue.compare("some value") == 0);
	return result;
}

int main() {
	assert(testValidate_Valid());

	assert(testValidate_InvalidRoot());

	assert(testValidate_MissingName());
	assert(testValidate_InvalidName());

	assert(testValidate_MissingType());
	assert(testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, true));
	assert(testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::COLOR, true));
	assert(testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, true));
	assert(testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::FILE, true));
	assert(testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, true));
	assert(testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, true));
	assert(testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::STRING, true));
	assert(testValidate_Type("unknowntype", false));
	assert(testValidate_Type(3, false));

	assert(testValidate_MissingValue());
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, true, true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, "mismatch type", false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "#ffcc9966", true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "#ffcc99", true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "#ffcc9", false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "#ffcc996", false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "this ain't no color", false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, 0xffcc9966, false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, 1.5, true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, 1, true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, "mismatch type", false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FILE, "../path.file.png", true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FILE, 5, false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, 1, true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, "mismatch type", false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, 1, true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, -1, false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, "mismatch type", false));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::STRING, "anything", true));
	assert(testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::STRING, 3, false));

	assert(testLocalizeValidationResult_Valid());
	assert(testLocalizeValidationResult_NameInvalid());
	assert(testLocalizeValidationResult_TypeInvalid());
	assert(testLocalizeValidationResult_ValueInvalid());

	assert(testConvertToDefn_Boolean());
	assert(testConvertToDefn_Color());
	assert(testConvertToDefn_Float());
	assert(testConvertToDefn_File());
	assert(testConvertToDefn_Integer());
	assert(testConvertToDefn_Object());
	assert(testConvertToDefn_String());

	std::cout << "All tests passed!\n";
	return 0;
}
