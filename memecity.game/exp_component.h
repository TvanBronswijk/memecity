#pragma once
#include "../memecity.engine.ecs/Component.h"
#include <string>

struct exp_component: public Component
{
	static std::string COMPONENT_TYPE;

	
public:
	int exp = 0;
	int next_level = 0;
	exp_component(Entity* e);
	std::string get_type() override;
	~exp_component();
};

