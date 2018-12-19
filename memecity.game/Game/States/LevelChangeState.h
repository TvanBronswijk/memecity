#ifndef LEVELCHANGESTATE_H
#define LEVELCHANGESTATE_H
#include <ECS.h>
#include <Engine/State/State.h>
#include "../../GameManager.h"
#include <UI/Menu/Menu.h>
#include "..\Input.h"

class LevelChangeState : public memecity::engine::state::State
{
	GameManager::GameContext* _context;
	memecity::engine::ecs::EntityManager* _entity_manager;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
public:
	LevelChangeState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, memecity::engine::ecs::EntityManager& em);

	void update(float dt) override;
	void draw() override;
	~LevelChangeState() = default;
};
#endif 
