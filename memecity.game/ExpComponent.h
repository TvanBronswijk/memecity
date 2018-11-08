#ifndef _EXP_COMPONENT_H
#define _EXP_COMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct ExpComponent: public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	int exp, next_level;
	ExpComponent(const ecs::Entity& e) : ecs::Component(e) {};
	ecs::component_typetoken get_type_token() const override { return ExpComponent::COMPONENT_TYPE; }
};

#endif
