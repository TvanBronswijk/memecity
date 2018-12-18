#ifndef _GAME_LOADER_H
#define _GAME_LOADER_H
#include "..\GameManager.h"
#include <ECS.h>
#include <UI\Loading.h>

class LevelBuilder {
private:
	GameManager::GameContext* _context;
	int _map_width;
	int _map_height;
	bool _load_from_file;

public:
	LevelBuilder(GameManager::GameContext& context, int map_width, int map_height, bool load_from_file)
		: _context(&context), _map_width(map_width), _map_height(map_height), _load_from_file(load_from_file) {};
	~LevelBuilder() = default;

	Point build(memecity::engine::ecs::EntityManager& em, memecity::engine::ui::loading::LoadingBar::Listener& listener);
};

#endif