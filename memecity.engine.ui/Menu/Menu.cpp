#include "Menu.h"

namespace memecity::engine::ui::menu {

	MenuItem& Menu::add_menu_item(std::unique_ptr<MenuItem> item)
	{
		return *menu_items.emplace_back(std::move(item));
	}

	std::unique_ptr<texture::TextTexture> Menu::get_texture() const
	{
		return  multimedia_manager.get_text_texture(title, "Minecraftia-Regular.ttf", 36, { 255,255,255 });

	}

	int Menu::reset_debounce_counter()
	{
		return debounce_counter = 10;
	}

	void Menu::handle_input()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->handle_input();
			return;
		}

		input_manager.update();
		if (input_manager.is_pressed(sdl::InputKeys::Up) && debounce_counter == 0)
		{
			selected_menu_items_index--;
			if (selected_menu_items_index < 0)
			{
				selected_menu_items_index = menu_items.size() - 1;
			}
			reset_debounce_counter();
		}
		else if (input_manager.is_pressed(sdl::InputKeys::Down) && debounce_counter == 0)
		{
			selected_menu_items_index++;
			if (selected_menu_items_index >= menu_items.size())
			{
				selected_menu_items_index = 0;
			}
			reset_debounce_counter();
		}
		else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Enter) && debounce_counter == 0)
		{
			menu_items.at(selected_menu_items_index)->handle();
			reset_debounce_counter();
		}
		else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Escape) && debounce_counter == 0)
		{
			if (parent != nullptr)
			{
				parent->unlock();
			}
			reset_debounce_counter();
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

	void Menu::render()
	{
		if (is_locked)
		{
			menu_items.at(selected_menu_items_index)->render();
			return;
		}
		multimedia_manager.clear_graphics();

		Vector2 position{ multimedia_manager.get_screen_width() / 2.0f, 200 };
		auto title_texture = get_texture();
		title_texture->translate(position);
		multimedia_manager.render_text_texture(*title_texture);
		position.y += 50;

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

}