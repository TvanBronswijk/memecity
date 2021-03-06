#ifndef _GAME_OVER_STATE_H
#define __OVER_STATE_H
#include <Engine/State.h>
#include <UI.h>
#include "..\..\GameManager.h"

class GameOverState : public memecity::engine::state::State
{
private:
	GameManager::GameContext* _context;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
	std::unique_ptr<memecity::engine::texture::TextTexture> name_text_texture;
	std::string name_text = " ";
	int experience;
	bool retire;
public:
	GameOverState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, int exp, bool retire = false);
	~GameOverState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};
#endif
