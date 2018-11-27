#include "GameState.h"

GameState::GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc,
	std::unique_ptr<memecity::engine::ecs::EntityManager> em)
	: State(sm), _context(&gc), entity_manager(std::move(em)), _hud(_context->get_multimedia_manager(), _context->get_multimedia_manager().get_texture("big_black.bmp",0,0, _context->get_multimedia_manager().get_screen_width(),100),0,0)
{
	//_hud.create_overlay_item(memecity::engine::ui::overlay::OverlayItem(_context->get_multimedia_manager(), _hud, std::string("Health:100"), 0, 0));
	_hud.create_overlay_item("Health:100", 20, 100, 20);
}

void GameState::on_load()
{

}

void GameState::update(float dt)
{
	entity_manager.update(memecity::engine::ecs::System::update);
}

void GameState::draw()
{
	entity_manager.update(memecity::engine::ecs::System::draw);
	_hud.render();
}

void GameState::on_enter()
{
	_context->get_multimedia_manager().play_background_music("Music/bgm-game.mp3", 100);
}

void GameState::on_exit()
{
	_context->get_multimedia_manager().pause_background_music();
}
