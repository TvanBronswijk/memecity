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
		std::vector<std::unique_ptr<MenuItem>> menu_items;
		int selected_menu_items_index;
		MultimediaManager& multimedia_manager;
		bool is_locked;
		MenuItem* parent;
		std::string title;
		std::unique_ptr<texture::TextTexture> title_texture;

	public:
		Menu(MultimediaManager& multimedia_manager, std::string title, MenuItem* parent = nullptr) 
		: selected_menu_items_index(0), multimedia_manager(multimedia_manager), is_locked(false), parent(parent), title(title)
		{
			title_texture = multimedia_manager.get_text_texture(title, "Minecraftia-Regular.ttf", 36, { 255,255,255 });
		}

		void set_parent(MenuItem* parent);

		template<class... Args>
		MenuItem& create_menu_item(Args&&... args)
		{
			static_assert(std::is_constructible<MenuItem, MultimediaManager&, Menu&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			return *menu_items.emplace_back(std::make_unique<MenuItem>(multimedia_manager, *this, std::forward<Args>(args)...));
		}

		void render();
		void unlock();
		void lock();

		void next();
		void previous();
		void select();
		void back();

	};
}
#endif