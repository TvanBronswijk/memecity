#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::init()
{
	city_generator.generate(50, 50, entity_manager, multimedia_manager);
	auto& entity = entity_manager.create_entity();
	entity_manager.create_component<PlayerComponent>(entity);
	entity_manager.create_component<VelocityComponent>(entity);
	auto& position_component = entity_manager.create_component<PositionComponent>(entity, multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2);
	auto& d_component = entity_manager.create_component<DrawableComponent>(entity);
	auto animated_character = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
	d_component.texture = animated_character;
	d_component.texture->set_position({ position_component.x, position_component.y });

	entity_manager.create_system<InputSystem>(input_manager);
	entity_manager.create_system<DrawSystem>(multimedia_manager);
	entity_manager.create_system<MoveSystem>();

	//test to show an example  for a NPC
	auto FS = new FightingSystem();
	auto IS = new InteractionSystem(multimedia_manager);
	entity_manager->register_system(FS);
	entity_manager->register_system(new AISystem());
	entity_manager->register_system(IS);
	entity_manager->register_system(new DrawSystem(multimedia_manager));
	entity_manager->register_system(new MoveSystem());

	for (size_t i = 0; i < 1; i++) {
		Entity* npc = entity_manager->create_entity();
		entity_manager->register_component(new AIComponent(npc));
		entity_manager->register_component(new VelocityComponent(npc));
		entity_manager->register_component(new LevelComponent(npc));
		entity_manager->register_component(new HealthComponent(100, npc));
		entity_manager->register_component(new StatsComponent(npc));
		PositionComponent* npc_position = new PositionComponent(npc, 10 * i, 10 * i);
		entity_manager->register_component(npc_position);
		entity_manager->register_component(new InteractionComponent(npc));
		std::shared_ptr<AnimatedCharacter> animated_npc = multimedia_manager->get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		auto DC = new DrawableComponent(npc);
		entity_manager->register_component(DC);
		DC->texture = animated_npc;
		DC->texture->set_position({ npc_position->x , npc_position->y + (multimedia_manager->get_screen_height() - (npc_position->y * 2)) });
	}
	// end test	

	// events
	interaction_event = new InteractionEvent(); // mem leak
	attack_event = new AttackEvent(); // mem leak
	interaction_event->subscribe(IS);
	attack_event->subscribe(FS);

	entity_manager->register_system(new InputSystem(input_manager, interaction_event, attack_event));

}

void GameManager::handle()
{
	entity_manager.update();
}
