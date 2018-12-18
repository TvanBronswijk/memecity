#ifndef _HEALTHSYSTEM_H
#define  _HEALTHSYSTEM_H
#include <ECS.h>
#include "..\..\GameManager.h"
#include "..\Components.h"

class HealthSystem : public memecity::engine::ecs::System
{
public:
	GameManager::GameContext *_context;
	
	HealthSystem(GameManager::GameContext& context)
		: _context(&context) {}
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
	void on_damage(memecity::engine::ecs::EntityManager& em, std::reference_wrapper<const memecity::engine::ecs::Entity> entity);
	void on_death(memecity::engine::ecs::EntityManager& em, memecity::engine::ecs::eventing::EventArgs args);
};

#endif
