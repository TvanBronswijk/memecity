#ifndef _GAME_LOADING_STATE_H
#define  _GAME_LOADING_STATE_H
#include <ctime>
#include <functional>
#include <Engine\State.h>
#include <UI\Loading.h>
#include "..\..\GameManager.h"
#include "../../Assets.h"

struct LoadingState : public memecity::engine::state::State {
	using Loader = std::function<void(GameManager::GameContext&, memecity::engine::ui::loading::LoadingBar::Listener& listener)>;
private:
	GameManager::GameContext* _context;
	std::unique_ptr<memecity::engine::texture::Texture> _advertisement;
	memecity::engine::ui::loading::LoadingBar _loading_bar;
	LoadingState::Loader _loader;
public:
	LoadingState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, LoadingState::Loader loader)
		: State(sm), _context(&gc), _loading_bar(gc.get_multimedia_manager()), _loader(loader)
	{
		srand(time(nullptr));

		this->_advertisement = _context->get_multimedia_manager().get_texture(assets::advertisements::get_random_ad());
		this->_advertisement->set_position({ _context->get_multimedia_manager().get_screen_width() / 2.0f, (_context->get_multimedia_manager().get_screen_height() - (_advertisement->get_render_rect().h / 2.0f)) });
	}

	~LoadingState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif
