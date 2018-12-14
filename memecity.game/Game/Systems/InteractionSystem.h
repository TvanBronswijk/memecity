#ifndef _INTERACTIONSYSTEM_H
#define  _INTERACTIONSYSTEM_H

#include <Engine\MultimediaManager.h>
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\InteractionEventArgs.h"

class InteractionSystem : public memecity::engine::ecs::System {

public:
	memecity::engine::MultimediaManager& multimedia_manager;

	InteractionSystem(memecity::engine::MultimediaManager& multimedia_manager)
		: multimedia_manager(multimedia_manager) {}

	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
	void on_interact(memecity::engine::ecs::EntityManager& em, InteractionEventArgs args);
};
#endif
