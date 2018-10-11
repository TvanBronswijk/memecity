#include "DrawSystem.h"

DrawSystem::DrawSystem(std::weak_ptr<MultimediaManager> multimedia_manager)
{
	this->multimedia_manager = multimedia_manager;
}


void DrawSystem::run(EntityManager& em)
{
	auto graphics_components = std::vector<DrawableComponent>();
	multimedia_manager.lock()->clear_graphics();
	for (DrawableComponent component : graphics_components)
	{
		component.texture->render();
	}
	multimedia_manager.lock()->render_graphics();
}

std::string DrawSystem::get_type()
{
	return  "GraphicSystem";
}
