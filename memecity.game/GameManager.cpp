#include "GameManager.h"

bool GameManager::init()
{
	if (multimedia_manager->init())
	{
		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(24, 24, entity_manager, multimedia_manager);

		const auto entity = entity_manager->create_entity();

		entity_manager->register_component(new PlayerComponent(entity));
		entity_manager->register_component(new VelocityComponent(entity));
		entity_manager->register_component(new AnimationComponent(entity));

		const auto position_component = new PositionComponent(entity, multimedia_manager->get_screen_width() / 2, multimedia_manager->get_screen_height() / 2);
		entity_manager->register_component(position_component);

		const auto animated_texture = multimedia_manager->get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedTexture::AnimationDirection::vertical);
		auto d_component = new DrawableComponent(entity);
		
		d_component->texture = animated_texture;
		d_component->texture->set_position({ position_component->x, position_component->y });
		entity_manager->register_component(d_component);

		entity_manager->register_system(new InputSystem(input_manager));
		entity_manager->register_system(new AnimationSystem());
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
		timer->reset();
	}
}

