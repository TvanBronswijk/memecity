#ifndef _INTERACTIONCOMPONENT_H
#define  _INTERACTIONCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include <vector>

struct InteractionComponent : public Component {

	static std::string COMPONENT_TYPE;

public:
	std::vector<std::string> _smallTalk;
	InteractionComponent(std::vector<std::string> smallTalk, Entity* e);
	InteractionComponent(Entity* e);
	std::string get_type() override;
};

#endif