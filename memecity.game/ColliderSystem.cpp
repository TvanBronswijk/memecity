#include "ColliderSystem.h"

std::string ColliderSystem::SYSTEM_TYPE = "ColliderSystem";

std::string ColliderSystem::get_type()
{
	return SYSTEM_TYPE;
}

ColliderSystem::ColliderSystem(ColliderEvent* collider_event)
{
	this->collider_event = collider_event;
}

ColliderSystem::~ColliderSystem()
{
	delete collider_event;
}

void ColliderSystem::run(EntityManager& em)
{
	auto components = em.get_components_of_type(ColliderComponent::COMPONENT_TYPE);

	for (auto collider_component : components)
	{
		const auto current_collider_component =
			dynamic_cast<ColliderComponent*>(em.get_component_of_entity(collider_component->entity_id, ColliderComponent::COMPONENT_TYPE));

		auto all_collider_components = em.get_components_of_type(ColliderComponent::COMPONENT_TYPE);

		for (auto other_collider_component : all_collider_components)
		{
			const auto current_other_collider_component = dynamic_cast<ColliderComponent*>(em.get_component_of_entity(other_collider_component->entity_id, ColliderComponent::COMPONENT_TYPE));

			if (current_collider_component->entity_id != current_other_collider_component->entity_id)
			{
				if (current_collider_component->x2 > current_other_collider_component->x &&
					current_other_collider_component->x2 > current_collider_component->x &&
					current_collider_component->y2 > current_other_collider_component->y &&
					current_other_collider_component->y2 > current_collider_component->y)
				{
					collider_event->fire(em, ColliderEventArgs(current_collider_component->entity_id,
						current_other_collider_component->entity_id));
				}
			}
		}
	}
}

void ColliderSystem::run(EntityManager & em, const EventArgs & e)
{
}