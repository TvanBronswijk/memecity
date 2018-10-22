#pragma once
#include "SerializableClass.h"
class example_guy :
	public SerializableClass
{
public:
	example_guy();
	~example_guy();
	std::string name;
	int age;
	std::map<std::string, std::any> to_map() override;
	void from_map(std::map<std::string, std::any> map) override;
private:
	int legCount;
};


