#ifndef _COLLIDERSYSTEM_H
#define  _COLLIDERSYSTEM_H
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\ColliderEventArgs.h"

class ColliderSystem : public memecity::engine::ecs::System
{
public:
	ColliderSystem() = default;
	void run(memecity::engine::ecs::EntityManager& em) const override;
	memecity::engine::ecs::eventing::Event<ColliderEventArgs> collider_event;
};

#endif
