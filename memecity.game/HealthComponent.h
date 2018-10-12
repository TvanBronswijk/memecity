#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct HealthComponent : public Component {

public:
	int _health;
	HealthComponent(Entity* e);
	HealthComponent(int health, Entity* e);
	std::string get_type() override;
};

#endif