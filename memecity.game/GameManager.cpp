#include "GameManager.h"
#include "Game\States.h"

void GameManager::init()
{
	_states.create_state<MenuState>(get_context());
}

void GameManager::update(float dt)
{
	_states.update(dt);
}

void GameManager::draw()
{
	_states.draw();
}
