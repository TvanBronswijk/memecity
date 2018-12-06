#include "GameLoader.h"
#include "Generate.h"
#include "Components.h"
#include "Systems.h"
#include "..\Assets.h"

using namespace memecity::engine::ecs;
using namespace memecity::engine::ui;

EntityManager GameLoader::build(loading::LoadingBar::Listener& listener)
{
	EntityManager em;
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

	return std::move(em);
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
			em.create_entity("tile")
				.with_component<BaseComponent>(multimedia_manager.get_texture(generate::models::char_to_asset(character)), x * 64.0f, y * 64.0f, 64.0f, 64.0f);
			listener.increase_current_value(75.0f / (_map_width * _map_height));
		}
	}
	listener.set_current_value(75.0f);
}

void GameLoader::create_npcs(EntityManager& em, loading::LoadingBar::Listener& listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();
	auto& timer = _context->get_timer();
	generate::NPCGenerator(multimedia_manager, em).generate(1, 10, 10);
	listener.increase_current_value(10.0f);
}

void GameLoader::create_player(EntityManager& em, loading::LoadingBar::Listener& listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();

	auto texture = multimedia_manager.get_texture(assets::spritesheets::HUMAN_MALE_1, 0, 0, 48, 48, 4, 0.25f, memecity::engine::texture::AnimatedTexture::AnimationDirection::vertical);
	texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2.0f, static_cast<float>(multimedia_manager.get_screen_height()) / 2.0f });
	
	em.create_entity("player")
		.with_component<BaseComponent>(std::move(texture), 0.0f, 0.0f, 48.0f, 48.0f)
		.with_component<PlayerComponent>()
		.with_component<AnimationComponent>()
		.with_component<VelocityComponent>();
	listener.increase_current_value(10.0f);
}


