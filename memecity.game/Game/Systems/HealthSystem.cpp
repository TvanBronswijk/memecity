#include "HealthSystem.h"
#include "../States/GameOverState.h"

using namespace memecity::engine::ecs;

void HealthSystem::run(EntityManager& em) const {

	auto& state_manager = _context->get_state_manager();
	auto player = em.get_entities_with_component<PlayerComponent>()[0];
	auto health_player = player.get().get<HealthComponent>();

	if (health_player->health <= 0) {
		state_manager.create_state<GameOverState>(*_context);
	}
}
