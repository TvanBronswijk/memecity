#include "SerializationFacade.h"


std::string SerializationFacade::serialize(std::map<std::string, std::any> map) const
{
	nlohmann::json json;

	for (auto entry : map)
	{
		if (entry.second.type().name() == typeid(int).name())
		{
			auto val = std::any_cast<int>(entry.second);
			json[entry.first] = val;
		}else if (entry.second.type().name() == typeid(std::string).name())
		{
			auto val = std::any_cast<std::string>(entry.second);
			json[entry.first] = val;
		}else if(entry.second.type().name() == typeid(float).name())
		{
			auto val = std::any_cast<float>(entry.second);
			json[entry.first] = val;
		}else if (entry.second.type().name() == typeid(bool).name())
		{
			auto val = std::any_cast<bool>(entry.second);
			json[entry.first] = val;
		}
	}
	return json.dump();
}

std::map<std::string, std::any> SerializationFacade::deserialize(const std::string& json_string) const
{
	std::map<std::string, std::any> map;
	auto json = nlohmann::json::parse(json_string);

	
	for (const auto& entry : json.items())
	{
		if(entry.value().is_number())
		{
			if(entry.value().is_number_float())
			{
				map[entry.key()] = float(entry.value());
			}
			else {
				map[entry.key()] = int(entry.value());
			}
		} else if (entry.value().is_string())
		{
			map[entry.key()] = std::string(entry.value());
		}
		else if (entry.value().is_boolean())
		{
			map[entry.key()] = bool(entry.value());
		}
	}
	return map;
}

