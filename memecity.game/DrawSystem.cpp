#include "DrawSystem.h"

std::string DrawSystem::SYSTEM_TYPE = "DrawSystem";

DrawSystem::DrawSystem(std::weak_ptr<MultimediaManager> multimedia_manager)
{
	this->multimedia_manager = multimedia_manager;
}


void DrawSystem::run(EntityManager& em)
{
	auto components = em.get_components_of_type(DrawableComponent::COMPONENT_TYPE);

	multimedia_manager.lock()->clear_graphics();
	for (Component* component : components)
	{
		dynamic_cast<DrawableComponent*>(component)->texture->render();
	}
	multimedia_manager.lock()->render_graphics();
}

std::string DrawSystem::get_type()
{
	return SYSTEM_TYPE;
}


void DrawSystem::run(EntityManager& em, EventArgs& e)
{
}

