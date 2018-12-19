#ifndef _STATS_STATE_H
#define __STATS_STATE_H
#include <Engine/State.h>
#include <UI.h>
#include "..\Components\StatsComponent.h"
#include "..\..\GameManager.h"
#include "UI/Overlay/Overlay.h"


enum class SPECIAL { Strenght, Perception, Luck, Intelligence, Endurance, Charisma, Agility };

class StatsState : public memecity::engine::state::State
{
private:
	GameManager::GameContext* _context;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
	void make_new_menu(memecity::engine::ui::overlay::Overlay& hud, StatsComponent& stats);

public:
	StatsState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, memecity::engine::ui::overlay::Overlay& hud, StatsComponent& stats);
	~StatsState() = default;
	void increase(memecity::engine::ui::overlay::Overlay& hud, StatsComponent& stats, SPECIAL type);
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};
#endif

