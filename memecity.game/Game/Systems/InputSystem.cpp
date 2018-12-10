#include "InputSystem.h"
#include "..\Components.h"
#include "..\States.h"
#include "..\Input.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

bool InputSystem::check_collision(BaseComponent& l, BaseComponent& r , int range) const{
	return ((l.location.x + range) >= r.location.x && (l.location.x - range) <= r.location.x)
		&& ((l.location.y + range) >= r.location.y && (l.location.y - range) <= r.location.y);
}

void InputSystem::run(EntityManager& em) const
{
	auto& input_manager = _context->get_input_manager();
	auto& state_manager = _context->get_state_manager();

	auto players = em.get_entities_with_component<PlayerComponent>();
	for (const Entity& player : players)
	{
		float speed = 5.0f;
		auto velocity_component = player.get<VelocityComponent>();
		if (input_manager.is_down(input::UP))
		{
			velocity_component->y -= speed;
		}
		else if (input_manager.is_down(input::DOWN))
		{
			velocity_component->y += speed;
		}
		if (input_manager.is_down(input::LEFT))
		{
			velocity_component->x -= speed;
		}
		else if (input_manager.is_down(input::RIGHT))
		{
			velocity_component->x += speed;
		}

		if (input_manager.is_pressed(input::INTERACTION))
		{
			auto npcs = em.get_entities_with_component<AIComponent>();
			for (const Entity& npc : npcs) {
				if(check_collision(*player.get<BaseComponent>(), *npc.get<BaseComponent>(), 30)){
					interaction_event.fire(em, { npc });
				}
			}
			auto quest_npcs = em.get_entities_with_component<QuestAIComponent>();
			for (const Entity& npc : quest_npcs) {
				if (check_collision(*player.get<BaseComponent>(), *npc.get<BaseComponent>(), 30)) {
					interaction_event.fire(em, { npc });
				}
			}
		}

		if (input_manager.is_pressed(input::ATTACK)) {
			const auto animation_component = player.get<AnimationComponent>();
			if (animation_component)
			{
				animation_component->current_state = AnimationComponent::AnimationState::fighting;
			}

			auto npcs = em.get_entities_with_component<AIComponent>();
			for (const Entity& npc : npcs) {
				if (check_collision(*player.get<BaseComponent>(), *npc.get<BaseComponent>(), 30)) {
					attack_event.fire(em, {player, npc });
				}
			}
		}
		if (input_manager.is_pressed(input::ESCAPE)) {
			state_manager.create_state<PauseMenuState>(*_context);
		}
		if (input_manager.is_pressed(input::N)) {
			state_manager.create_state<StoryState>(*_context, entity.get<PlayerComponent>()->_stories);
		}
	}
}

