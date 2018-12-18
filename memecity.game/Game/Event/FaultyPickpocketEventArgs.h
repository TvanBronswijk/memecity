#ifndef FAULTY_PICKPOCKET_EVENT_ARGS_H
#define FAULTY_PICKPOCKET_EVENT_ARGS_H
#include <ECS.h>

struct FaultyPickpocketEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{

	const memecity::engine::ecs::Entity &ai;
	std::string text;

	FaultyPickpocketEventArgs(const memecity::engine::ecs::Entity& ai, std::string text) : ai(ai), text(text) {}

};
#endif
