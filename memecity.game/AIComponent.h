#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include <ECS.h>

struct AIComponent : public ecs::Component {
	
public:
	enum class State { Fighting, Fleeing, Roaming };
	State state;

	AIComponent(const ecs::Entity& entity) : AIComponent(entity, AIComponent::State::Fightings) {};

	AIComponent(const ecs::Entity& entity, State type) : ecs::Component(entity), state(type) {};
};

#endif
