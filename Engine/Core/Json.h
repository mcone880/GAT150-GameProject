#pragma once
#include "document.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <string>

namespace MAC {
	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document);
		bool Get(const rapidjson::Value& value, const std::string& name, int& data);
		bool Get(const rapidjson::Value& value, const std::string& name, float& data);
		bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool Get(const rapidjson::Value& value, const std::string& name, MAC::Vector2& data);
		bool Get(const rapidjson::Value& value, const std::string& name, MAC::Color& data);

	}
}
