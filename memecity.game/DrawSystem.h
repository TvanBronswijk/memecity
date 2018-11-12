#ifndef _DRAWSYSTEM_H
#define _DRAWSYSTEM_H
#include "ECS/System.h"
#include "MultimediaManager.h"

class DrawSystem : public ecs::System
{
private:
	MultimediaManager& multimedia_manager;

public:
	DrawSystem(MultimediaManager& multimedia_manager)
		: multimedia_manager(multimedia_manager) {}

	void run(ecs::EntityManager& em) const override;
};
#endif

