#ifndef _GAME_LOADING_STATE_H
#define  _GAME_LOADING_STATE_H
#include <functional>
#include <Engine\State.h>
#include <UI\Loading.h>
#include "..\..\GameManager.h"

struct LoadingState : public memecity::engine::state::State {
	using Loader = std::function<void(GameManager::GameContext&, memecity::engine::ui::loading::LoadingBar::Listener& listener)>;
private:
	GameManager::GameContext* _context;
	memecity::engine::ui::loading::LoadingBar _loading_bar;
	LoadingState::Loader _loader;
public:
	LoadingState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, LoadingState::Loader loader)
		: State(sm), _context(&gc), _loader(loader), _loading_bar(gc.get_multimedia_manager()) {}
	~LoadingState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif
