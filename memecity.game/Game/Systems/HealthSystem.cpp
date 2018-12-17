#include "HealthSystem.h"
#include "../States/GameOverState.h"

using namespace memecity::engine::ecs;

void HealthSystem::run(EntityManager& em, float dt) const {}

void HealthSystem::on_death(EntityManager &em, eventing::EventArgs args) {
	auto player = em.get_entities_with_component<PlayerComponent>().front();
	auto exp_component = player.get().get<ExpComponent>();

	auto& state_manager = _context->get_state_manager();
	state_manager.create_state<GameOverState>(*_context, exp_component->exp);
}
