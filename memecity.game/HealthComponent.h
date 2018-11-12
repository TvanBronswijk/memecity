#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct HealthComponent : public ecs::Component{

	static ecs::component_typetoken COMPONENT_TYPE;

public:
	int _health;

	HealthComponent(const ecs::Entity& entity) : ecs::Component(entity) {
		_health = 1;
	};
	HealthComponent(const ecs::Entity& entity, int health) : ecs::Component(entity) {
		_health = health;
	};
	ecs::component_typetoken get_type_token() const override { return HealthComponent::COMPONENT_TYPE; }
};

#endif