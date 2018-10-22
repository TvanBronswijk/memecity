#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct AIComponent : public Component {
	
	static std::string COMPONENT_TYPE;
	enum State
	{
		FIGHTING,
		FLEEING,
		STATIC

	};

public:
	State _state;
	AIComponent(Entity* e);
	AIComponent(State state, Entity* e);
	std::string get_type() override;
};

#endif
