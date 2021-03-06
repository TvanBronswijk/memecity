#ifndef _FIGHTINGSYSTEM_H
#define  _FIGHTINGSYSTEM_H
#include <Engine\MultimediaManager.h>
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\AttackEventArgs.h"
#include "..\Event\QuestEventArgs.h"
#include "..\Event\ExpEventArgs.h"
#include "../Event/HealthChangedEventArgs.h"
#include "../Event/DeathEventArgs.h"

class FightingSystem : public memecity::engine::ecs::System {

public:
	memecity::engine::MultimediaManager& multimedia_manager;

	memecity::engine::ecs::eventing::Event<std::reference_wrapper<const memecity::engine::ecs::Entity>> damage_event;
	memecity::engine::ecs::eventing::Event<QuestEventArgs> quest_event;
	memecity::engine::ecs::eventing::Event<HealthChangedEventArgs> health_changed_event;
	memecity::engine::ecs::eventing::Event<DeathEventArgs> death_event;
	memecity::engine::ecs::eventing::Event<ExpEventArgs> exp_event;

	FightingSystem(memecity::engine::MultimediaManager& multimedia_manager)
		: multimedia_manager(multimedia_manager) {}

	void on_attack(memecity::engine::ecs::EntityManager& em, AttackEventArgs args);
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
};

#endif