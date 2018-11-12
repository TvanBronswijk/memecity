#ifndef _MOVESYSTEM_H
#define  _MOVESYSTEM_H
#include <ECS.h>
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"
#include "../memecity.engine/AnimatedCharacter.h"
#include "PlayerComponent.h"


class MoveSystem : public ecs::System
{
public:
	void run(ecs::EntityManager& em) const override;
};
#endif
