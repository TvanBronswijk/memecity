#ifndef _TASKCOMPONENT_H
#define  _TASKCOMPONENT_H
#include "../Enum/QuestStates.h"
#include <ECS.h>
#include <iostream>
#include <vector>

struct TaskComponent : public memecity::engine::ecs::Component
{
	bool completed = false;
	std::string description;

	Quest_State state;

	const memecity::engine::ecs::Entity* target;
	std::vector<std::string> dialog;

	const memecity::engine::ecs::Entity* item;

	int counter = 0;
	int amount;

	TaskComponent(memecity::engine::ecs::Entity& entity, std::string description, Quest_State state, std::vector<std::string> dialog, const memecity::engine::ecs::Entity* target, const memecity::engine::ecs::Entity* item, int amount) :
		memecity::engine::ecs::Component(entity), description(description), state(state), dialog(dialog) , target(target), item(item), amount(amount) {};
};

#endif;
