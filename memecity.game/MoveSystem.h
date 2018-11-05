﻿#ifndef _MOVESYSTEM_H
#define  _MOVESYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"


class MoveSystem : public System
{
	static std::string SYSTEM_TYPE;
public:
	std::string get_type() const override;
	void run(EntityManager& em) override;
	void run(EntityManager& em, EventArgs& e) override;
};

#endif