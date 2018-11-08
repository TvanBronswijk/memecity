#include "InputSystem.h"

#include "PlayerComponent.h"
#include "VelocityComponent.h"
#include "InteractionSystem.h"

using namespace ecs;

system_typetoken InputSystem::SYSTEM_TYPE = "InputSystem";

InputSystem::InputSystem(InputManager &input_manager) : input_manager(input_manager)
{
	this->interaction_event = interaction_event;
	this->attack_event = attack_event;
}

bool InputSystem::check_collision(EntityManager& em, Component& element , int range) const{
	auto player = em.get_components_of_type<PlayerComponent>(PlayerComponent::COMPONENT_TYPE)[0];
	auto player_position_component = em.get_component_of_entity<PositionComponent>(player.get().entity, PositionComponent::COMPONENT_TYPE);
	auto xy = em.get_component_of_entity<PositionComponent>(element.entity, PositionComponent::COMPONENT_TYPE);
	if ((player_position_component->x + range) >= xy->x && (player_position_component->x - range) <= xy->x) {
		if ((player_position_component->y + range) >= xy->y && (player_position_component->y - range) <= xy->y) {
			return true;
		}
	}
	return false;
}

void InputSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component(PlayerComponent::COMPONENT_TYPE);

	for (auto entity : entities)
	{
		auto velocity_component = em.get_component_of_entity<VelocityComponent>(entity.get(), VelocityComponent::COMPONENT_TYPE);


		if (this->input_manager.is_pressed(Up))
		{
			velocity_component->y += 5;
		}
		if (this->input_manager.is_pressed(Down))
		{
			velocity_component->y -= 5;
		}
		if (this->input_manager.is_pressed(Left))
		{
			velocity_component->x -= 5;
		}
		if (this->input_manager.is_pressed(Right))
		{
			velocity_component->x += 5;
		}
		//test for interaction with NPC
		if (this->input_manager.is_pressed(Interaction))
		{
			auto vector = em.get_components_of_type<AIComponent>(AIComponent::COMPONENT_TYPE);
			for (auto& element : vector) {
				if(check_collision(em, element, 30)){
					auto args = InteractionEventArgs(element.get().entity.id);
					//interaction_event->fire(em, args);
				}
			}
		}
		if (this->input_manager.is_pressed(Attack)) {
			auto player = em.get_components_of_type<PlayerComponent>(PlayerComponent::COMPONENT_TYPE)[0];
			auto vector = em.get_components_of_type<AIComponent>(AIComponent::COMPONENT_TYPE);
			for (auto & element : vector) {
				if (check_collision(em, element, 30)) {
					auto args = AttackEventArgs(player.get().entity.id, element.get().entity.id);
					//attack_event->fire(em, args);
				}
			}
		}
	}
}

