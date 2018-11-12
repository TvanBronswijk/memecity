#include "MoveSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "PlayerComponent.h"
#include "MoveSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "AnimatedTexture.h"

using namespace ecs;

void MoveSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component<VelocityComponent>();

	for (auto entity : entities)
	{
		auto current_position = entity.get().get<PositionComponent>();
		auto current_velocity_component = entity.get().get<VelocityComponent>();
		auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();

		if (entity.get().id != player_component.entity.id) {

			auto drawable = current_velocity_component->entity.get<DrawableComponent>();

			if (drawable != nullptr) {
				auto& animated_charater = dynamic_cast<AnimatedTexture&>(drawable->get_texture());
				animated_charater.update();
				if (current_velocity_component->x == 0 && current_velocity_component->y == 0) {
					animated_charater.set_direction(AnimatedTexture::Direction::idle);
				}
				else if (current_velocity_component->y > 0)
				{
					animated_charater.set_direction(AnimatedTexture::Direction::up);
				}
				else if (current_velocity_component->y < 0)
				{
					animated_charater.set_direction(AnimatedTexture::Direction::down);
				}
				else if (current_velocity_component->x < 0)
				{
					animated_charater.set_direction(AnimatedTexture::Direction::left);
				}
				else if (current_velocity_component->x > 0)
				{
					animated_charater.set_direction(AnimatedTexture::Direction::right);
				}

				animated_charater.translate(Vector2(current_velocity_component->x, (current_velocity_component->y - current_velocity_component->y * 2))); //TODO: x and y = *2

			}
		}

		if (current_velocity_component->x != 0)
		{
			current_position->x += current_velocity_component->x;
			current_position->diffx = current_velocity_component->x;
			current_velocity_component->x = 0;
		}
		else
		{
			current_position->diffx = 0;
		}

		if (current_velocity_component->y != 0)
		{
			current_position->y += current_velocity_component->y;
			current_position->diffy = current_velocity_component->y;
			current_velocity_component->y = 0;
		}
		else
		{
			current_position->diffy = 0;
		}
	}
}

void MoveSystem::on_collision(EntityManager& em, ColliderEventArgs ea)
{
	auto position_target = ea.target.get<PositionComponent>();
	auto position = ea.source.get<PositionComponent>();
	auto velocity = ea.source.get<VelocityComponent>();

	if (velocity != nullptr)
	{
		if (position_target->x > position->x)
		{
			position->x -= 5;
			position->diffx = -5;
		}
		else if (position_target->x < position->x)
		{
			position->x += 5;
			position->diffx = 5;
		}
		if (position_target->y > position->y)
		{
			position->y -= 5;
			position->diffy = -5;
		}
		else if (position_target->y < position->y)
		{
			position->y += 5;
			position->diffy = 5;
		}
	}
}
