#ifndef _MENU_ITEM_H
#define  _MENU_ITEM_H
#include <functional>
#include <Engine.h>

namespace memecity::engine::ui::menu {
	class Menu;
	class MenuItem
	{
	private:
		MultimediaManager& multimedia_manager;
		InputManager& input_manager;
		std::string text;
		sdl::Color standard_color;
		sdl::Color selected_color;
		bool is_selected;
		Menu& parent;
		Menu* sub_menu;
		std::function<void(MenuItem& menu_item)> callback;
		
	public:
		MenuItem(MultimediaManager& multimedia_manager, InputManager& input_manager, Menu& parent, std::string text, Menu* sub_menu = nullptr, std::function<void(MenuItem& menu_item)> callback = nullptr);
			
		void set_selected(bool selected);
		std::unique_ptr<texture::TextTexture> get_texture() const;
		void handle_input();
		void render() const;
		void unlock() const;
		void handle();
	};
};
#endif