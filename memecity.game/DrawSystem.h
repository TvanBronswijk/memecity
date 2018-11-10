#ifndef _DRAWSYSTEM_H
#define _DRAWSYSTEM_H
#include <ECS.h>
#include "MultimediaManager.h"
class DrawSystem : public ecs::System
{
public:
	void run(ecs::EntityManager& em) const override;
};
#endif

