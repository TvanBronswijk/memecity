#include "InputSystem.h"

using namespace ecs;

system_typetoken InputSystem::SYSTEM_TYPE = "InputSystem";

InputSystem::InputSystem(InputManager &input_manager) : input_manager(input_manager)
{
	this->input_manager = input_manager;
	this->interaction_event = interaction_event;
	this->attack_event = attack_event;
}

bool InputSystem::check_collision(EntityManager& em, Component* element , int range){
	auto player = em.get_components_of_type(PlayerComponent::COMPONENT_TYPE);
	auto player_position_component = dynamic_cast<PositionComponent*>(em.get_component_of_entity(player[0]->entity_id, PositionComponent::COMPONENT_TYPE));
	PositionComponent* xy = (PositionComponent*)em.get_component_of_entity(element->entity_id, PositionComponent::COMPONENT_TYPE);
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


		if (this->input_manager.is_pressed(UP))
		{
			velocity_component->y += 5;
		}
		if (this->input_manager.is_pressed(DOWN))
		{
			velocity_component->y -= 5;
		}
		if (this->input_manager.is_pressed(LEFT))
		{
			velocity_component->x -= 5;
		}
		if (this->input_manager.is_pressed(RIGHT))
		{
			velocity_component->x += 5;
		}
		//test for interaction with NPC
		if (this->input_manager.lock()->is_pressed(INTERACTION))
		{
			auto vector = em.get_components_of_type(AIComponent::COMPONENT_TYPE);
			for (auto & element : vector) {
				if(check_collision(em, element, 30)){
					auto args = InteractionEventArgs(element->entity_id);
					interaction_event->fire(em, args);
				}
			}
		}
		if (this->input_manager.lock()->is_pressed(ATTACK)) {
			auto player = em.get_components_of_type(PlayerComponent::COMPONENT_TYPE);
			auto vector = em.get_components_of_type(AIComponent::COMPONENT_TYPE);
			for (auto & element : vector) {
				if (check_collision(em, element, 30)) {
					auto args = AttackEventArgs(player[0]->entity_id, element->entity_id);
					attack_event->fire(em, args);
				}
			}
		}
	}
}


void InputSystem::run(EntityManager& em, EventArgs& e)
{
}
