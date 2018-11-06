#ifndef _MOVESYSTEM_H
#define  _MOVESYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"


class MoveSystem : public ecs::System
{
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	MoveSystem();
	void run(ecs::EntityManager& em) override;
	ecs::system_typetoken get_type_token() override { return MoveSystem::SYSTEM_TYPE; }
};

#endif