#include "GameManager.h"
#include "Components.h"
#include "Systems.h"

using namespace memecity::engine;
using namespace memecity::engine::ecs;

void GameManager::init()
{
	city_generator.generate(24, 24, entity_manager, multimedia_manager, _quad_tree);

	auto player_position_x = multimedia_manager.get_screen_width() / 2; 
	auto player_position_y = multimedia_manager.get_screen_height() / 2;

	auto texture = multimedia_manager.get_animated_texture(*timer, "SpriteSheet.png", 0, 0, 48, 48, 4, 0.25f, texture::AnimatedTexture::AnimationDirection::vertical);
	texture->set_position({ static_cast<float>(player_position_x), static_cast<float>(player_position_y) });
	auto builder = builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<PlayerComponent>()
		.with_component<AnimationComponent>()
		.with_component<DimensionComponent>(64.0f, 64.0f)
		.with_component<PositionComponent>(player_position_x, player_position_y)
		.with_component<VelocityComponent>()
		.with_component<DrawableComponent>(std::move(texture));

	auto& player = builder.get();


	auto position_component = player.get<PositionComponent>();
	auto dimension_component = player.get<DimensionComponent>();

	const auto player_collider = BoundaryRectangle(position_component->x, position_component->y, dimension_component->w, dimension_component->h);

	builder.with_component<ColliderComponent>(player_collider);

	auto collider_component = player.get<ColliderComponent>();

	_quad_tree.insert(collider_component->boundary_rectangle);

	auto text_texture = multimedia_manager.get_text_texture("Health: 500", "Minecraftia-Regular.ttf", 16, { 255,255,255 });
	text_texture->set_parent(&player.get<DrawableComponent>()->get_texture());
	text_texture->set_position({ 0, -30 });
	builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<DrawableComponent>(std::move(text_texture));


	//test to show an example  for a NPC
	/*auto& fighting_system = entity_manager.create_system<FightingSystem>();
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
			.with_component<DimensionComponent>(64.0f, 64.0f)
			.with_component<InteractionComponent>()
			.with_component<DrawableComponent>(std::move(texture))
			.with_component<PositionComponent>(x, y);

	}*/
	// end test	

	entity_manager.create_system<AnimationSystem>(System::draw);
	entity_manager.create_system<DrawSystem>(System::draw, multimedia_manager);
	auto& input_system = entity_manager.create_system<InputSystem>(System::update, input_manager);
	auto& move_system = entity_manager.create_system<MoveSystem>();
	auto& collider_system = entity_manager.create_system<ColliderSystem>(System::draw, _quad_tree);

	// events
	//input_system.interaction_event.bind([&](EntityManager& em, InteractionEventArgs args) { interaciton_system.on_interact(em, args); });
	//input_system.attack_event.bind([&](EntityManager& em, AttackEventArgs args) { fighting_system.on_attack(em, args); });
	collider_system.collider_event.bind([&](ecs::EntityManager& em, ColliderEventArgs args) { move_system.on_collision(em, args); });
}

void GameManager::update(float dt)
{
	entity_manager.update(System::update);
}

void GameManager::draw()
{
	entity_manager.update(System::draw);
}
