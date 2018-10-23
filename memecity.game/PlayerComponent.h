#ifndef _PLAYERCOMPONENT_H
#define  _PLAYERCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct PlayerComponent : public Component
{
	static std::string COMPONENT_TYPE;

	PlayerComponent(Entity* e) : Component(e) {};
	std::string get_type() override;
};

#endif;