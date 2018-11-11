#include "AnimationSystem.h"
#include "AnimatedTexture.h"
#include "PositionComponent.h"
#include "AnimationComponent.h"
#include "DrawableComponent.h"
using namespace ecs;

system_typetoken AnimationSystem::SYSTEM_TYPE = "AnimationSystem";

void AnimationSystem::run(ecs::EntityManager& em) const
{
	auto animation_components = em.get_components_of_type<AnimationComponent>(AnimationComponent::COMPONENT_TYPE);
	for (auto animation_component : animation_components)
	{	
		const auto current_position = em.get_component_of_entity<PositionComponent>(animation_component.get().entity, PositionComponent::COMPONENT_TYPE);
		auto texture = em.get_component_of_entity<DrawableComponent>(animation_component.get().entity, DrawableComponent::COMPONENT_TYPE)->texture.get();

		// Cast from base class (Texture) to derived class (AnimatedTexture)
		auto animated_texture = dynamic_cast<AnimatedTexture*>(&*texture);

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
