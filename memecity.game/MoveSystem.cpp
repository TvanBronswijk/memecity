#include "MoveSystem.h"

using namespace ecs;

system_typetoken MoveSystem::SYSTEM_TYPE = "MoveSystem";

MoveSystem::MoveSystem() : System() 
{

}

void MoveSystem::run(EntityManager& em) const
{
	auto player_component = em.get_components_of_type<PlayerComponent>(PlayerComponent::COMPONENT_TYPE)[0];

	auto components = em.get_components_of_type<VelocityComponent>(VelocityComponent::COMPONENT_TYPE);

	for (auto velocity_component : components)
	{
		auto current_position =	em.get_component_of_entity<PositionComponent>(velocity_component.get().entity, PositionComponent::COMPONENT_TYPE);

		if (velocity_component.get().entity.id != player_component.get().entity.id) {
		
			auto drawable = em.get_component_of_entity<DrawableComponent>(velocity_component.get().entity, DrawableComponent::COMPONENT_TYPE);

			if (drawable != nullptr) {
				auto animated_charater = std::dynamic_pointer_cast<AnimatedCharacter>(drawable->texture);
				animated_charater->update();
				if (velocity_component.get().x == 0 && velocity_component.get().y == 0) {
					animated_charater->set_walking_direction(AnimatedCharacter::idle);
				}
				else if (velocity_component.get().y > 0)
				{
					animated_charater->set_walking_direction(AnimatedCharacter::up);
				}
				else if (velocity_component.get().y < 0)
				{
					animated_charater->set_walking_direction(AnimatedCharacter::down);
				}
				else if (velocity_component.get().x < 0)
				{
					animated_charater->set_walking_direction(AnimatedCharacter::left);
				}
				else if (velocity_component.get().x > 0)
				{
					animated_charater->set_walking_direction(AnimatedCharacter::right);
				}

				animated_charater->translate(Vector2(velocity_component.get().x, (velocity_component.get().y - velocity_component.get().y * 2))); //TODO: check y axes it is inverted.
				
			}
		}

		if (velocity_component.get().x != 0)
		{
			current_position->x += velocity_component.get().x;
			current_position->diffx = velocity_component.get().x;
			velocity_component.get().x = 0;
		}
		else
		{
			current_position->diffx = 0;
		}

		if (velocity_component.get().y != 0)
		{
			current_position->y += velocity_component.get().y;
			current_position->diffy = velocity_component.get().y;
			velocity_component.get().y = 0;
		}
		else
		{
			current_position->diffy = 0;
		}
	}
}