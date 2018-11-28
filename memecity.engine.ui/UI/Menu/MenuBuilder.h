#ifndef _MENU_BUILDER_H
#define _MENU_BUILDER_H

#include "MenuItem.h"
#include "Menu.h"
#include <Engine.h>

namespace memecity::engine::ui::menu {

	class MenuBuilder
	{
	private:
		MultimediaManager& multimedia_manager;
		std::unique_ptr<Menu> menu;
	public:
		MenuBuilder(MultimediaManager& multimedia_manager) 
		: multimedia_manager(multimedia_manager) {}
		MenuBuilder& create_menu(std::string title, std::string font_path);

		template<class... Args>
		MenuBuilder& with_menu_item(Args&&... args)
		{
			menu->create_menu_item(std::forward<Args>(args)...);
			return *this;
		}

		template<class... Args>
		MenuBuilder& with_read_only_menu_item(Args&&... args)
		{
			menu->create_read_only_menu_item(std::forward<Args>(args)...);
			return *this;
		}
		MenuBuilder& with_back_menu_item();
		std::unique_ptr<Menu> get_menu();
	};
};
#endif;
