#ifndef _DRAWSYSTEM_H
#define _DRAWSYSTEM_H
#include <ECS.h>
#include "MultimediaManager.h"

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

