#ifndef _STORY_STATE_H
#define _STORY_STATE_H
#include <Engine/State.h>
#include <UI.h>
#include <ECS.h>
#include "..\Quest\Story.h"
#include "..\..\GameManager.h"

class StoryState : public memecity::engine::state::State
{
private:
	GameManager::GameContext* _context;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> help_menu;

	std::vector<Story> stories;
	int depth;
public:
	StoryState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, std::vector<Story> stories);
	~StoryState() = default;
	void make_menu(GameManager::GameContext & gc);
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};
#endif

