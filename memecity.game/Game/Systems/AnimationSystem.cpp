#include "AnimationSystem.h"
#include <Engine\Textures.h>
#include "../Event/MoveEventArgs.h"
#include "../../Assets.h"

using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void AnimationSystem::run(EntityManager& em) const
{
}

void AnimationSystem::set_texture(BaseComponent &base_component, std::unique_ptr<Texture> texture) const
{
	auto current_texture = base_component.get_texture();
	if (current_texture.get_filename() != texture->get_filename())
	{
		base_component.set_texture(std::move(texture));
		base_component.get_texture().set_position(current_texture.get_position());
	}
}

void AnimationSystem::on_move(EntityManager& em, MoveEventArgs args)
{
	const auto animation_component = args.source.get<AnimationComponent>();
	const auto& current_velocity = args.source.get<VelocityComponent>();

	auto base_component = args.source.get<BaseComponent>();
	auto& texture = base_component->get_texture();

	// Cast from base class (Texture) to derived class (AnimatedTexture)
	auto animated_texture = dynamic_cast<AnimatedTexture*>(&texture);

	if (animated_texture != nullptr && current_velocity != nullptr)
	{
		animated_texture->update(_context->get_timer().get_delta_time());
		animated_texture->set_state(AnimatedTexture::AnimationState::idle);

		switch (animation_component->current_state)
		{
			case AnimationComponent::AnimationState::fighting:
				set_texture(*base_component, _context->get_multimedia_manager().get_texture(assets::spritesheets::HUMAN_FIGHTING_1, 0, 0, 48, 48, 4, 0.25f, AnimatedTexture::AnimationDirection::horizontal));
				if (animated_texture->column() >= 3)
				{
					animation_component->current_state = AnimationComponent::AnimationState::idle;
				}
				break;
			
			case AnimationComponent::AnimationState::dying:
				set_texture(*base_component, _context->get_multimedia_manager().get_texture(assets::spritesheets::HUMAN_DYING_1, 0, 0, 48, 48, 4, 0.25f, AnimatedTexture::AnimationDirection::horizontal));
				break;
			
			default:
				set_texture(*base_component, _context->get_multimedia_manager().get_texture(assets::spritesheets::HUMAN_MALE_1, 0, 0, 48, 48, 4, 0.25f, AnimatedTexture::AnimationDirection::vertical));
				animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::vertical);
				animated_texture->set_state(args.state);
				break;
		}
	}
}

