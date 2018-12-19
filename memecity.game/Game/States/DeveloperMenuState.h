#ifndef DEVELOPERMENUSTATE_H
#define DEVELOPERMENUSTATE_H
#include "Engine/State/State.h"
#include "UI/Menu/Menu.h"
#include "../../GameManager.h"
#include "ECS/EntityManager.h"
#include "UI/Overlay/Overlay.h"



class DeveloperMenuState : public memecity::engine::state::State
{
private:
	GameManager::GameContext* _context;
	memecity::engine::ecs::EntityManager* _entity_manager;
	memecity::engine::ui::overlay::Overlay* _hud;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> cheat_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> speed_menu;
public:
	DeveloperMenuState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, memecity::engine::ecs::EntityManager& em, memecity::engine::ui::overlay::Overlay& hud);

	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	~DeveloperMenuState() = default;
};
#endif // DEVELOPERMENUSTATE_H
