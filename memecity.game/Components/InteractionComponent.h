#ifndef _INTERACTIONCOMPONENT_H
#define  _INTERACTIONCOMPONENT_H
#include <ECS.h>
#include <vector>

struct InteractionComponent : public memecity::engine::ecs::Component{


public:
	std::vector<std::string> smallTalk; // markovketen

	InteractionComponent(memecity::engine::ecs::Entity& entity) : InteractionComponent(entity, { "Hello Stranger!", "Sorry, i can't talk.", "what are you doing?" }) {};
	InteractionComponent(memecity::engine::ecs::Entity& entity, std::vector<std::string> smallTalk) : memecity::engine::ecs::Component(entity), smallTalk(smallTalk) {};
};

#endif
