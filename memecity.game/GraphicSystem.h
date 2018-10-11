#ifndef _GRAPHICSSYSTEM_H
#define _GRAPHICSSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "GraphicComponent.h"
#include <vector>
#include "MultimediaManager.h"

class GraphicSystem : public System
{
private:
	std::weak_ptr<MultimediaManager> multimedia_manager;
public:
	GraphicSystem(std::weak_ptr<MultimediaManager> multimedia_manager);
	std::string get_type() override;
	void run(EntityManager& em) override;
};

#endif

