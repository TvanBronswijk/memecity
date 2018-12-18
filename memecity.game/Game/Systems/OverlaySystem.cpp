#include "OverlaySystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::ecs;

void OverlaySystem::run(EntityManager& em, float dt) const
{
	auto health_overlay_components = em.get_components_of_type<HealthComponent>();
	auto interaction_overlay_components = em.get_components_of_type<InteractionComponent>();
	auto AI_name_overlay_components = em.get_components_of_type<AIComponent>();
	auto AI_quest_name_overlay_components = em.get_components_of_type<QuestAIComponent>();

	int buh = 1;
	for (HealthComponent& item : health_overlay_components)
	{
		if (item.texture != nullptr && item.texture->get_parent() != nullptr && item.texture->get_parent()->get_position().x == 640)
		{
			//auto parent = static_cast<memecity::engine::texture::Texture*>(item.texture->get_parent());
			//parent->translate({ -9000, -9000 });
			//multimedia_manager.render_texture(*parent);
			std::cout << "BLEH HealthComponent"<< buh<<"\n";
			buh++;
		}
		if (item.texture != nullptr)
		multimedia_manager.render_text(item.get_texture());
	}
	for (InteractionComponent& item : interaction_overlay_components)
	{
		if (item.texture != nullptr && item.texture->get_parent() != nullptr && item.texture->get_parent()->get_position().x == 640)
		{
			std::cout << "BLEH InteractionComponent\n";
		}
		multimedia_manager.render_text(item.get_texture());
	}
	for (AIComponent& item : AI_name_overlay_components)
	{
		if (item.texture != nullptr && item.texture->get_parent() != nullptr && item.texture->get_parent()->get_position().x == 640)
		{
			std::cout << "BLEH AIComponent\n";
		}
		multimedia_manager.render_text(item.get_texture());
	}
	for (QuestAIComponent& item : AI_quest_name_overlay_components)
	{
		if (item.texture != nullptr && item.texture->get_parent() != nullptr && item.texture->get_parent()->get_position().x == 640)
		{
			std::cout << "BLEH QuestAIComponent\n";
		}
		multimedia_manager.render_text(item.get_texture());
	}
}
