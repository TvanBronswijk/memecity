#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include <ECS.h>

struct HealthComponent : public ecs::Component{

public:
	int _health;

	HealthComponent(const ecs::Entity& entity) : HealthComponent(entity, 1) {};
	HealthComponent(const ecs::Entity& entity, int health) : ecs::Component(entity), _health(health) {};
};

#endif