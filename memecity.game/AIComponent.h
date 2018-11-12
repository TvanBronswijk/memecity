#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include <ECS.h>

struct AIComponent : public ecs::Component {
	
public:
	enum State { Fighting, Fleeing, Static };
	State _state;

	AIComponent(const ecs::Entity& entity) : AIComponent(entity, Fighting) {};

	AIComponent(const ecs::Entity& entity, State type) : ecs::Component(entity), _state(type) {};
};

#endif
