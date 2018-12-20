#include "LevelChangeState.h"
#include <UI/Menu/MenuBuilder.h>
#include "..\..\Assets.h"
#include "LoadingState.h"
#include "..\LevelBuilder.h"
#include "..\Components\PlayerComponent.h"
#include "..\Builder\QuestBuilder.h"
#include "..\GameSaver.h"

LevelChangeState::LevelChangeState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, memecity::engine::ecs::EntityManager & em, int& map_number, std::string save_location)
	:State(sm), _context(&gc), _entity_manager(&em), map_number(map_number), save_location(save_location)
{
	auto& player = em.get_entities_by_type("player").front().get();
	GameSaver().save(em, gc, save_location, map_number);


	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Station", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Go to Next City", nullptr, [&](auto& _) {
		Point start;

		player.get<PlayerComponent>()->_stories = QuestBuilder(_context->get_multimedia_manager(), em, start).get_all_stories();
		player.get<PlayerComponent>()->_stories[0].active = false;
		
		next<LoadingState>(*_context,
			[&](auto& ctx, auto& listener) {
			auto entities = em.query_all_entities().where([](const auto& e) { return e.type != "player";  }).to_vector();
			listener.set_text("Clearing State...");
			listener.set_max_value(100.0f);
			listener.set_current_value(0.0f);
			for (const auto& entity : entities) {
				em.remove_entity(entity);
				listener.increase_current_value(100.0f / entities.size());
			}
			back(); });
		
		next<LoadingState>(*_context,
			[&](auto& ctx, auto& listener) { start = LevelBuilder(ctx, 1, 128, 128, false, false, this->save_location).build(em, listener, map_number); back(); });//TODO tobi, hier het nummer van de map meegeven
		player.get<BaseComponent>()->location = start;
		back();
	})
		.with_menu_item("Go to Last City", nullptr, [&](auto& _) {
		Point start;
		next<LoadingState>(*_context,
			[&](auto& ctx, auto& listener) {
			auto entities = em.query_all_entities().where([](const auto& e) { return e.type != "player";  }).to_vector();
			listener.set_text("Clearing State...");
			listener.set_max_value(100.0f);
			listener.set_current_value(0.0f);
			for (const auto& entity : entities) {
				em.remove_entity(entity);
				listener.increase_current_value(100.0f / entities.size());
			}
			back(); });

		next<LoadingState>(*_context,
			[&](auto& ctx, auto& listener) { start = LevelBuilder(ctx, 1, 128, 128, true, false, this->save_location).build(em, listener, map_number); back(); });//TODO tobi, hier het nummer van de map meegeven
		player.get<BaseComponent>()->location = start;
		back();
	})
		.get_menu();
}

void LevelChangeState::update(float dt)
{
	auto& input_manager = _context->get_input_manager();
	if (input_manager.is_pressed(input::UP))
	{
		menu->next();
	}
	else if (input_manager.is_pressed(input::DOWN))
	{
		menu->previous();
	}
	else if (input_manager.is_pressed(input::ENTER))
	{
		menu->select();
	}
}

void LevelChangeState::draw()
{
	menu->render();
}
