#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct AIComponent : public Component {
	
public:
	bool _fighting, _fleeing;
	AIComponent();
	AIComponent(bool fighting, bool fleeing);
	std::string get_type() override;
};

#endif
