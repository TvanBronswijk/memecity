#pragma once
#include "../memecity.engine.ecs/System.h"
#include "PositionComponent.h"
#include "velocityComponent.h"
#include "AIComponent.h"
#include "../memecity.engine.ecs/EntityManager.h"

class AISystem : public System {
public:
	AISystem();
	std::string get_type() override;
	void run(EntityManager &em) override;
	void run(EntityManager &em, Event *e) override;
};
