#ifndef _FOGOFWARSYSTEM_H
#define _FOGOFWARSYSTEM_H
#include "ECS/System.h"
#include "Engine/MultimediaManager.h"

class FogOfWarSystem : public memecity::engine::ecs::System
{
private:
	memecity::engine::MultimediaManager* multimedia_manager;

public:
	FogOfWarSystem(memecity::engine::MultimediaManager& multimedia_manager)
		: multimedia_manager(&multimedia_manager) {}

	void run(memecity::engine::ecs::EntityManager& em) const override;
};
#endif