#include "StoryState.h"
#include "..\..\Assets.h"
#include "..\Input.h"
#include "..\Components\StoryComponent.h"
#include "..\Components\questComponent.h"
#include "..\Components\taskComponent.h"

StoryState::StoryState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, std::vector<const memecity::engine::ecs::Entity*> stories)
	: State(sm), _context(&gc)
{

	auto builder = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager());
	builder.create_menu("Stories", assets::fonts::DEFAULT_FONT);
	for (std::vector<const memecity::engine::ecs::Entity*>::iterator it = stories.begin(); it != stories.end(); ++it) {
		auto story = (*it)->get<StoryComponent>();
		if (story->active) {
			builder.with_read_only_menu_item("******************************");
			if (story->completed) {
				builder.with_read_only_menu_item("Completed");
				builder.with_read_only_menu_item("Story: " + story->description);
			}
			else {
				builder.with_read_only_menu_item("Story: " + story->description);
				builder.with_read_only_menu_item("Quest: " + story->_quests.front()->description);
				builder.with_read_only_menu_item("Task:	" + story->_quests.front()->_tasks.front()->description);
			}
			builder.with_read_only_menu_item("******************************");
			builder.with_read_only_menu_item(" ");
		}
	}
	builder.with_menu_item("Back", nullptr, [&](auto& menu_item) { back(); });

	menu = builder.get_menu();
}

void StoryState::on_load()
{

}

void StoryState::update(float dt)
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

void StoryState::draw()
{
	menu->render();
}

void StoryState::on_enter()
{

}

void StoryState::on_exit()
{

}
