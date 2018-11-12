#ifndef _EXP_COMPONENT_H
#define _EXP_COMPONENT_H
#include <ECS.h>

struct ExpComponent : public memecity::engine::ecs::Component
{
	int exp, next_level;
	ExpComponent(const memecity::engine::ecs::Entity& entity)
		: ExpComponent(entity, 0, 0) {};
	ExpComponent(const memecity::engine::ecs::Entity& entity, int exp, int next_level) 
		: memecity::engine::ecs::Component(entity), exp(exp), next_level(next_level) {};
};

#endif
