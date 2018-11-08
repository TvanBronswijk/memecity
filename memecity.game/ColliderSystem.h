#ifndef _COLLIDERSYSTEM_H
#define  _COLLIDERSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "ColliderEventArgs.h"
#include "ColliderComponent.h"
#include "Event.h"


class ColliderSystem : public ecs::System
{
public:
	ColliderSystem() = default;
	static ecs::system_typetoken SYSTEM_TYPE;
	void run(ecs::EntityManager& em) const override;
	ecs::system_typetoken get_type_token() const override { return ColliderSystem::SYSTEM_TYPE; }
	ecs::eventing::Event<ColliderEventArgs> collider_event;
};

#endif