#ifndef _INTERACTIONCOMPONENT_H
#define  _INTERACTIONCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "Serializable.h"
#include <vector>
#include <iostream>
#include <map>

struct InteractionComponent : public ecs::Component, public Serializable {

	static ecs::component_typetoken COMPONENT_TYPE;

public:
	std::vector<std::string> _smallTalk; //maybe private?
	InteractionComponent(const ecs::Entity& entity) : ecs::Component(entity) {
		_smallTalk = { "Hello Stranger!", "Sorry, i can't talk.", "what are you doing?" };
	};
	InteractionComponent(const ecs::Entity& entity, std::vector<std::string> smallTalk) : ecs::Component(entity) {
		_smallTalk = smallTalk;
	};
	ecs::component_typetoken get_type_token() const override { return InteractionComponent::COMPONENT_TYPE; }
	std::map<std::string, std::any> to_map() override;
	void from_map(std::map<std::string, std::any> map) override;
};

#endif