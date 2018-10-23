#include "GameManager.h"

bool GameManager::init()
{

	if (multimedia_manager->init())
	{
		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(12, 12, entity_manager, multimedia_manager);

		auto entity = entity_manager->create_entity();
		entity_manager->register_component(new PlayerComponent(entity));
		entity_manager->register_component(new VelocityComponent(entity));
		auto position_component = new PositionComponent(entity, multimedia_manager->get_screen_width() / 2, multimedia_manager->get_screen_height() / 2);
		entity_manager->register_component(position_component);

		auto d_component = new DrawableComponent(entity);

		animated_character = multimedia_manager->get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		d_component->texture = animated_character;
		d_component->texture->set_position({ position_component->x, position_component->y });
		entity_manager->register_component(d_component);

		//test to show an example  for a NPC
		auto IS = new InteractionSystem(multimedia_manager);
		entity_manager->register_system(new AISystem());
		entity_manager->register_system(IS);
		interaction_event = new InteractionEvent();
		interaction_event->subscribe(IS);

		entity_manager->register_system(new InputSystem(input_manager, interaction_event));
		entity_manager->register_system(new DrawSystem(multimedia_manager));
		entity_manager->register_system(new MoveSystem());
		return true;
	}
	return false;
}
void GameManager::handle()
{
	timer->update();
	if (timer->get_delta_time() >= 1.0f / 60)
	{
		input_manager->update();
		entity_manager->update();
		animated_character->update();
		
		if (input_manager->is_pressed(ONE))
		{
			Entity* npc = entity_manager->create_entity();
			entity_manager->register_component(new AIComponent(npc));
			entity_manager->register_component(new VelocityComponent(npc));
			entity_manager->register_component(new LevelComponent(npc));
			entity_manager->register_component(new HealthComponent(npc));
			entity_manager->register_component(new StatsComponent(npc));
			entity_manager->register_component(new PositionComponent(npc, 250, 250));
			entity_manager->register_component(new InteractionComponent(npc));
			
			auto sprite = multimedia_manager->get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
			sprite->set_position(Vector2(250.0, 250.0));

			auto DC = new DrawableComponent(npc);
			entity_manager->register_component(DC);
			DC->texture = sprite;
		}
		
		if (input_manager->is_pressed(ESCAPE))
		{
			multimedia_manager->pause_background_music();
		}
		animated_character->set_walking_direction(AnimatedCharacter::idle);
		if (input_manager->is_pressed(LEFT))
		{
			animated_character->set_walking_direction(AnimatedCharacter::left);
		}

		if (input_manager->is_pressed(RIGHT))
		{
			animated_character->set_walking_direction(AnimatedCharacter::right);
		}

		if (input_manager->is_pressed(UP))
		{
			animated_character->set_walking_direction(AnimatedCharacter::up);
		}

		if (input_manager->is_pressed(DOWN))
		{
			animated_character->set_walking_direction(AnimatedCharacter::down);
		}
		
		timer->reset();
	}
}

