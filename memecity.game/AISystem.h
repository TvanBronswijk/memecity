#pragma once
#include "../memecity.engine.ecs/System.h"
#include "PositionComponent.h"
#include "velocityComponent.h"
#include "AIComponent.h"

class AiSystem : public System {
public:
	std::string get_type() override;
	void run(EntityManager &em) override;
	void run(EntityManager &em, Event &e) override;
};
