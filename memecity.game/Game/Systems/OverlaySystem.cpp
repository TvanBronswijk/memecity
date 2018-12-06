#include "OverlaySystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::ecs;

void OverlaySystem::run(EntityManager& em) const
{
	auto health_overlay_components = em.get_components_of_type<HealthComponent>();
	auto interaction_overlay_components = em.get_components_of_type<InteractionComponent>();

	for (HealthComponent& item : health_overlay_components)
	{
		multimedia_manager.render_text(item.get_texture());
	}
	for (InteractionComponent& item : interaction_overlay_components)
	{
		multimedia_manager.render_text(item.get_texture());
	}
}
