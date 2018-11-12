#ifndef _EXP_COMPONENT_H
#define _EXP_COMPONENT_H
#include <ECS.h>

struct ExpComponent : public ecs::Component
{
	int exp, next_level;
	ExpComponent(const ecs::Entity& entity)
		: ExpComponent(entity, 0, 0) {};
	ExpComponent(const ecs::Entity& entity, int exp, int next_level) 
		: ecs::Component(entity), exp(exp), next_level(next_level) {};
};

#endif
