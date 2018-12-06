#ifndef _QUEST_EVENT_ARGS_H
#define _QUEST_EVENT_ARGS_H
#include <ECS.h>

struct QuestEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	const memecity::engine::ecs::Entity *target;
	const memecity::engine::ecs::Entity *item;

	QuestEventArgs(const memecity::engine::ecs::Entity* target, const memecity::engine::ecs::Entity* item) : target(target), item(item) {}
};

#endif

