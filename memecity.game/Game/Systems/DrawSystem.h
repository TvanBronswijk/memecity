#ifndef _DRAWSYSTEM_H
#define _DRAWSYSTEM_H
#include <Engine\MultimediaManager.h>
#include <ECS.h>

class DrawSystem : public memecity::engine::ecs::System
{
private:
	memecity::engine::MultimediaManager& multimedia_manager;

public:
	DrawSystem(memecity::engine::MultimediaManager& multimedia_manager)
		: multimedia_manager(multimedia_manager) {}

	void run(memecity::engine::ecs::EntityManager& em) const override;
};
#endif

