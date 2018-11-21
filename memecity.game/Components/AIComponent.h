#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include <ECS.h>

struct AIComponent : public memecity::engine::ecs::Component {
	
	enum class State { Fighting, Fleeing, Roaming, Idle };
	State state;

	AIComponent(const memecity::engine::ecs::Entity& entity) : AIComponent(entity, AIComponent::State::Idle) {};

	AIComponent(const memecity::engine::ecs::Entity& entity, State type) : memecity::engine::ecs::Component(entity), state(type) {};
};

#endif
