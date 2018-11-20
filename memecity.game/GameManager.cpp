#include "GameManager.h"
#include "Components.h"
#include "Systems.h"
#include "Menu/MenuBuilder.h"

using namespace memecity::engine;
using namespace ecs;

void GameManager::init()
{
	city_generator.generate(50, 50, entity_manager, multimedia_manager);

	auto texture = multimedia_manager.get_animated_texture(*timer, "SpriteSheet.png", 0, 0, 48, 48, 4, 0.25f, texture::AnimatedTexture::AnimationDirection::vertical);
	texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });
	auto& player = builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<PlayerComponent>()
		.with_component<AnimationComponent>()
		//.with_component<ColliderComponent>(64.0f, 64.0f)
		.with_component<PositionComponent>(multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2)
		.with_component<VelocityComponent>()
		.with_component<DrawableComponent>(std::move(texture))
		.get();


	auto text_texture = multimedia_manager.get_text_texture("Health: 500", "Minecraftia-Regular.ttf", 16, { 255,255,255 });
	text_texture->set_parent(&player.get<DrawableComponent>()->get_texture());
	text_texture->set_position({ 0, -30 });
	builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<DrawableComponent>(std::move(text_texture));


	//test to show an example  for a NPC
	auto& fighting_system = entity_manager.create_system<FightingSystem>();
	entity_manager.create_system<AISystem>();
	auto& interaciton_system = entity_manager.create_system<InteractionSystem>();

	for (size_t i = 0; i < 1; i++) {
		float x = 10 * i;
		float y = 10 * i;

		auto texture = multimedia_manager.get_animated_texture(*timer, "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, texture::AnimatedTexture::AnimationDirection::vertical);
		texture->set_position({ x , y + (multimedia_manager.get_screen_height() - (y * 2)) });

		builder::EntityBuilder(entity_manager)
			.create_entity()
			.with_component<AIComponent>()
			.with_component<VelocityComponent>()
			.with_component<LevelComponent>()
			.with_component<HealthComponent>(100)
			.with_component<StatsComponent>()
			.with_component<InteractionComponent>()
			.with_component<DrawableComponent>(std::move(texture))
			.with_component<PositionComponent>(x, y);

	}
	// end test

	entity_manager.create_system<AnimationSystem>(System::draw);
	entity_manager.create_system<DrawSystem>(System::draw, multimedia_manager);
	auto& input_system = entity_manager.create_system<InputSystem>(System::update, input_manager);
	auto& move_system = entity_manager.create_system<MoveSystem>();
	//auto& collider_system = entity_manager.create_system<ColliderSystem>();

	// events
	input_system.interaction_event.bind([&](EntityManager& em, InteractionEventArgs args) { interaciton_system.on_interact(em, args); });
	input_system.attack_event.bind([&](EntityManager& em, AttackEventArgs args) { fighting_system.on_attack(em, args); });
	//collider_system.collider_event.bind([&](ecs::EntityManager& em, ColliderEventArgs args) { move_system.on_collision(em, args); });

	auto& mm = multimedia_manager;
	auto enable_fullscreen = [&](menu::MenuItem& menu_item) { mm.set_fullscreen(true); };
	auto disable_fullscreen = [&](menu::MenuItem& menu_item) { mm.set_fullscreen(false); };

	advanced_graphics_menu = menu::MenuBuilder(multimedia_manager, input_manager)
		.create_menu()
		.with_back_menu_item()
		.get_menu();

	settings_menu = menu::MenuBuilder(multimedia_manager, input_manager)
		.create_menu()
		.with_menu_item("Enable fullscreen", enable_fullscreen)
		.with_menu_item("Disable fullscreen", disable_fullscreen)
		.with_menu_item("Advanced Graphics", advanced_graphics_menu.get())
		.with_back_menu_item()
		.get_menu();


	menu = menu::MenuBuilder(multimedia_manager, input_manager)
		.create_menu()
		.with_menu_item("Start Game")
		.with_menu_item("Settings",	settings_menu.get())
		.with_menu_item("Credits")
		.with_menu_item("Exit")
		.get_menu();
}

void GameManager::update(float dt)
{
	menu->handle_input();
	entity_manager.update(System::update);
}

void GameManager::draw()
{
	entity_manager.update(System::draw);

	menu->render();
}
