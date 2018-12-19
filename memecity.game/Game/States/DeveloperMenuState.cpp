#include "DeveloperMenuState.h"
#include "UI/Menu/MenuBuilder.h"
#include "../../Assets.h"
#include "../Input.h"
#include "../Components/PlayerComponent.h"
#include "../Components/HealthComponent.h"
#include "../Systems/ExpSystem.h"

DeveloperMenuState::DeveloperMenuState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, memecity::engine::ecs::EntityManager& em, memecity::engine::ui::overlay::Overlay& _hud)
	:State(sm), _context(&gc), _entity_manager(&em), _hud(&_hud)
{

	cheat_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Cheats", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Motherlode", nullptr, [&](auto& menu_item)//money
	{
		auto player = em.get_components_of_type<PlayerComponent>();
		for (auto& player_component : player)
		{
			player_component.get().blik_coins += 50000;
			_hud.update("BLIKCOIN", "BlikCoin: " + std::to_string(player_component.get().blik_coins));

		}
		back();
	})
		.with_menu_item("wanpanman", nullptr, [&](auto& menu_item)// one punch kill
	{
		auto players = em.get_components_of_type<PlayerComponent>();
		for (auto& player : players)
		{
			const auto& stats = player.get().entity().get<StatsComponent>();
			stats->strength = 100;
		}
		back();
	})
		.with_menu_item("Avada Kedavra", nullptr, [&](auto& menu_item)// alle (niet quest) npcs gaan dood
	{
		auto healtyEntities = em.get_entities_with_component<HealthComponent>();
		for (auto& healty_entity : healtyEntities)
		{
			if(!healty_entity.get().has<PlayerComponent>())
			{
				const auto& health = healty_entity.get().get<HealthComponent>();
				health->health = 0;
			}
		}
		back();
	})
		.with_back_menu_item()
		.get_menu();

	auto& engine = _context->get_engine();
	
	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Developer Menu", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) {back(); })
		.with_menu_item("Toggle fps on", nullptr, [&](auto& menu_item)
	{
		auto& engine = _context->get_engine();
		engine.bind_fps([&](bool enabled, auto fps)
		{
			if (enabled) {
				_hud.update("FPS", "FPS: " + std::to_string(fps));
			}
			else
			{
				_hud.update("FPS", " ");
			}
		});
	})
		.with_menu_item("Toggle fps off", nullptr, [&](auto& menu_item) {engine.disable_calculate_fps(); })
		.with_menu_item("Toggle gamespeed on", nullptr, [&](auto& menu_item)
	{
		engine.bind_game_speed([&](bool enabled, float game_speed)
		{
			if (enabled)
			{
				_hud.update("GAMESPEED", "Gamespeed: " + std::to_string(game_speed));
			}
			else
			{
				_hud.update("GAMESPEED", " ");
			}
		}); 
	})
		.with_menu_item("Toggle gamespeed off", nullptr, [&](auto& menu_item) {engine.disable_display_gamespeed(); })
		.with_menu_item("Cheats", cheat_menu.get())
		.get_menu();

	
}

void DeveloperMenuState::on_load()
{
}

void DeveloperMenuState::update(float dt)
{
	auto& input_manager = _context->get_input_manager();
	if (input_manager.is_pressed(input::UP))
	{
		menu->next();
	}
	else if (input_manager.is_pressed(input::DOWN))
	{
		menu->previous();
	}
	else if (input_manager.is_pressed(input::ENTER))
	{
		menu->select();
	}
	else if (input_manager.is_pressed(input::ESCAPE))
	{
		if (!menu->back())
		{
			back();
		}
	}
}

void DeveloperMenuState::draw()
{
	menu->render();
}

void DeveloperMenuState::on_enter()
{
}

void DeveloperMenuState::on_exit()
{
}
