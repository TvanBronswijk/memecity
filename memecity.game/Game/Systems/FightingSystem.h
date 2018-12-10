#ifndef _FIGHTINGSYSTEM_H
#define  _FIGHTINGSYSTEM_H
#include <Engine\MultimediaManager.h>
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\AttackEventArgs.h"
#include "../Event/HealthChangedEventArgs.h"

class FightingSystem : public memecity::engine::ecs::System {

public:
	memecity::engine::MultimediaManager& multimedia_manager;
	memecity::engine::ecs::eventing::Event<HealthChangedEventArgs> health_changed_event;

	FightingSystem(memecity::engine::MultimediaManager& multimedia_manager)
		: multimedia_manager(multimedia_manager) {}

	void on_attack(memecity::engine::ecs::EntityManager& em, AttackEventArgs args);
	void run(memecity::engine::ecs::EntityManager& em) const override;
};

#endif