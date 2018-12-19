#include "AnimationSystem.h"
#include <Engine\Textures.h>
#include "../Event/MoveEventArgs.h"
#include "../../Assets.h"
#include "../States/GameOverState.h"

using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void AnimationSystem::run(EntityManager& em, float dt) const {}

void AnimationSystem::change_texture(BaseComponent& base_component, std::unique_ptr<Texture> texture) const
{
	auto& current_texture = base_component.get_texture();
	if (current_texture.get_filename() != texture->get_filename())
	{
		texture->set_position(current_texture.get_position());
		base_component.set_texture(std::move(texture));
	}
}

void AnimationSystem::on_move(EntityManager& em, MoveEventArgs args)
{
	const auto animation_component = args.source.get<AnimationComponent>();
	const auto current_velocity = args.source.get<VelocityComponent>();

	auto base_component = args.source.get<BaseComponent>();
	auto& texture = base_component->get_texture();
	auto animated_texture = dynamic_cast<AnimatedTexture*>(&texture);
	
	if (animated_texture && current_velocity)
	{
		animated_texture->update(_context->get_timer().get_delta_time());

		switch (animation_component->current_state)
		{
			case AnimationComponent::AnimationState::fighting:
				animated_texture->column(4);
				if (animated_texture->is_last())
				{
					animation_component->current_state = AnimationComponent::AnimationState::idle;
				}
				break;
			
			case AnimationComponent::AnimationState::dying:
				animated_texture->column(5);
				if (animated_texture->is_last())
				{
					animated_texture->row(animated_texture->frame_count() - 1);
					if (animation_component->is_finished())
					{
						if (animation_component->entity().has<PlayerComponent>())
						{
							auto exp = animation_component->entity().get<ExpComponent>()->exp;
							_context->get_state_manager().create_state<GameOverState>(*_context, exp);
						}
					}
					else
					{
						animation_component->animation_timer += _context->get_timer().get_delta_time();
					}
				}
				break;
			
			default:
				animated_texture->set_state(args.state);
				break;
		}
	}
}

void AnimationSystem::on_death(EntityManager& em, DeathEventArgs args)
{
	args.target.get<AnimationComponent>()->current_state = AnimationComponent::AnimationState::dying;
}