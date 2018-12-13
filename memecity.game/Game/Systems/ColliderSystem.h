#ifndef _COLLIDERSYSTEM_H
#define _COLLIDERSYSTEM_H
#include <ECS.h>
#include <Engine\Collision.h>
#include "..\Components.h"
#include "..\Event\ColliderEventArgs.h"

class ColliderSystem : public memecity::engine::ecs::System
{
private:
	mutable QuadTree quad_tree;
	float _map_width, _map_height;
public:
	ColliderSystem(float map_width, float map_height)
		: _map_width(map_width), _map_height(map_height), quad_tree(4, { 0.0f, 0.0f, map_width, map_height }) {}
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
	memecity::engine::ecs::eventing::Event<ColliderEventArgs> collider_event;
};

#endif
