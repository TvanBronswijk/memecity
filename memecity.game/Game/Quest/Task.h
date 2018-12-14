#ifndef _TASK_H
#define  _TASK_H
#include <ECS.h>
#include <vector>
#include <string>
#include "../Enum/QuestStates.h"

struct Task
{
	bool completed = false;
	std::string description;

	Quest_State state;

	const memecity::engine::ecs::Entity* target;
	std::vector<std::string> dialog;

	const memecity::engine::ecs::Entity* item;

	int counter = 0;
	int amount;

	Task(std::string description, Quest_State state, std::vector<std::string> dialog, const memecity::engine::ecs::Entity* target, const memecity::engine::ecs::Entity* item, int amount) :
		description(description), state(state), dialog(dialog) , target(target), item(item), amount(amount) {};
};

#endif;
