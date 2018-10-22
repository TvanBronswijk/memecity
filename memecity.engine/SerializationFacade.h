#ifndef _SERIALIZATIONFACADE_H
#define _SERIALIZATIONFACADE_H
#include <string>
#include <map>
#include <any>
#include "../dependencies/json.hpp"

class SerializationFacade
{
public:
	std::string serialize(std::map<std::string, std::any> map);
	std::map<std::string, std::any> deserialize(std::string json_string);

};

#endif