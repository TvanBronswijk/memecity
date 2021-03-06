﻿#include "MapSaver.h"
#include "ECS/Default/BaseComponent.h"
#include "Components/TileComponent.h"
#include "Generate/City/Models/Models.h"
#include "Generate/City/CityGenerator.h"

std::string MapSaver::get_map(memecity::engine::ecs::EntityManager& em)
{
	auto map_entities = em.get_entities_by_type("tile");
	int max_x = 0;
	int max_y = 0;

	for (auto entity : map_entities)
	{
		auto base_component = entity.get().get<BaseComponent>();
		int x = base_component->location.x + base_component->w;
		if (x > max_x)
		{
			max_x = x;
		}

		int y = base_component->location.y + base_component->h;
		if (y > max_y)
		{
			max_y = y;
		}
	}
	auto first_base_component = map_entities[0].get().get<BaseComponent>();
	max_x /= first_base_component->w;
	max_y /= first_base_component->h;

	generate::models::Base64_Tilemap map{ max_x,  max_y };
	
	for (auto entity : map_entities)
	{
		auto base_component = entity.get().get<BaseComponent>();
		auto tile_component = entity.get().get<TileComponent>();
		int x = base_component->location.x / base_component->w;
		int y = base_component->location.y / base_component->h;
		map(y, x) = tile_component->character;
	}
	
	return map.get_tile_string();
}
