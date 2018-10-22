#ifndef _INPUTCOMPONENT_H
#define  _INPUTCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct InputComponent : public Component
{
	static std::string COMPONENT_TYPE;

	InputComponent(Entity* e);
	std::string get_type() override;
};

#endif;