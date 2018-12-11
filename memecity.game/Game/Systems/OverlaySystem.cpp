#include "OverlaySystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::ecs;

void OverlaySystem::run(EntityManager& em) const
{
	auto health_overlay_components = em.get_components_of_type<HealthComponent>();
	auto interaction_overlay_components = em.get_components_of_type<InteractionComponent>();
	auto AI_name_overlay_components = em.get_components_of_type<AIComponent>();
	auto AI_quest_name_overlay_components = em.get_components_of_type<QuestAIComponent>();

	for (HealthComponent& item : health_overlay_components)
	{
		if (item.texture != nullptr)
		multimedia_manager.render_text(item.get_texture());
	}
	for (InteractionComponent& item : interaction_overlay_components)
	{
		multimedia_manager.render_text(item.get_texture());
	}
	for (AIComponent& item : AI_name_overlay_components)
	{
		multimedia_manager.render_text(item.get_texture());
	}
	for (QuestAIComponent& item : AI_quest_name_overlay_components)
	{
		multimedia_manager.render_text(item.get_texture());
	}
}
