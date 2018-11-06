#include "AnimationSystem.h"

std::string const AnimationSystem::SYSTEM_TYPE = "AnimationSystem";

std::string AnimationSystem::get_type()
{
	return SYSTEM_TYPE;
}

void AnimationSystem::run(EntityManager& em)
{
	auto animation_components = em.get_components_of_type(AnimationComponent::COMPONENT_TYPE);

	for (auto animation_component : animation_components)
	{	
		const auto current_position = dynamic_cast<PositionComponent*>(em.get_component_of_entity(animation_component->entity_id, PositionComponent::COMPONENT_TYPE));
		shared_ptr<Texture> texture = dynamic_cast<DrawableComponent*>(em.get_component_of_entity(animation_component->entity_id, DrawableComponent::COMPONENT_TYPE))->texture;
		shared_ptr<AnimatedTexture> animated_texture = static_pointer_cast<AnimatedTexture>(texture);

		if (animated_texture != nullptr && current_position != nullptr)
		{
			animated_texture->update();
			animated_texture->set_direction(AnimatedTexture::Direction::idle);

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

void AnimationSystem::run(EntityManager& em, EventArgs& e)
{
}
