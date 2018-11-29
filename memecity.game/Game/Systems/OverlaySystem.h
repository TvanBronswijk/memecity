#ifndef _OVERLAYSYSTEM_H
#define _OVERLAYSYSTEM_H
#include <Engine\MultimediaManager.h>
#include <ECS.h>
#include "../Components.h"

class OverlaySystem : public memecity::engine::ecs::System
{
private:
	memecity::engine::MultimediaManager& multimedia_manager;

public:
	OverlaySystem(memecity::engine::MultimediaManager& multimedia_manager)
		: multimedia_manager(multimedia_manager) {}

	void run(memecity::engine::ecs::EntityManager& em) const override;
};
#endif


