#ifndef _COLLIDERSYSTEM_H
#define _COLLIDERSYSTEM_H

#include <ECS.h>
#include <Engine\Collision.h>
#include "..\Components.h"
#include "..\Event\ColliderEventArgs.h"

class ColliderSystem : public memecity::engine::ecs::System
{
private:
	float _map_width, _map_height;
public:
	ColliderSystem(int map_width, int map_height)
		: _map_width(map_width), _map_height(map_height) {}
	void run(memecity::engine::ecs::EntityManager& em) const override;
	memecity::engine::ecs::eventing::Event<ColliderEventArgs> collider_event;
};

#endif
