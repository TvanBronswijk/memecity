#ifndef _LEVELCOMPONENT_H
#define  _LEVELCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "Serializable.h"
#include <iostream>
#include <map>

struct LevelComponent : public ecs::Component, public Serializable {

	static ecs::component_typetoken COMPONENT_TYPE;

public:
	int _level;
	LevelComponent(const ecs::Entity& entity) : ecs::Component(entity) {
		this->_level = 1;
	};
	LevelComponent(const ecs::Entity& entity, int level) : ecs::Component(entity) {
		this->_level = level;
	};
	LevelComponent(const ecs::Entity& entity, int world, int range) : ecs::Component(entity) {
		_level = (rand() % (world - (range / 2))/*min*/ + (world + (range / 2)))/*max*/;
	};
	ecs::component_typetoken get_type_token() const override { return LevelComponent::COMPONENT_TYPE; }
	std::map<std::string, std::any> to_map() override;
	void from_map(std::map<std::string, std::any> map) override;
};

#endif

