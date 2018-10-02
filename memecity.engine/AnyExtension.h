#pragma once
#include <any>
#include "../dependencies/json.hpp"

class AnyExtension : std::any

{
public:
	AnyExtension();
	~AnyExtension();
	nlohmann::json to_json()
	{
		nlohmann::json j;
		return j;
	}
};

