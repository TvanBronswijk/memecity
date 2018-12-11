#ifndef _INTERACTIONSYSTEM_H
#define  _INTERACTIONSYSTEM_H

#include "..\..\GameManager.h"
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\InteractionEventArgs.h"
#include "..\Event\QuestEventArgs.h"

class InteractionSystem : public memecity::engine::ecs::System {

public:
	GameManager::GameContext* _context;

	memecity::engine::ecs::eventing::Event<QuestEventArgs> quest_event;


	InteractionSystem(GameManager::GameContext& context)
		: _context(&context) {}

	void run(memecity::engine::ecs::EntityManager& em) const override;
	void on_interact(memecity::engine::ecs::EntityManager& em, InteractionEventArgs args);
};
#endif
