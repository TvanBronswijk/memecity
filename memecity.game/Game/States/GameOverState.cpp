#include "GameOverState.h"
#include "..\..\Assets.h"
#include "..\Input.h"
#include <string>
#include "../HighscoreLoader.h"

GameOverState::GameOverState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, int experience)
	: State(sm), _context(&gc)
{
	this->experience = experience;
	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Game Over", assets::fonts::DEFAULT_FONT)
		.with_read_only_menu_item(" ")
		.with_read_only_menu_item("Enter your name:")
		.with_menu_item(" ")
		.with_read_only_menu_item(" ")
		.with_read_only_menu_item("Your total experience is:")
		.with_read_only_menu_item(std::to_string(experience))
		.with_read_only_menu_item(" ")
		.with_menu_item("Main Menu", nullptr, [&](auto& menu_item) { back(2);  })
		.get_menu();

	_context->get_input_manager().enable_text_editing();



}

void GameOverState::on_load()
{

}

void GameOverState::update(float dt)
{
	name_text = _context->get_input_manager().get_text();
	auto& input_manager = _context->get_input_manager();
	if (input_manager.is_pressed(input::UP))
	{
		//menu->next();
	}
	else if (input_manager.is_pressed(input::DOWN))
	{
		//menu->previous();
	}
	else if (input_manager.is_pressed(input::ENTER))
	{
		_context->get_input_manager().disable_text_editing();
		HighscoreLoader loader;
		auto load_data = _context->get_storage_manager().load(assets::saves::SAVE_HIGHSCORES);
		loader.Load(load_data);
		loader.add_highscore({ experience, name_text });
		auto save_data = loader.save();
		_context->get_storage_manager().save(assets::saves::SAVE_HIGHSCORES, save_data);
		menu->next();
		menu->select();
	}
}

void GameOverState::draw()
{
	menu->render();
	name_text_texture = _context->get_multimedia_manager().get_text(name_text, 24);
	name_text_texture->set_position(menu->get_position_of_item(2));
	_context->get_multimedia_manager().render_text(*name_text_texture);
}

void GameOverState::on_enter()
{

}

void GameOverState::on_exit()
{

}
