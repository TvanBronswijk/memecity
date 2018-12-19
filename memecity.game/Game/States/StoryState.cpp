#include "StoryState.h"
#include "..\..\Assets.h"
#include "..\Input.h"
#include "..\Quest\Quest.h"
#include "..\Quest\Task.h"

StoryState::StoryState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, std::vector<Story> stories)
	: State(sm), _context(&gc)
{
	this->stories = stories;
	this->depth = 0;
	make_menu(gc);

}

void StoryState::make_menu(GameManager::GameContext & gc) {
	auto builder = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager());
	builder.create_menu("Stories", assets::fonts::DEFAULT_FONT);
	std::vector<Story>::iterator it = stories.begin() + depth;

	auto& story = *it;
	if (story.active) {
		builder.with_read_only_menu_item("******************************");
		if (story.completed) {
			builder.with_read_only_menu_item("Completed");
			builder.with_read_only_menu_item("Story: " + story.description);
		}
		else {
			builder.with_read_only_menu_item("Story: " + story.description);
			builder.with_read_only_menu_item("Quest: " + story.quests.front().description);
			builder.with_read_only_menu_item("Task:	" + story.quests.front().tasks.front().description);
		}
		builder.with_read_only_menu_item("******************************");
		builder.with_read_only_menu_item(" ");
	}
	if (it++ != stories.end()) {
		auto& story2 = *it++;
		if (story2.active) {
			builder.with_read_only_menu_item("******************************");
			if (story.completed) {
				builder.with_read_only_menu_item("Completed");
				builder.with_read_only_menu_item("Story: " + story2.description);
			}
			else {
				builder.with_read_only_menu_item("Story: " + story2.description);
				builder.with_read_only_menu_item("Quest: " + story2.quests.front().description);
				builder.with_read_only_menu_item("Task:	" + story2.quests.front().tasks.front().description);
			}
			builder.with_read_only_menu_item("******************************");
			builder.with_read_only_menu_item(" ");
		}
	}
	if (depth * 2 < stories.size() -1)
		builder.with_menu_item("next", nullptr, [&](auto& menu_item) { depth += 2; make_menu(gc); });
	else if (depth + 1 < stories.size() - 1)
		builder.with_menu_item("next", nullptr, [&](auto& menu_item) { depth += 1; make_menu(gc); });
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
