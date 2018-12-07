#include "GameState.h"
#include "LoadingState.h"
#include "../../Assets.h"
#include "../Systems/FightingSystem.h"
#include "..\GameLoader.h"

void GameState::on_load()
{
	next<LoadingState>(*_context, [&](auto& ctx, auto& listener) { GameLoader(ctx, 256, 256).build(entity_manager, listener); back(); });
}

void GameState::update(float dt)
{
	system_pool.update(entity_manager, memecity::engine::ecs::System::update);
}

void GameState::draw()
{
	system_pool.update(entity_manager, memecity::engine::ecs::System::draw);
	_hud.render();
}

void GameState::on_enter()
{
	_context->get_multimedia_manager().play_background_music(assets::music::DEFAULT_BGM);
}

void GameState::on_exit()
{
	_context->get_multimedia_manager().pause_background_music();
}
