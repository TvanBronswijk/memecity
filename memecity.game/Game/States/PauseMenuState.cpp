#include "PauseMenuState.h"
#include "..\Input.h"

PauseMenuState::PauseMenuState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc)
	: State(sm), _context(&gc)
{
	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Paused")
		.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) { back(); })
		.with_menu_item("Main menu", nullptr, [&](auto& menu_item) { back(2);  })
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
		menu->back();
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
