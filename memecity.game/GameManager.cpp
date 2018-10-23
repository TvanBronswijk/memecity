#include "GameManager.h"

bool GameManager::init()
{

	if (multimedia_manager->init())
	{
	
		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(128, 128, entity_manager, multimedia_manager);

		auto entity = entity_manager->create_entity();
		entity_manager->register_component(new PlayerComponent(entity));
		entity_manager->register_component(new VelocityComponent(entity));
		auto position_component = new PositionComponent(entity, multimedia_manager->get_screen_width() / 2, multimedia_manager->get_screen_height() / 2);
		entity_manager->register_component(position_component);

		auto d_component = new DrawableComponent(entity);
		d_component->texture = multimedia_manager->get_texture("red.bmp", 0, 0, 32, 32);
		d_component->texture->set_position({ position_component->x, position_component->y});
		entity_manager->register_component(d_component);

		entity_manager->register_system(new InputSystem(input_manager));
		entity_manager->register_system(new DrawSystem(multimedia_manager));
		entity_manager->register_system(new MoveSystem());

		// Test to show an example how to create a animated character
		animated_character = multimedia_manager->get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		animated_character->set_position(Vector2(200.0, 200.0));

		const auto animated_character_entity = entity_manager->create_entity();
		const auto drawable_component = new DrawableComponent(animated_character_entity);
		entity_manager->register_component(drawable_component);
		entity_manager->register_system(new DrawSystem(multimedia_manager));
		drawable_component->texture = animated_character;

		//test to show an example  for a NPC
		auto IS = new InteractionSystem();
		entity_manager->register_system(new AISystem());
		entity_manager->register_system(new MoveSystem());
		entity_manager->register_system(IS);
		interaction_event = new InteractionEvent();
		interaction_event->subscribe(IS);

		return true;
	}
	return false;
}
void GameManager::handle()
{
	timer->update();
	if (timer->get_delta_time() >= 1.0f / 60)
	{
		animated_character->update();

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

		if (input_manager->is_pressed(LEFT))
		{
			animated_character->set_walking_direction(AnimatedCharacter::left);
			animated_character->translate(Vector2(-60.0f, 0.0f) * timer->get_delta_time());
		}

		if (input_manager->is_pressed(RIGHT))
		{
			animated_character->set_walking_direction(AnimatedCharacter::right);
			animated_character->translate(Vector2(+60.0f, 0.0f) * timer->get_delta_time());
		}

		if (input_manager->is_pressed(UP))
		{
			animated_character->set_walking_direction(AnimatedCharacter::up);
			animated_character->translate(Vector2(0.0f, -60.0f) * timer->get_delta_time());
		}

		if (input_manager->is_pressed(DOWN))
		{
			animated_character->set_walking_direction(AnimatedCharacter::down);
			animated_character->translate(Vector2(0.0f, +60.0f) * timer->get_delta_time());
		}
		//test for interaction with NPC
		if (input_manager->is_pressed(INTERACTION))
		{
			auto position = animated_character->get_position();
			auto vector = entity_manager->get_components_of_type(AIComponent::COMPONENT_TYPE);
			for (auto & element : vector) {
				PositionComponent* xy = (PositionComponent*)entity_manager->get_component_of_entity(element->entity_id, PositionComponent::COMPONENT_TYPE);
				if ((position.x + 15) >= xy->x && (position.x - 15) <= xy->x) {
					if ((position.y + 15) >= xy->y && (position.y - 15) <= xy->y) {
						auto args = InteractionEventArgs(element->entity_id);

						interaction_event->fire(entity_manager, args);
					}
				}
			}
		}


		timer->reset();
	}
}

