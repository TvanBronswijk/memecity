#ifndef _COLLIDERSYSTEM_H
#define  _COLLIDERSYSTEM_H
#include "ColliderEventArgs.h"
#include "ColliderComponent.h"
#include "ECS.h"

class ColliderSystem : public ecs::System
{
public:
	ColliderSystem() = default;
	void run(ecs::EntityManager& em) const override;
	ecs::eventing::Event<ColliderEventArgs> collider_event;
};

#endif