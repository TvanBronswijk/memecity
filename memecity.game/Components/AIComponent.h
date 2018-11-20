#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include <ECS.h>

struct AIComponent : public memecity::engine::ecs::Component {
	
public:
	enum class State { Fighting, Fleeing, Roaming };
	State state;

	AIComponent(memecity::engine::ecs::Entity& entity) : AIComponent(entity, AIComponent::State::Fighting) {};

	AIComponent(memecity::engine::ecs::Entity& entity, State type) : memecity::engine::ecs::Component(entity), state(type) {};
};

#endif
