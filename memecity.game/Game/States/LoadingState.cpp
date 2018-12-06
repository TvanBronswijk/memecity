#include "LoadingState.h"
#include "GameState.h"

void LoadingState::on_load()
{
	auto listener = _loading_bar.get_listener();
	_loader(*_context, listener);
}

void LoadingState::update(float dt)
{

}

void LoadingState::draw()
{
	_loading_bar.render();
	multimedia_manager->render_texture(*_advertisement);
}

void LoadingState::on_enter()
{

}

void LoadingState::on_exit()
{

}