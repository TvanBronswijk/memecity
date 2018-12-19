#include "GameOverState.h"
#include "..\..\Assets.h"
#include "..\Input.h"
#include <string>

GameOverState::GameOverState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, int experience)
	: State(sm), _context(&gc)
{
	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Game Over", assets::fonts::DEFAULT_FONT)
		.with_read_only_menu_item(" ")
		.with_read_only_menu_item("Your total experience is:")
		.with_read_only_menu_item(std::to_string(experience))
		.with_read_only_menu_item(" ")
		.with_menu_item("Main Menu", nullptr, [&](auto& menu_item) { back(2);  })
		.get_menu();
}

void GameOverState::on_load()
{

}

void GameOverState::update(float dt)
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
}

void GameOverState::draw()
{
	menu->render();
}

void GameOverState::on_enter()
{

}

void GameOverState::on_exit()
{

}
