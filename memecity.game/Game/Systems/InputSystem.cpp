#include "InputSystem.h"
#include "..\Components.h"
#include "..\States.h"
#include "..\Input.h"

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
	for (const Entity& entity : entities)
	{
		auto velocity_component = entity.get<VelocityComponent>();
		if (input_manager.is_down(input::UP))
		{
			velocity_component->y -= 0.1f;
		}
		if (input_manager.is_down(input::DOWN))
		{
			velocity_component->y += 0.1f;
		}
		if (input_manager.is_down(input::LEFT))
		{
			velocity_component->x -= 0.1f;
		}
		if (input_manager.is_down(input::RIGHT))
		{
			velocity_component->x += 0.1f;
		}
		//test for interaction with NPC
		if (input_manager.is_pressed(input::INTERACTION))
		{
			auto vector = em.get_components_of_type<AIComponent>();
			for (AIComponent& element : vector) {
				if(check_collision(em, element, 30)){
					interaction_event.fire(em, { element.entity() });
				}
			}
		}
		if (input_manager.is_pressed(input::ATTACK)) {
			const auto animation_component = entity.get<AnimationComponent>();
			if (animation_component)
			{
				animation_component->current_state = AnimationComponent::AnimationState::fighting;
			}

			auto& player = em.get_components_of_type<PlayerComponent>()[0].get();
			auto vector = em.get_components_of_type<AIComponent>();
			for (AIComponent& element : vector) {
				if (check_collision(em, element, 30)) {
					attack_event.fire(em, {player.entity(), element.entity() });
				}
			}
		}
		if (input_manager.is_pressed(input::ESCAPE)) {
			state_manager.create_state<PauseMenuState>(*_context);
		}
		//inventory
		if (input_manager.is_pressed(input::DROP)) {
			auto player_position = entity.get<PositionComponent>();
			auto player_drawable = entity.get<DrawableComponent>();

			auto inventory = entity.get<InventoryComponent>();
			auto item = inventory->items.at(inventory->selected);
			inventory->items.erase(inventory->items.begin() + inventory->selected);

			//update position
			auto item_position = item->get<PositionComponent>();
			auto item_drawable = item->get<DrawableComponent>();

			item_position = player_position;
			item_drawable->get_texture().set_position(player_drawable->get_texture().get_position());

			//drop item to items in itemcomponent
		}
		if (input_manager.is_pressed(input::TAKE)) {
			auto inventory = entity.get<InventoryComponent>();
			//when collid you you can get the item
			inventory->items.emplace_back();

			//update postion texture

			//add item to items in itemcomponent
		}
		if (input_manager.is_pressed(input::ONE)) {
			auto inventory = entity.get<InventoryComponent>();
			inventory->selected = 1;
			//item 1 is selected from items in itemcomponent
		}
		if (input_manager.is_pressed(input::TWO)) {
			auto inventory = entity.get<InventoryComponent>();
			inventory->selected = 2;
			//item 2 is selected from items in itemcomponent
		}
		if (input_manager.is_pressed(input::THREE)) {
			auto inventory = entity.get<InventoryComponent>();
			inventory->selected = 3;
			//item 3 is selected from items in itemcomponent
		}
		if (input_manager.is_pressed(input::ARROWDOWN)) {
			auto inventory = entity.get<InventoryComponent>();
			if (inventory->selected == 0)
				inventory->selected = inventory->items.size();
			else
				inventory->selected--;
			
			//next item is selected from items in itemcomponent
		}
		if (input_manager.is_pressed(input::ARROWUP)) {
			auto inventory = entity.get<InventoryComponent>();

			if (inventory->selected == inventory->items.size())
				inventory->selected = 0;
			else
				inventory->selected--;
			//previous item is selected from items in itemcomponent
		}
	}
}

