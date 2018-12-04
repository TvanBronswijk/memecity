#ifndef _TASKCOMPONENT_H
#define  _TASKCOMPONENT_H
#include <ECS.h>
#include <iostream>

struct TaskComponent : public memecity::engine::ecs::Component
{
	std::string description;

	bool completed = false;

	const memecity::engine::ecs::Entity* target;

	int counter = 0;
	int amount;

	TaskComponent(memecity::engine::ecs::Entity& entity, std::string description, const memecity::engine::ecs::Entity& target, int amount) : memecity::engine::ecs::Component(entity), description(description), target(&target), amount(amount) {};
};

#endif;
