#ifndef _GAME_LOADING_STATE_H
#define  _GAME_LOADING_STATE_H
#include <functional>
#include <Engine\State.h>
#include "..\..\GameManager.h"

struct LoadingState : public memecity::engine::state::State {
	using Loader = std::function<void(GameManager::GameContext&)>;
private:
	GameManager::GameContext* _context;
	Loader _loader;
public:
	LoadingState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, Loader loader)
		: State(sm), _context(&gc), _loader(loader) {}
	~LoadingState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif
