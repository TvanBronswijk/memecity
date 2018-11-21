#include "Menu.h"

namespace memecity::engine::ui::menu {

	void Menu::render()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->render();
			return;
		}
		multimedia_manager.clear_graphics();

		Vector2 position{ multimedia_manager.get_screen_width() / 2.0f, 200 };
		title_texture->set_position(position);
		multimedia_manager.render_text_texture(*title_texture);
		position.y += 50;

		int index = 0;
		for (auto& menu_item : menu_items)
		{
			menu_item->set_selected(index == selected_menu_items_index);
			auto texture = menu_item->get_texture();
			texture.translate(position);
			position.y += 30;
			multimedia_manager.render_text_texture(texture);
			index++;
		}

		multimedia_manager.render_graphics();
	}

	void Menu::set_parent(MenuItem* parent)
	{
		this->parent = parent;
	}

	void Menu::unlock()
	{
		if (parent != nullptr && !is_locked)
		{
			parent->unlock();
		}
		is_locked = false;
	}

	void Menu::lock()
	{
		is_locked = true;
	}

	void Menu::handle_up()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->handle_up();
			return;
		}

		selected_menu_items_index--;
		if (selected_menu_items_index < 0)
		{
			selected_menu_items_index = menu_items.size() - 1;
		}
	}

	void Menu::handle_down()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->handle_down();
			return;
		}

		selected_menu_items_index++;
		if (selected_menu_items_index >= menu_items.size())
		{
			selected_menu_items_index = 0;
		}
	}

	void Menu::handle_enter()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->handle_enter();
			return;
		}

		menu_items.at(selected_menu_items_index)->handle();
	}

	void Menu::handle_escape()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->handle_escape();
			return;
		}

		if (parent != nullptr)
		{
			parent->unlock();
		}
	}
}
