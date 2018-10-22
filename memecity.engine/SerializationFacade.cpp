#include "SerializationFacade.h"


std::string SerializationFacade::serialize(std::map<std::string, std::any> map)
{
	nlohmann::json json;

	for (auto line : map)
	{

		if (line.second.type().name() == typeid(int).name())
		{
			auto val = std::any_cast<int>(line.second);
			json[line.first] = val;
		}
	}
	return json.dump();
}

std::map<std::string, std::any> SerializationFacade::deserialize(std::string json_string)
{
	std::map<std::string, std::any> map;
	auto json = nlohmann::json::parse(json_string);

	
	for (auto line : json.items())
	{
		auto b = line.value().type_name();
		if(line.value().type_name() == "number")
		{
			map[line.key()] = 0 + line.value();
		}


	}
	return map;
}

