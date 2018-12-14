#include "DeveloperMenuState.h"
#include "UI/Menu/MenuBuilder.h"
#include "../../Assets.h"
#include "../Input.h"
#include "../Components/PlayerComponent.h"
#include "../Components/HealthComponent.h"
#include "../Systems/ExpSystem.h"

DeveloperMenuState::DeveloperMenuState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, memecity::engine::ecs::EntityManager& em)
	:State(sm), _context(&gc), _entity_manager(&em)
{

	cheat_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Cheats", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Motherlode", nullptr, [&](auto& menu_item)
	{
		auto player = em.get_components_of_type<PlayerComponent>();
		for (auto& player_component : player)
		{
			player_component.get().BlikCoins += 50000;

		}
	})//money
		.with_menu_item("wanpanman", nullptr, [&](auto& menu_item)// one punch kill
	{
		auto players = em.get_components_of_type<PlayerComponent>();
		for (auto& player : players)
		{
			const auto& stats = player.get().entity().get<StatsComponent>();
			stats->strength = 100;
		}
	})
		.with_menu_item("Amnesia Completa",nullptr, [&](auto& menu_item)
	{
		//TODO
	})// npcs vergeten dat ze boos zijn
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
	})
		.with_back_menu_item()
		.get_menu();

	auto& engine = _context->get_engine();
	
	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Developer Menu", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) {back(); })
		.with_menu_item("Toggle fps on", nullptr, [&](auto& menu_item) {engine.set_calculate_fps(true); })
		.with_menu_item("Toggle fps off", nullptr, [&](auto& menu_item) {engine.set_calculate_fps(false); })
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
