#ifndef _FIGHTING_COMPONENT_H
#define _FIGHTING_COMPONENT_H

#include <ECS.h>

struct FightingComponent : public memecity::engine::ecs::Component
{
	bool is_fighting = false;
	FightingComponent(memecity::engine::ecs::Entity& entity) : memecity::engine::ecs::Component(entity) {}
};

#endif
