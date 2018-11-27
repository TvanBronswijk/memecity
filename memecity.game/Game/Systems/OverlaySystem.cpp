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

	//hud WIP

	//black box
	auto black_box_texture = multimedia_manager.get_texture("big_black.bmp", 0, 0, multimedia_manager.get_screen_width(), 90);
	textures.push_back(black_box_texture.get());

	//health
	/*std::string hp = "HP: ";
	auto player_healt_component = player_component.get<HealthComponent>();
	hp += std::to_string(player_healt_component->health);
	auto target_health_texture = multimedia_manager.get_text_texture(hp, "Minecraftia-Regular.ttf", 10, { 34,139,34 });
	target_health_texture->set_position({ 0, -20 });*/

	//end hud




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
			multimedia_manager.render_texture(*text_texture);
		}
		else
		{
			multimedia_manager.render_texture(*texture);
		}
	}
}
