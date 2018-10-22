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
		}else if (line.second.type().name() == typeid(std::string).name())
		{
			auto val = std::any_cast<std::string>(line.second);
			json[line.first] = val;
		}else if(line.second.type().name() == typeid(double).name())
		{
			auto val = std::any_cast<double>(line.second);
			json[line.first] = val;
		}else if (line.second.type().name() == typeid(bool).name())
		{
			auto val = std::any_cast<bool>(line.second);
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

		auto idk = line.value().is_string();

		auto b = line.value().type_name();
		auto c = line.value();
		if(line.value().is_number())
		{
			map[line.key()] = int( line.value());
		} else if (line.value().is_string())
		{
			map[line.key()] = std::string(line.value());
		}
		/*else if (line.value().is() )
		{
			map[line.key()] = float(line.value());
		}*/
		else if (line.value().is_boolean())
		{
			map[line.key()] = bool(line.value());
		}


	}
	return map;
}

