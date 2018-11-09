#ifndef _EXP_COMPONENT_H
#define _EXP_COMPONENT_H
#include <ECS.h>

struct ExpComponent: public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	int exp, next_level;
	ExpComponent(const ecs::Entity& entity) : ecs::Component(entity) {};
	ecs::component_typetoken get_type_token() const override { return ExpComponent::COMPONENT_TYPE; }
};

#endif
