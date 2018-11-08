#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct AIComponent : public ecs::Component {
	

	static ecs::component_typetoken COMPONENT_TYPE;
	enum State
	{
		Fighting,
		Fleeing,
		Static

	};

public:
	State _state;
	AIComponent(const ecs::Entity& entity) : ecs::Component(entity) {
			this->_state = Static;
	};
	ecs::component_typetoken get_type_token() const override { return AIComponent::COMPONENT_TYPE; }
};

#endif
