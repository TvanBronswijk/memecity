#include "ExampleGuy.h"
#include <string>
#include "../dependencies/json.hpp"
#include <iostream>


example_guy::example_guy()
= default;


example_guy::~example_guy()
= default;

std::map<std::string, AnyExtension> example_guy::to_map()
{
	std::map<std::string, AnyExtension> map;

	map["name"] = this->name;
	map["age"] = this->age;
	map["legCount"] = this->legCount;

	nlohmann::json j = nlohmann::json(map);

	std::cout << j.dump() << std::endl;

	return map;
}

void example_guy::from_map(std::map<std::string, AnyExtension> map)
{
	this->name = std::any_cast<std::string>(map["name"]);
	this->age = std::any_cast<int>(map["age"]);
	this->legCount = std::any_cast<int>(map["legCount"]);
}

