#ifndef _HEALTH_SYSTEM_H
#define _HEALTH_SYSTEM_H
#include <ECS.h>
#include "..\..\GameManager.h"
#include "..\Components.h"

class HealthSystem : public memecity::engine::ecs::System
{
private:
	GameManager::GameContext *_context;

public:
	HealthSystem(GameManager::GameContext& context)
		: _context(&context) {}
	void run(memecity::engine::ecs::EntityManager& em) const override;

	void on_death(memecity::engine::ecs::EntityManager& em);
};
#endif
