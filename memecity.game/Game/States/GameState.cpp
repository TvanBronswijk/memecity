#include "GameState.h"



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
