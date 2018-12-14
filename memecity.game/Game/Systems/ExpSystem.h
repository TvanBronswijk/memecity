#ifndef _EXP_SYSTEM_H
#define _EXP_SYSTEM_H
#include <ECS.h>
#include "..\Components.h"

class ExpSystem: public memecity::engine::ecs::System
{
public:
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
	void on_exp_gain(memecity::engine::ecs::EntityManager& em, int exp) const;
};
#endif
