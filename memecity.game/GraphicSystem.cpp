#include "GraphicSystem.h"

GraphicSystem::GraphicSystem(std::weak_ptr<MultimediaManager> multimedia_manager)
{
	this->multimedia_manager = multimedia_manager;
}


void GraphicSystem::run(EntityManager& em)
{
	auto components = std::vector<Component>();
	auto graphics_components = std::vector<GraphicComponent>(components.begin(), components.end());
	multimedia_manager.lock()->clear_graphics();
	for (GraphicComponent component : graphics_components)
	{
		component.texture->render();
	}
	multimedia_manager.lock()->render_graphics();
}

std::string GraphicSystem::get_type()
{
	return  "GraphicSystem";
}
