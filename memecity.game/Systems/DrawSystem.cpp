#include "DrawSystem.h"
#include <Engine\Textures.h>
#include "../Components/VelocityComponent.h"

using namespace memecity::engine::ecs;

void DrawSystem::run(EntityManager& em) const
{
	auto& player_component = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_position_component = player_component.get<PositionComponent>();

	auto drawable_components = em.get_components_of_type<DrawableComponent>();
	
	for (DrawableComponent& drawable_component : drawable_components)
	{	
		auto& tex = drawable_component.get_texture();
		//bool found = drawable_component.entity.has<VelocityComponent>();
		if (drawable_component.entity != player_component)
		{
			tex.translate({ (player_position_component->diffx*-1) , player_position_component->diffy });
		}

		auto text_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&tex);
		if (text_texture)
		{
			multimedia_manager.render_text_texture(*text_texture);
		}
		else
		{
			multimedia_manager.render_texture(tex);
		}
	}
}


//if (entity.get().id != player_component.entity.id) {
//
//	auto drawable = current_velocity_component->entity.get<DrawableComponent>();
//
//	if (drawable != nullptr) {
//		auto& animated_charater = dynamic_cast<AnimatedTexture&>(drawable->get_texture());
//		animated_charater.update();
//		if (current_velocity_component->x == 0 && current_velocity_component->y == 0) {
//			animated_charater.set_direction(AnimatedTexture::Direction::idle);
//		}
//		else if (current_velocity_component->y > 0)
//		{
//			animated_charater.set_direction(AnimatedTexture::Direction::up);
//		}
//		else if (current_velocity_component->y < 0)
//		{
//			animated_charater.set_direction(AnimatedTexture::Direction::down);
//		}
//		else if (current_velocity_component->x < 0)
//		{
//			animated_charater.set_direction(AnimatedTexture::Direction::left);
//		}
//		else if (current_velocity_component->x > 0)
//		{
//			animated_charater.set_direction(AnimatedTexture::Direction::right);
//		}
//
//		//animated_charater.translate(Vector2(current_velocity_component->x, (current_velocity_component->y - current_velocity_component->y * 2))); //TODO: x and y = *2
//		animated_charater.translate(Vector2((current_velocity_component->x * current_velocity_component->x) / 1.5, current_velocity_component->y));
//	}
//}
