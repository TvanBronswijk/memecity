#include "HealthSystem.h"
#include "../States/GameOverState.h"

using namespace memecity::engine::ecs;

void HealthSystem::run(EntityManager& em) const {}

void HealthSystem::on_death(EntityManager &em) {
	auto& state_manager = _context->get_state_manager();
	state_manager.create_state<GameOverState>(*_context);
}
