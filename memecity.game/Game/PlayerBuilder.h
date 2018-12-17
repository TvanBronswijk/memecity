#ifndef _PLAYER_BUILDER_H
#define _PLAYER_BUILDER_H
#include "..\GameManager.h"
#include <ECS.h>
#include <UI\Loading.h>

class PlayerBuilder {
private:
	GameManager::GameContext* _context;
	Point _start;

public:
	PlayerBuilder(GameManager::GameContext& context, Point start)
		: _context(&context), _start(start) {};
	~PlayerBuilder() = default;

	const memecity::engine::ecs::Entity& build(memecity::engine::ecs::EntityManager& em, memecity::engine::ui::loading::LoadingBar::Listener& listener);
};

#endif
