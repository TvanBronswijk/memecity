#ifndef _MENU_ITEM_H
#define  _MENU_ITEM_H
#include <functional>
#include "Engine/SDL/Wrappers/Color.h"
#include "Engine/Textures/TextTexture.h"
#include "Engine/MultimediaManager.h"
#include "Engine/InputManager.h"

namespace menu {
	class Menu;
	class MenuItem
	{
	private:
		memecity::engine::MultimediaManager& multimedia_manager;
		memecity::engine::InputManager& input_manager;
		std::string text;
		memecity::engine::sdl::Color standard_color;
		memecity::engine::sdl::Color selected_color;
		bool is_selected;
		Menu& parent;
		Menu* sub_menu;
		int debounce_counter;
		std::function<void(MenuItem& menu_item)> callback;
	public:
		MenuItem(memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::InputManager& input_manager, std::string text, Menu& parent, Menu* sub_menu = nullptr, std::function<void(MenuItem& menu_item)> callback = nullptr);
			
		void set_selected(bool selected);
		std::unique_ptr<memecity::engine::texture::TextTexture> get_texture() const;
		void handle_input();
		void render() const;
		void unlock() const;
		void handle();
	};
};
#endif