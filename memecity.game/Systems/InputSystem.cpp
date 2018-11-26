#include "InputSystem.h"
#include "Engine/State/State.h"
#include "../States.h"

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
	auto entities = em.get_entities_with_component<PlayerComponent>();

	for (auto& entity : entities)
	{

		auto velocity_component = entity.get().get<VelocityComponent>();
			
		auto animation_component = entity.get().get<AnimationComponent>();

		if (this->input_manager.is_down(sdl::Attack))
		{
			animation_component->is_fighting = true;
		}
		if (this->input_manager.is_down(sdl::Up))
		{
			velocity_component->y -= 0.1f;
		}
		if (this->input_manager.is_down(sdl::Down))
		{
			velocity_component->y += 0.1f;
		}
		if (this->input_manager.is_down(sdl::Left))
		{
			velocity_component->x -= 0.1f;
		}
		if (this->input_manager.is_down(sdl::Right))
		{
			velocity_component->x += 0.1f;
		}
		//test for interaction with NPC
		if (this->input_manager.is_down(sdl::Interaction))
		{
			auto vector = em.get_components_of_type<AIComponent>();
			for (auto& element : vector) {
				if(check_collision(em, element, 30)){
					interaction_event.fire(em, { element.get().entity() });
				}
			}
		}
		if (this->input_manager.is_down(sdl::Attack)) {
			auto player = em.get_components_of_type<PlayerComponent>()[0];
			auto vector = em.get_components_of_type<AIComponent>();
			for (auto & element : vector) {
				if (check_collision(em, element, 30)) {
					attack_event.fire(em, {player.get().entity(), element.get().entity() });

				}
			}
		}
		if (this->input_manager.is_pressed(sdl::Escape)) {
			state_machine.create_state<PauseMenuState>(state_machine.current_state()->get_context());
		}
	}
}

