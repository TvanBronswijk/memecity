#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include <ECS.h>

struct HealthComponent : public ecs::Component{

public:
	int health;

	HealthComponent(const ecs::Entity& entity) : HealthComponent(entity, 0) {};
	HealthComponent(const ecs::Entity& entity, int health) : ecs::Component(entity), health(health) {};
};

#endif