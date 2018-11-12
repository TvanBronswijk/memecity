#include "AnimationSystem.h"
#include "AnimatedTexture.h"
#include "PositionComponent.h"
#include "AnimationComponent.h"
#include "DrawableComponent.h"
using namespace ecs;

void AnimationSystem::run(ecs::EntityManager& em) const
{
	auto animation_components = em.get_components_of_type<AnimationComponent>();
	for (auto& animation_component : animation_components)
	{	

		const auto& current_position = animation_component.get().entity.get<PositionComponent>();

		auto& texture = animation_component.get().entity.get<DrawableComponent>()->get_texture();

		// Cast from base class (Texture) to derived class (AnimatedTexture)
		auto animated_texture = dynamic_cast<AnimatedTexture*>(&texture);

		if (animated_texture != nullptr && current_position != nullptr)
		{
			animated_texture->update();
			animated_texture->set_direction(AnimatedTexture::Direction::idle);

			if (animation_component.get().is_fighting)
			{
				std::cout << "IS FIGHTING" << std::endl;
				animation_component.get().is_fighting = false;
			}
			if (current_position->diffx > 0)
			{
				animated_texture->set_direction(AnimatedTexture::Direction::right);
				return;
			}
			if (current_position->diffx < 0)
			{
				animated_texture->set_direction(AnimatedTexture::Direction::left);
				return;
			}
			if (current_position->diffy > 0)
			{
				animated_texture->set_direction(AnimatedTexture::Direction::up);
				return;
			}
			if (current_position->diffy < 0)
			{
				animated_texture->set_direction(AnimatedTexture::Direction::down);
				return;
			}
		}
	}
}
