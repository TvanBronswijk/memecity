#include "ColliderSystem.h"
#include "ColliderComponent.h"

std::string ColliderSystem::SYSTEM_TYPE = "ColliderSystem";

std::string ColliderSystem::get_type()
{
	return SYSTEM_TYPE;
}

bool ColliderSystem::is_on_event(Event* e)
{
	return false;
}

void ColliderSystem::run(EntityManager& em)
{
	auto components = em.get_components_of_type(ColliderComponent::COMPONENT_TYPE);

	for (auto collider_component : components)
	{
		auto current_collider_component =
			dynamic_cast<ColliderComponent*>(em.get_component_of_entity(collider_component->entity_id, ColliderComponent::COMPONENT_TYPE));

		auto texture_position = current_collider_component->texture->get_position();

		texture_position.x = 0.0f;
		texture_position.y = 0.0f;
	}
}


void ColliderSystem::run(EntityManager& em, Event* e)
{

}
