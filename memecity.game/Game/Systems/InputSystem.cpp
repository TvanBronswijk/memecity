﻿#include "InputSystem.h"
#include "..\Components.h"
#include "..\States.h"
#include "..\Input.h"
#include "..\States\DeveloperMenuState.h"
#include "..\PlayerManager.h"
#include "..\States\StatsState.h"
#include "..\Util\Util.h"
#include "..\LevelBuilder.h"
#include "..\States\LevelChangeState.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

bool InputSystem::check_collision(BaseComponent& l, BaseComponent& r , int range) const{
	return ((l.location.x + range) >= r.location.x && (l.location.x - range) <= r.location.x)
		&& ((l.location.y + range) >= r.location.y && (l.location.y - range) <= r.location.y);
}

void InputSystem::run(EntityManager& em, float dt) const
{
	auto& input_manager = _context->get_input_manager();
	auto& state_manager = _context->get_state_manager();

	auto players = em.get_entities_with_component<PlayerComponent>();
	for (const Entity& player : players)
	{
		auto player_stats = player.get<StatsComponent>();
		float speed = player.get<PlayerComponent>()->min_movement_speed + (player_stats->endurance * 10);

		auto animation_component = player.get<AnimationComponent>();
		auto velocity_component = player.get<VelocityComponent>();
		if (input_manager.is_down(input::UP))
		{
			animation_component->old_state = texture::AnimatedTexture::AnimationState::up;
			velocity_component->y -= speed;
		}
		else if (input_manager.is_down(input::DOWN))
		{
			animation_component->old_state = texture::AnimatedTexture::AnimationState::down;
			velocity_component->y += speed;
		}
		if (input_manager.is_down(input::LEFT))
		{
			animation_component->old_state = texture::AnimatedTexture::AnimationState::left;
			velocity_component->x -= speed;
		}
		else if (input_manager.is_down(input::RIGHT))
		{
			animation_component->old_state = texture::AnimatedTexture::AnimationState::right;
			velocity_component->x += speed;
		}

		if (input_manager.is_pressed(input::INTERACTION))
		{
			if (on_tile(em, player) == "Station") {
				state_manager.create_state<LevelChangeState>(*_context, em, *_map_number, *_save_slot);
			}

			auto npcs = em.get_entities_with_component<AIComponent>();
			for (const Entity& npc : npcs) {
				if(check_collision(*player.get<BaseComponent>(), *npc.get<BaseComponent>(), 60)){
					interaction_event.fire(em, { npc });
				}
			}
			auto quest_npcs = em.get_entities_with_component<QuestAIComponent>();
			for (const Entity& npc : quest_npcs) {
				if (check_collision(*player.get<BaseComponent>(), *npc.get<BaseComponent>(), 60)) {
					interaction_event.fire(em, { npc });
				}
			}
		}
		
		if (input_manager.is_pressed(input::ATTACK)) {
			auto npcs = em.get_entities_with_component<AIComponent>();
			for (const Entity& npc : npcs) {
				if (check_collision(*player.get<BaseComponent>(), *npc.get<BaseComponent>(), 60)) {
					attack_event.fire(em, {player, npc });
				}
			}
		}

		if (input_manager.is_pressed(input::Z)) {
			auto npcs = em.get_entities_with_component<AIComponent>();
			for (const Entity& npc : npcs) {
				if (check_collision(*player.get<BaseComponent>(), *npc.get<BaseComponent>(), 60)) {
					pickpocket_event.fire(em, { player, npc });
				}
			}
		}

		if (input_manager.is_pressed(input::ESCAPE)) {
			state_manager.create_state<PauseMenuState>(*_context, em, *_map_number, *_save_slot);
		}
		if (input_manager.is_pressed(input::STATS)) {
			auto& stats = *player.get<StatsComponent>();
			state_manager.create_state<StatsState>(*_context, *_hud, stats);
		}

		//inventory
		if (input_manager.is_pressed(input::DROP)) {
			auto inventory = player.get<InventoryComponent>();
			if (inventory->items.size() != 0){
				if (inventory->items.size() -1 < inventory->selected) {
					inventory->selected = inventory->items.size() - 1;
				}
				auto item = inventory->items.at(inventory->selected);
				inventory->items.erase(inventory->items.begin() + inventory->selected);

				//update position
				auto item_base = item->get<BaseComponent>();
				auto player_base = player.get<BaseComponent>();

				auto& animation_texture = dynamic_cast<texture::AnimatedTexture&>(player_base->get_texture());

				texture::AnimatedTexture::AnimationState state;
				if (animation_texture.get_state() != texture::AnimatedTexture::AnimationState::idle) {
					state = animation_texture.get_state();
				}
				else {
					state = animation_component->old_state;

				}
				switch (state) {
				case texture::AnimatedTexture::AnimationState::down:
					item_base->location = uPoint<float>(player_base->location.x, player_base->location.y + 50);
					break;
				case texture::AnimatedTexture::AnimationState::left:
					item_base->location = uPoint<float>(player_base->location.x - 50, player_base->location.y);
					break;
				case texture::AnimatedTexture::AnimationState::right:
					item_base->location = uPoint<float>(player_base->location.x + 50, player_base->location.y);
					break;
				case texture::AnimatedTexture::AnimationState::up:
					item_base->location = uPoint<float>(player_base->location.x, player_base->location.y - 50);
					break;
				case texture::AnimatedTexture::AnimationState::idle:
					item_base->location = uPoint<float>(player_base->location.x + 50, player_base->location.y);
					break;
				}

				this->quest_event.fire(em, { nullptr , item });
			}
		}
		if (input_manager.is_pressed(input::TAKE)) {
			auto inventory = player.get<InventoryComponent>();
			auto items = em.get_entities_with_component<ItemComponent>();
			//when collid you you can get the item
			for (const Entity& item : items) {
				if (check_collision(*player.get<BaseComponent>(), *item.get<BaseComponent>(), 60)) {
					inventory->items.emplace_back(&item);
					this->quest_event.fire(em, { &item , nullptr });
					item.get<BaseComponent>()->location = uPoint<float>(-999, -999);
				}
			}
		}

		if (input_manager.is_pressed(input::N)) {
			state_manager.create_state<StoryState>(*_context, player.get<PlayerComponent>()->_stories);
		}
		if(input_manager.is_pressed(input::DEVELOPER))
		{
			state_manager.create_state<DeveloperMenuState>(*_context, em, *_hud);
		}
		if (input_manager.is_pressed(input::ONE)) {
			auto inventory = player.get<InventoryComponent>();
			inventory->selected = 0;
			//item 1 is selected from items in itemcomponent
		}
		if (input_manager.is_pressed(input::TWO)) {
			auto inventory = player.get<InventoryComponent>();
			inventory->selected = 1;
			//item 2 is selected from items in itemcomponent
		}
		if (input_manager.is_pressed(input::THREE)) {
			auto inventory = player.get<InventoryComponent>();
			inventory->selected = 2;
			//item 3 is selected from items in itemcomponent
		}
		if (input_manager.is_pressed(input::ARROWDOWN)) {
			auto inventory = player.get<InventoryComponent>();
			if (inventory->selected == 0)
				inventory->selected = inventory->items.size();
			else
				inventory->selected--;

			//next item is selected from items in itemcomponent
		}
		if (input_manager.is_pressed(input::ARROWUP)) {
			auto inventory = player.get<InventoryComponent>();

			if (inventory->selected == inventory->items.size())
				inventory->selected = 0;
			else
				inventory->selected--;
			//previous item is selected from items in itemcomponent
		}

		if(input_manager.is_pressed(input::SPEEDDOWN))
		{
			auto* engine = &_context->get_engine();
			engine->set_games_speed_modifier(engine->get_game_speed_modifier() - 0.5f);
		}
		if(input_manager.is_pressed(input::SPEEDUP))
		{
			auto* engine = &_context->get_engine();
			engine->set_games_speed_modifier(engine->get_game_speed_modifier() + 0.5f);
		}
		if(input_manager.is_pressed(input::SPEEDRESET))
		{
			auto* engine = &_context->get_engine();
			engine->set_games_speed_modifier(1.0f);
		}
	}
}


