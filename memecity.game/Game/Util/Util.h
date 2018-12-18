#ifndef MEMECITY_GAME_UTIL_H
#define MEMECITY_GAME_UTIL_H
#include <ECS.h>
#include <Engine\Util.h>
#include "..\Components.h"

const char* on_tile(memecity::engine::ecs::EntityManager& em, const memecity::engine::ecs::Entity& entity) {
	auto entity_base = entity.get<BaseComponent>();
	return em.query_entities("tile")
		.first([&](const auto& e){
		auto tile_base = e.get<BaseComponent>();
		return intersects(Rectangle{entity_base->location.x, entity_base->location.y, entity_base->w, entity_base->h}, 
			Rectangle{ tile_base->location.x, tile_base->location.y, tile_base->w, tile_base->h });
		})->get<TileComponent>()->type;
}

#endif
