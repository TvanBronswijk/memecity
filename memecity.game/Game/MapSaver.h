#ifndef _MAPSAVER_H
#define _MAPSAVER_H
#include "ECS/EntityManager.h"

class MapSaver
{
public:
	std::string get_map(memecity::engine::ecs::EntityManager& em);
};

#endif