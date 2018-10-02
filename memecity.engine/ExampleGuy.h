#pragma once
#include "SerializableClass.h"
#include <iostream>
class example_guy :
	public SerializableClass
{
public:
	example_guy();
	~example_guy();
	std::map<int, std::any> to_map() override;
	void from_map(std::map<int, std::any> map) override;
};


