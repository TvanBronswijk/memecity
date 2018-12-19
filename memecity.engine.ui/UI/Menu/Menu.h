#ifndef _MENU_H
#define  _MENU_H
#include <vector>
#include <memory>
#include <Engine.h>
#include "MenuItem.h"

namespace memecity::engine::ui::menu {
	class Menu
	{
	private:
		static const int title_height = 50;
		static const int menu_item_height = 30;

		std::vector<std::unique_ptr<MenuItem>> menu_items;
		size_t selected_menu_items_index;
		MultimediaManager& multimedia_manager;
		bool is_locked;
		MenuItem* parent;
		std::string title;
		std::string font_path;
		std::unique_ptr<texture::TextTexture> title_texture;
		
	public:
		Menu(MultimediaManager& multimedia_manager, std::string title, std::string font_path, MenuItem* parent = nullptr)
		: selected_menu_items_index(0), multimedia_manager(multimedia_manager), is_locked(false), parent(parent), title(title), font_path(font_path)
		{
			title_texture = multimedia_manager.get_text(font_path, title, 36);
		}

		void set_parent(MenuItem* parent);

		template<class... Args>
		MenuItem& create_menu_item(Args&&... args)
		{
			static_assert(std::is_constructible<MenuItem, MultimediaManager&, Menu&, std::string, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			return *menu_items.emplace_back(std::make_unique<MenuItem>(multimedia_manager, *this, font_path, std::forward<Args>(args)...));
		}

		template<class... Args>
		MenuItem& create_read_only_menu_item(Args&&... args)
		{
			static_assert(std::is_constructible<MenuItem, MultimediaManager&, Menu&, std::string, Args..., bool>::value, "The requested type cannot be constructed from the arguments provided.");
			return *menu_items.emplace_back(std::make_unique<MenuItem>(multimedia_manager, *this, font_path, std::forward<Args>(args)..., true));
		}

		Vector2 get_position_of_item(int index)
		{
			return menu_items.at(index)->get_texture().get_position();
		}

		void render();
		void unlock();
		void lock();

		void next();
		void previous();
		void select();
		bool back();

	};
}
#endif
