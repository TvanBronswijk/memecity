#include "Menu.h"


void menu::Menu::add_menu_item(std::unique_ptr<MenuItem> item)
{
	menu_items.emplace_back(std::move(item));
}

void menu::Menu::handle_input()
{
	if (is_locked)
	{
		menu_items.at(selected_menu_items_index)->handle_input();
		return;
	}

	input_manager.update();
	if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Up) && debounce_counter == 0)
	{
		selected_menu_items_index--;
		if (selected_menu_items_index < 0)
		{
			selected_menu_items_index = menu_items.size()-1;
		}
		debounce_counter=100;
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Down) && debounce_counter == 0)
	{
		selected_menu_items_index++;
		if (selected_menu_items_index >= menu_items.size())
		{
			selected_menu_items_index = 0;
		}
		debounce_counter=100;
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Enter) && debounce_counter == 0)
	{
		menu_items.at(selected_menu_items_index)->handle();
		debounce_counter = 100;
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Escape) && debounce_counter == 0)
	{
		if (parent != nullptr)
		{
			parent->unlock();
		}
		debounce_counter = 100;
	}
	else
	{
		debounce_counter--;
		if (debounce_counter < 0)
		{
			debounce_counter = 0;
		}
	}
}

void menu::Menu::render()
{
	if (is_locked)
	{
		menu_items.at(selected_menu_items_index)->render();
		return;
	}
	multimedia_manager.clear_graphics();

	Vector2 position {multimedia_manager.get_screen_width()/2.0f, 200};

	int index = 0;
	for (auto& menu_item : menu_items)
	{
		menu_item->set_selected(index == selected_menu_items_index);
		auto texture = menu_item->get_texture();
		texture->translate(position);
		position.y += 30;
		multimedia_manager.render_text_texture(*texture);
		index++;
	}

	multimedia_manager.render_graphics();
}

void menu::Menu::set_parent(MenuItem* parent)
{
	this->parent = parent;
}

void menu::Menu::unlock()
{
	is_locked = false;
}

void menu::Menu::lock()
{
	is_locked = true;
}


