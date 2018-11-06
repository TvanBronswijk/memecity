#ifndef _EXP_SYSTEM_H
#define _EXP_SYSTEM_H
#include "../memecity.engine.ecs/ECS.h"
#include "ExpComponent.h"
#include "StatsComponent.h"


class ExpSystem: public ecs::System
{
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	ExpSystem();
	void run(ecs::EntityManager& em) override;
	void on_exp_gain(ecs::EntityManager& em, int exp);
	ecs::system_typetoken get_type_token() override { return ExpSystem::SYSTEM_TYPE; }
};

#endif