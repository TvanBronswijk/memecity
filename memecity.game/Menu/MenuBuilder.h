#ifndef _MENU_BUILDER_H
#define _MENU_BUILDER_H

#include "Engine/MultimediaManager.h"
#include "Engine/InputManager.h"
#include "MenuItem.h"
#include "Menu.h"

namespace menu {

	class MenuBuilder
	{
	private:
		memecity::engine::MultimediaManager& multimedia_manager;
		memecity::engine::InputManager& input_manager;
		std::unique_ptr<Menu> menu;
	public:
		MenuBuilder(memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::InputManager& input_manager) 
		: multimedia_manager(multimedia_manager), input_manager(input_manager) {}
		MenuBuilder& create_menu(std::string title);

		template<class C, class... Args>
		MenuBuilder& with_menu_item(Args&&... args)
		{
			menu->create_menu_item<MenuItem>(std::forward<Args>(args)...);
			return *this;
		}

		MenuBuilder& with_back_menu_item();
		std::unique_ptr<Menu> get_menu();
	};
};
#endif;
