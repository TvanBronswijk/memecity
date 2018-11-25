#ifndef _GAME_LOADER_H
#define _GAME_LOADER_H
#include "..\GameManager.h"
#include <ECS.h>

class GameLoader {
private:
	GameManager::GameContext* _context;
	int _map_width;
	int _map_height;

	void create_map(memecity::engine::ecs::EntityManager& em);
	void create_npcs(memecity::engine::ecs::EntityManager& em);
	void create_player(memecity::engine::ecs::EntityManager& em);
	void create_systems(memecity::engine::ecs::EntityManager& em);
public:
	GameLoader(GameManager::GameContext& context, int map_width, int map_height)
		: _context(&context), _map_width(map_width), _map_height(map_height) {};
	~GameLoader() = default;
	std::unique_ptr<memecity::engine::ecs::EntityManager> build();
};

#endif
