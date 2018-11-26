#include "InputSystem.h"
#include "..\Components.h"
#include "..\States.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

bool InputSystem::check_collision(EntityManager& em, Component& element , int range) const{
	auto player = em.get_components_of_type<PlayerComponent>()[0];
	auto player_position_component = player.get().entity().get<PositionComponent>();
	auto xy = element.entity().get<PositionComponent>();
	if ((player_position_component->x + range) >= xy->x && (player_position_component->x - range) <= xy->x) {
		if ((player_position_component->y + range) >= xy->y && (player_position_component->y - range) <= xy->y) {
			return true;
		}
	}
	return false;
}

void InputSystem::run(EntityManager& em) const
{
	auto& input_manager = _context->get_input_manager();
	auto& state_manager = _context->get_state_manager();

	auto entities = em.get_entities_with_component<PlayerComponent>();
	for (auto& entity : entities)
	{
		auto velocity_component = entity.get().get<VelocityComponent>();

		if (input_manager.is_down(sdl::Attack))
		{
			const auto &fighting_component = entity.get().get<FightingComponent>();
			fighting_component->is_fighting = true;
		}
		if (input_manager.is_down(sdl::Up))
		{
#ifdef DEBUG
			std::cout << "walking /n";
#endif
			velocity_component->y += 5;
		}
		if (input_manager.is_down(sdl::Down))
		{
			velocity_component->y -= 5;
		}
		if (input_manager.is_down(sdl::Left))
		{
			velocity_component->x -= 5;
		}
		if (input_manager.is_down(sdl::Right))
		{
			velocity_component->x += 5;
		}
		//test for interaction with NPC
		if (input_manager.is_down(sdl::Interaction))
		{
			auto vector = em.get_components_of_type<AIComponent>();
			for (auto& element : vector) {
				if(check_collision(em, element, 30)){
					interaction_event.fire(em, { element.get().entity() });
				}
			}
		}
		if (input_manager.is_down(sdl::Attack)) {
			auto player = em.get_components_of_type<PlayerComponent>()[0];
			auto vector = em.get_components_of_type<AIComponent>();
			for (auto & element : vector) {
				if (check_collision(em, element, 30)) {
					attack_event.fire(em, {player.get().entity(), element.get().entity() });

				}
			}
		}
		if (input_manager.is_pressed(sdl::Escape)) {
			state_manager.create_state<PauseMenuState>(*_context);
		}
	}
}

