#include "PauseMenuState.h"
#include "..\..\Assets.h"
#include "..\Input.h"
#include "../MapSaver.h"
#include "../PlayerManager.h"

PauseMenuState::PauseMenuState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, memecity::engine::ecs::EntityManager & em)
	: State(sm), _context(&gc), _entity_manager(&em)
{


	help_menu2 = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Help", assets::fonts::DEFAULT_FONT)
		.with_read_only_menu_item("Goal:")
		.with_read_only_menu_item("Kill NPCs to gain XP.")
		.with_read_only_menu_item("Interact with NPCs to start quests.")
		.with_read_only_menu_item("Complete quests to gain more XP.")
		.with_read_only_menu_item(" ")
		.with_read_only_menu_item("Die or click Retire to finish the game.")
		.with_read_only_menu_item(" ")
		//add next when needed.
		.with_back_menu_item()
		.get_menu();

	help_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Help", assets::fonts::DEFAULT_FONT)
		.with_read_only_menu_item("Controls:")
		.with_read_only_menu_item("W: Up")
		.with_read_only_menu_item("S: Down")
		.with_read_only_menu_item("A: Left")
		.with_read_only_menu_item("D: Right")
		.with_read_only_menu_item("E: Interact")
		.with_read_only_menu_item("Space: Attack")
		.with_read_only_menu_item("F: Take")
		.with_read_only_menu_item("R: Drop")
		.with_read_only_menu_item("Arrow up: next item")
		.with_read_only_menu_item("Arrow down: previous item")
		.with_read_only_menu_item(" ")
		.with_menu_item("Next", help_menu2.get())
		.with_back_menu_item()
		.get_menu();

	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Paused", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) { back(); })
		.with_menu_item("Help", help_menu.get())
		.with_read_only_menu_item(" ")
		.with_menu_item("Save Game", nullptr, [&](auto& menu_item)
	       {
		       const auto player_manager = PlayerManager(*_entity_manager);
		       const auto player_data = player_manager.save_player();
		       const auto success = _context->get_storage_manager().save(assets::saves::SAVE_GAME, player_data);

			   auto map = MapSaver{}.get_map(em);
			   auto map_success = _context->get_storage_manager().save_string(assets::saves::SAVE_MAP, map);
			   if (success && map_success) back();
	       })
		.with_menu_item("Main Menu", nullptr, [&](auto& menu_item) { back(2); })
		.get_menu();
}

void PauseMenuState::on_load()
{

}

void PauseMenuState::update(float dt)
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

void PauseMenuState::draw()
{
	menu->render();
}

void PauseMenuState::on_enter()
{

}

void PauseMenuState::on_exit()
{

}
