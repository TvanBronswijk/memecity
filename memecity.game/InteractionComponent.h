#ifndef _INTERACTIONCOMPONENT_H
#define  _INTERACTIONCOMPONENT_H
#include <ECS.h>
#include <vector>

struct InteractionComponent : public ecs::Component{


public:
	std::vector<std::string> _smallTalk;

	InteractionComponent(const ecs::Entity& entity) : InteractionComponent(entity, { "Hello Stranger!", "Sorry, i can't talk.", "what are you doing?" }) {};
	InteractionComponent(const ecs::Entity& entity, std::vector<std::string> smallTalk) : ecs::Component(entity), _smallTalk(smallTalk) {};
};

#endif