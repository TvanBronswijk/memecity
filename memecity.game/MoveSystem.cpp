#include "MoveSystem.h"
#include "VelocityComponent.h"

void MoveSystem::run(EntityManager& em)
{
	auto components = em.get_components_of_type("VelocityComponent");

	for (auto velocity_component : components)
	{
	}
}
