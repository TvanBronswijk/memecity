#include "FogOfWarSystem.h"
#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/DrawableComponent.h"
#include "../Components/StatsComponent.h"

void FogOfWarSystem::run(memecity::engine::ecs::EntityManager& em) const
{
	auto components = em.query<DrawableComponent>()
		.where([&](DrawableComponent& c) {
		auto render_rect = c.get_texture().get_render_rect();
		return render_rect.x > -100
			&& render_rect.x < multimedia_manager->get_screen_width() + 100
			&& render_rect.y > -100
			&& render_rect.y < multimedia_manager->get_screen_height() + 100;
	}).to_vector();

	auto& player = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_tex_position = player.get<DrawableComponent>()->get_texture().get_position();
	auto player_perception = player.get<StatsComponent>()->perception;
	auto perception_pixels = player_perception * 255;

	for (DrawableComponent& component : components)
	{
		auto component_tex_position = component.get_texture().get_position();
		
		auto x_distance = abs(player_tex_position.x - component_tex_position.x);
		auto y_distance = abs(player_tex_position.y - component_tex_position.y);
		auto distance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));

		auto alpha = (1.0f / perception_pixels) * pow(distance, logf(10.0f / perception_pixels *distance ));
		if (alpha > 255)
		{
			alpha = 255;
		}

		auto rectangle = component.get_texture().get_render_rect();

		rectangle.w = rectangle.h = alpha == 255 ? 64.5f : 64.0f;

		multimedia_manager->render_rect(rectangle, true, { 0,0,0, static_cast<uint8_t>(alpha)});
	}
}
