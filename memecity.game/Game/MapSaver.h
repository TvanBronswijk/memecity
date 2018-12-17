#ifndef _MAPSAVER_H
#define _MAPSAVER_H
#include "ECS/EntityManager.h"

class MapSaver
{
public:
	void save(memecity::engine::ecs::EntityManager& em);
};

#endif