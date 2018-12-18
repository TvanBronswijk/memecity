#ifndef PICKPOCKET_EVENT_ARGS_H
#define PICKPOCKET_EVENT_ARGS_H
#include <ECS.h>

struct PickpocketEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{

	const memecity::engine::ecs::Entity &player, &ai;

	PickpocketEventArgs(const memecity::engine::ecs::Entity& player, const memecity::engine::ecs::Entity& ai) : player(player), ai(ai) {}

};
#endif
