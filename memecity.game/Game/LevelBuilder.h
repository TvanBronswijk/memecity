#ifndef _GAME_LOADER_H
#define _GAME_LOADER_H
#include "..\GameManager.h"
#include <ECS.h>
#include <UI\Loading.h>

class LevelBuilder {
private:
	GameManager::GameContext* _context;
	int _level;
	int _map_width;
	int _map_height;
	bool _load_from_file;
	std::string _save_location;

public:
	LevelBuilder(GameManager::GameContext& context, int level, int map_width, int map_height, bool load_from_file, std::string save_location = "")
		: _context(&context), _level(level), _map_width(map_width), _map_height(map_height), _load_from_file(load_from_file),_save_location(save_location) {};
	~LevelBuilder() = default;

	Point build(memecity::engine::ecs::EntityManager& em, memecity::engine::ui::loading::LoadingBar::Listener& listener, int& map_number);
};

#endif
