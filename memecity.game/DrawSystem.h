#ifndef _DRAWSYSTEM_H
#define _DRAWSYSTEM_H
#include "../memecity.engine.ecs/ECS.h"
#include <vector>
#include "MultimediaManager.h"
#include "DrawableComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"

class DrawSystem : public ecs::System
{
private:
	MultimediaManager &multimedia_manager;
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	DrawSystem(MultimediaManager& multimedia_manager);
	void run(ecs::EntityManager& em) const override;
	ecs::system_typetoken get_type_token() const override { return DrawSystem::SYSTEM_TYPE; }
};

#endif

