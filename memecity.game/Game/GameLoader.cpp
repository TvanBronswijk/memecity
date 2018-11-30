#include "GameLoader.h"
#include "Generate.h"
#include "Components.h"
#include "Systems.h"
#include "Systems/HudSystem.h"

using namespace memecity::engine::ecs;
using namespace memecity::engine::ui;

EntityManager GameLoader::build(loading::LoadingBar::Listener& listener)
{
	EntityManager em;
	listener.set_max_value(100.0f);

	listener
		.set_current_value(0.0f)
		.set_text("Loading Map");
	create_map(em, listener);
	listener
		.set_text("Loading NPCs");
	create_npcs(em, listener);	
	listener
		.set_text("Loading Player");
	create_player(em, listener);
	listener
		.set_text("Loading Systems");
	create_systems(em, listener);	
	listener
		.set_text("Loading Complete!");

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
			std::string filename;
			switch (character)
			{
			case '-':
				filename = "Sprites/Tiles/gray.bmp";
				break;
			case  'W':
				filename = "Sprites/Tiles/brown.bmp";
				break;
			case  'w':
				filename = "Sprites/Tiles/blue.bmp";
				break;
			case 'g':
				filename = "Sprites/Tiles/green.bmp";
				break;
			default:
				std::cout << "ERROR!" << std::endl;
			}

			auto texture = multimedia_manager.get_texture(filename);
			texture->set_position({ x * 64.0f, y * 64.0f });

			auto& builder = builder::EntityBuilder(em)
				.create_entity()
				.with_component<DrawableComponent>(std::move(texture))
				.with_component<PositionComponent>(x * 64.0f, y * 64.0f);

			if (character == 'W' || character == 'w')
			{
				builder
					.with_component<ColliderComponent>(64.0f, 64.0f);
			}
			listener.increase_current_value(75.0f / (_map_width * _map_height));
		}
#ifdef DEBUG
		std::cout << '\n';
#endif
	}
	listener.set_current_value(75.0f);
}

void GameLoader::create_npcs(EntityManager& em, loading::LoadingBar::Listener& listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();
	auto& timer = _context->get_timer();
	generate::NPCGenerator(multimedia_manager, timer, em).generate(1, 10, 10);
	listener.increase_current_value(10.0f);
}

void GameLoader::create_player(EntityManager& em, loading::LoadingBar::Listener& listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();
	auto& timer = _context->get_timer();

	auto texture = multimedia_manager.get_animated_texture(timer, "Spritesheets/SpriteSheet.png", 0, 0, 48, 48, 4, 0.25f, memecity::engine::texture::AnimatedTexture::AnimationDirection::vertical);
	texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });
	
	builder::EntityBuilder(em)
		.create_entity()
		.with_component<PlayerComponent>()
		.with_component<AnimationComponent>()
		.with_component<ColliderComponent>(48.0f, 48.0f)
		.with_component<PositionComponent>(0,0)
		.with_component<VelocityComponent>()
		.with_component<DrawableComponent>(std::move(texture))
		.get();
	listener.increase_current_value(10.0f);
}

void GameLoader::create_systems(EntityManager& em, loading::LoadingBar::Listener& listener)
{
	auto& multimedia_manager = _context->get_multimedia_manager();

	auto& hud_system = em.create_system<HudSystem>();
	auto& draw_system =			em.create_system<DrawSystem>(System::draw, multimedia_manager);
	auto& animation_system =	em.create_system<AnimationSystem>(System::draw);
	auto& input_system =		em.create_system<InputSystem>(System::update, *_context);
	auto& move_system =			em.create_system<MoveSystem>();
	auto& collider_system =		em.create_system<ColliderSystem>();
	auto& ai_system =			em.create_system<AISystem>();
	auto& fighting_system =		em.create_system<FightingSystem>(System::draw, multimedia_manager);
	auto& interaction_system =	em.create_system<InteractionSystem>(System::draw, multimedia_manager);
	auto& overlay_system =		em.create_system<OverlaySystem>(System::draw, multimedia_manager);


	
	
	eventing::bind(move_system.move_event, &animation_system, &AnimationSystem::on_move);
	eventing::bind(input_system.interaction_event, &interaction_system, &InteractionSystem::on_interact);
	eventing::bind(input_system.attack_event, &fighting_system, &FightingSystem::on_attack);
	eventing::bind(collider_system.collider_event, &move_system, &MoveSystem::on_collision);

	eventing::bind(fighting_system.health_event, &hud_system, &HudSystem::on_health_changed);

	listener.increase_current_value(5.0f);
}


