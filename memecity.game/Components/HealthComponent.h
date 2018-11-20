#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include <ECS.h>

struct HealthComponent : public memecity::engine::ecs::Component{

public:
	int health;

	HealthComponent(memecity::engine::ecs::Entity& entity) : HealthComponent(entity, 0) {};
	HealthComponent(memecity::engine::ecs::Entity& entity, int health) : memecity::engine::ecs::Component(entity), health(health) {};
};

#endif
