#include "GameLoader.h"
#include "Generate.h"
#include "Builder/QuestBuilder.h"
#include "Components.h"
#include "Systems.h"
#include "..\Assets.h"

using namespace memecity::engine::ecs;
using namespace memecity::engine::ui;

void GameLoader::build(memecity::engine::ecs::EntityManager& em, loading::LoadingBar::Listener& listener)
{
	listener
		.set_max_value(100.0f)
		.set_current_value(0.0f);

	listener.set_text("Loading Map");
	create_map(em, listener);
	listener.set_text("Loading NPCs");
	create_npcs(em, listener);	
	listener.set_text("Loading Player");
	create_player(em, listener);	
	listener.set_text("Loading Complete!");
}

void GameLoader::create_map(EntityManager& em, loading::LoadingBar::Listener& listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();
	generate::models::City city = generate::CityGenerator(_map_width, _map_height).generate();
	for (int y = city.begin.y; y < city.end.y; y++) {
		for (int x = city.begin.x; x < city.end.x; x++) {
			auto& character = city(x, y);
#ifdef DEBUG
			std::cout << character;
#endif
			auto& builder = em.create_entity("tile")
				.with_component<BaseComponent>(multimedia_manager.get_texture(generate::models::char_to_asset(character)), x * 64.0f, y * 64.0f, 64.0f, 64.0f);
			if (character == 'W' || character == 'w') {
				auto base_component = builder.get().get<BaseComponent>();
				builder.with_component<ColliderComponent>(BoundaryRectangle{ base_component->location.x, base_component->location.y, base_component->w, base_component->h });
			}
			listener.increase_current_value(75.0f / (_map_width * _map_height));
		}
	}
	listener.set_current_value(75.0f);
}

void GameLoader::create_npcs(EntityManager& em, loading::LoadingBar::Listener& listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();
	auto& timer = _context->get_timer();
	generate::NPCGenerator(multimedia_manager, em).generate_random_npc(1, 220, 0, 1);
	listener.increase_current_value(20.0f);
}

void GameLoader::create_player(EntityManager& em, loading::LoadingBar::Listener& listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();

	auto texture = multimedia_manager.get_texture(assets::spritesheets::HUMAN_MALE_1, 0, 0, 48, 48, 4, 0.25f, memecity::engine::texture::AnimatedTexture::AnimationDirection::vertical);
	texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });

	auto builder = em.create_entity("player")
		.with_component<BaseComponent>(std::move(texture), 0.0f, 0.0f, 48.0f, 48.0f)
		.with_component<PlayerComponent>(QuestBuilder(multimedia_manager, em).getAllStories())
		.with_component<StatsComponent>(1,3,1,1,1,1,1)
		.with_component<AnimationComponent>()
		.with_component<HealthComponent>(100, nullptr)
		.with_component<VelocityComponent>();
	auto base_component = builder.get().get<BaseComponent>();
	builder.with_component<ColliderComponent>(BoundaryRectangle(base_component->location.x, base_component->location.y, base_component->w, base_component->h));
	listener.increase_current_value(5.0f);
}


