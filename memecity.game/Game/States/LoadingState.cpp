#include "LoadingState.h"
#include "GameState.h"
#include "Engine/SDL/Wrappers/FileWrapper.h"

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
	memecity::engine::sdl::FileWrapper fw = memecity::engine::sdl::FileWrapper("Assets/new-game.txt");
	_loading_bar.render();
	_context->get_multimedia_manager().render_texture(*_advertisement);
}

void LoadingState::on_enter()
{

}

void LoadingState::on_exit()
{

}