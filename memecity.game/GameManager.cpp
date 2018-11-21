#include "GameManager.h"
#include "States.h"

void GameManager::init()
{
	_states.create_state<MenuState>(_context);
}

void GameManager::update(float dt)
{
	_states.update(dt);
}

void GameManager::draw()
{
	_states.draw();
}
