#ifndef _SERIALIZATIONFACADE_H
#define _SERIALIZATIONFACADE_H
#include <string>
#include <map>
#include <any>
#include "../dependencies/json.hpp"

class SerializationFacade
{
public:
	std::string serialize(std::map<std::string, std::any> map) const;
	std::map<std::string, std::any> deserialize(const std::string& json_string) const;

};

#endif