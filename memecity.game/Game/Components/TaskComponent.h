#ifndef _TASKCOMPONENT_H
#define  _TASKCOMPONENT_H
#include <ECS.h>
#include <iostream>
#include <vector>

struct TaskComponent : public memecity::engine::ecs::Component
{
	std::string description;

	std::vector<std::string> dialog;

	bool completed = false;

	const memecity::engine::ecs::Entity* target;

	int counter = 0;
	int amount;

	TaskComponent(memecity::engine::ecs::Entity& entity, std::string description, std::vector<std::string> dialog , const memecity::engine::ecs::Entity& target, int amount) : memecity::engine::ecs::Component(entity), description(description), dialog(dialog) , target(&target), amount(amount) {};
};

#endif;
