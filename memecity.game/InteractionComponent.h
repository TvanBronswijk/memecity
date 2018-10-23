#ifndef _INTERACTIONCOMPONENT_H
#define  _INTERACTIONCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "Serializable.h"
#include <vector>
#include <iostream>
#include <map>

struct InteractionComponent : public Component, public Serializable {

	static std::string COMPONENT_TYPE;

public:
	std::vector<std::string> _smallTalk;
	InteractionComponent(std::vector<std::string> smallTalk, Entity* e);
	InteractionComponent(Entity* e);
	std::string get_type() override;
	std::map<std::string, std::any> to_map() override;
	void from_map(std::map<std::string, std::any> map) override;
};

#endif