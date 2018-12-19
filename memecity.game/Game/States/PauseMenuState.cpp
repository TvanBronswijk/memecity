#include "PauseMenuState.h"
#include "..\..\Assets.h"
#include "..\Input.h"
#include "../MapSaver.h"
#include "../PlayerManager.h"
#include "../GameSaver.h"
#include "GameOverState.h"
#include "../Components/ExpComponent.h"

PauseMenuState::PauseMenuState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, memecity::engine::ecs::EntityManager & em, int& map_number, std::string& save_slot)
	: State(sm), _context(&gc), _entity_manager(&em), _map_number(&map_number), _save_slot(&save_slot)
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

	;

	retire_confirm_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Retire?", assets::fonts::DEFAULT_FONT)
		.with_menu_item("No", nullptr, [&](memecity::engine::ui::menu::MenuItem& menu_item) { menu_item.unlock(); })
		.with_menu_item("Yes", nullptr, [&](auto& menu_item) {_context->get_state_manager().create_state<GameOverState>(*_context, _entity_manager->get_components_of_type<ExpComponent>().front().get().exp, true);  })
		.get_menu();

	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Paused", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) { back(); })
		.with_menu_item("Help", help_menu.get())
		.with_read_only_menu_item(" ")
		.with_menu_item("Save Game", nullptr, [&](memecity::engine::ui::menu::MenuItem& menu_item) {GameSaver{}.save(em, *_context, *_save_slot, map_number); back(); })
		.with_menu_item("Main Menu", nullptr, [&](auto& menu_item) { back(2); })
		.with_read_only_menu_item("-----")
		.with_menu_item("Retire", retire_confirm_menu.get())
		.with_read_only_menu_item("-----")
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
