#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct AIComponent : public Component {
	
	static std::string COMPONENT_TYPE;

public:
	bool _fighting, _fleeing;
	AIComponent(Entity* e);
	AIComponent(bool fighting, bool fleeing, Entity* e);
	std::string get_type() override;
};

#endif
