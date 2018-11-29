#include "Menu.h"

namespace memecity::engine::ui::menu {

	void Menu::render()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->render();
			return;
		}

		if (menu_items.at(selected_menu_items_index)->get_read_only())
		{
			previous();
		}

		float render_offset = multimedia_manager.get_screen_height() - 2 * title_height - menu_items.size() * menu_item_height;
		if (render_offset > 200)
		{
			render_offset = 200;
		}
		if (render_offset < 50)
		{
			render_offset = 50;
		}

		Vector2 position{ multimedia_manager.get_screen_width() / 2.0f, render_offset };
		title_texture->set_position(position);
		multimedia_manager.render_text(*title_texture);
		position.y += title_height;

		int index = 0;
		for (auto& menu_item : menu_items)
		{
			menu_item->set_selected(index == selected_menu_items_index);
			auto& texture = menu_item->get_texture();
			texture.set_position(position);
			position.y += menu_item_height;
			multimedia_manager.render_text(texture);
			index++;
		}
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

	void Menu::next()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->next();
			return;
		}

		if (selected_menu_items_index == 0)
		{
			selected_menu_items_index = menu_items.size() - 1;
		}
		else 
		{
			selected_menu_items_index--;
		}
		if (menu_items.at(selected_menu_items_index)->get_read_only())
		{
			next();
		}
	}

	void Menu::previous()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->previous();
			return;
		}

		selected_menu_items_index++;
		if (selected_menu_items_index >= menu_items.size())
		{
			selected_menu_items_index = 0;
		}
		if (menu_items.at(selected_menu_items_index)->get_read_only())
		{
			previous();
		}
	}

	void Menu::select()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->select();
			return;
		}

		menu_items.at(selected_menu_items_index)->handle();
	}

	void Menu::back()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->back();
			return;
		}

		if (parent != nullptr)
		{
			parent->unlock();
		}
	}
}
