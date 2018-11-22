#include "OverlaySystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::ecs;

void OverlaySystem::run(EntityManager& em) const
{
	auto& player_component = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_position_component = player_component.get<PositionComponent>();

	auto Health_overlay_components = em.get_components_of_type<HealthComponent>();
	auto Interaction_overlay_components = em.get_components_of_type<InteractionComponent>();

	std::vector<memecity::engine::texture::Texture*> textures;

	for (std::vector<std::reference_wrapper<HealthComponent>>::iterator it =Health_overlay_components.begin(); it != Health_overlay_components.end(); ++it) {
		textures.push_back(&it->get().get_texture());
	}
	for (std::vector<std::reference_wrapper<InteractionComponent>>::iterator it = Interaction_overlay_components.begin(); it != Interaction_overlay_components.end(); ++it) {
		textures.push_back(&it->get().get_texture());
	}

	for (auto texture : textures)
	{
		
		texture->translate({ (player_position_component->diffx*-1) , player_position_component->diffy });
		
		auto text_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(texture);
		if (text_texture)
		{
			multimedia_manager.render_text_texture(*text_texture);
		}
		else
		{
			multimedia_manager.render_texture(*texture);
		}
	}
}