#pragma once
#include "../memecity.engine.ecs/Component.h"

struct exp_component: public Component
{
private:
	int exp = 0;
	int next_level = 0;
public:
	exp_component(Entity* e);
	~exp_component();
};

