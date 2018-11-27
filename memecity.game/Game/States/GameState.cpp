#include "GameState.h"
#include "..\..\Assets.h"

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
}

void GameState::on_enter()
{
	_context->get_multimedia_manager().play_background_music(assets::music::DEFAULT_BGM, 100);
}

void GameState::on_exit()
{
	_context->get_multimedia_manager().pause_background_music();
}
