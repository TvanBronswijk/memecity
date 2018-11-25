#include "GameLoadingState.h"
#include "GameState.h"

void GameLoadingState::on_load()
{
	replace<GameState>(get_context(), game_loader.build());
}

void GameLoadingState::update(float dt)
{

}

void GameLoadingState::draw()
{

}

void GameLoadingState::on_enter()
{

}

void GameLoadingState::on_exit()
{

}
