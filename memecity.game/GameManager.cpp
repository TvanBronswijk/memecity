#include "GameManager.h"
#include "Game\States.h"
#include "Assets.h"

void GameManager::init()
{
	multimedia_manager.set_default_font(assets::fonts::DEFAULT_FONT);
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
