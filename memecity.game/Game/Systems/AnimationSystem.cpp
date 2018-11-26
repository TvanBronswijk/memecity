#include "AnimationSystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void AnimationSystem::run(EntityManager& em) const
{
	auto animation_components = em.get_components_of_type<AnimationComponent>();
	for (auto& animation_component : animation_components)
	{	
		const auto& current_position = animation_component.get().entity().get<PositionComponent>();
		const auto& fighting_component = animation_component.get().entity().get<FightingComponent>();

		auto& texture = animation_component.get().entity().get<DrawableComponent>()->get_texture();

		// Cast from base class (Texture) to derived class (AnimatedTexture)
		auto animated_texture = dynamic_cast<AnimatedTexture*>(&texture);

		if (animated_texture != nullptr && current_position != nullptr)
		{
			animated_texture->update();
			animated_texture->set_direction(AnimatedTexture::Direction::idle);

			if (fighting_component && fighting_component->is_fighting)
			{
				animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::horizontal);
				fighting_component->is_fighting = false;
			}
			else
			{
				animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::vertical);

				if (current_position->diffx > 0)
				{
					animated_texture->set_direction(AnimatedTexture::Direction::right);
				}
				else if (current_position->diffx < 0)
				{
					animated_texture->set_direction(AnimatedTexture::Direction::left);
				}
				else if (current_position->diffy > 0)
				{
					animated_texture->set_direction(AnimatedTexture::Direction::up);
				}
				else if (current_position->diffy < 0)
				{
					animated_texture->set_direction(AnimatedTexture::Direction::down);
				}
			}
		}
	}
}
