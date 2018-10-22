#ifndef _DRAWSYSTEM_H
#define _DRAWSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include <vector>
#include "MultimediaManager.h"
#include "DrawableComponent.h"
#include "../memecity.engine.ecs/EntityManager.h"

class DrawSystem : public System
{
	static std::string SYSTEM_TYPE;

private:
	std::weak_ptr<MultimediaManager> multimedia_manager;
public:
	DrawSystem(std::weak_ptr<MultimediaManager> multimedia_manager);
	std::string get_type() override;
	void run(EntityManager& em) override;
};

#endif

