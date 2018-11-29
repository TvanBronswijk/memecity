#ifndef _COLLIDERSYSTEM_H
#define  _COLLIDERSYSTEM_H
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\ColliderEventArgs.h"
#include "QuadTree.h"

class ColliderSystem : public memecity::engine::ecs::System
{
private:
	QuadTree& _quad_tree;

public:
	ColliderSystem(QuadTree& quad_tree) : _quad_tree(quad_tree) {}
	void run(memecity::engine::ecs::EntityManager& em) const override;
	memecity::engine::ecs::eventing::Event<ColliderEventArgs> collider_event;
};

#endif
