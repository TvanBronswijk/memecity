#ifndef _MENU_H
#define  _MENU_H
#include <vector>
#include <memory>
#include "Engine/MultimediaManager.h"
#include "Engine/InputManager.h"
#include "MenuItem.h"

namespace menu {
	class Menu
	{
	private:
		std::vector<std::unique_ptr<MenuItem>> menu_items;
		int selected_menu_items_index;
		memecity::engine::MultimediaManager& multimedia_manager;
		memecity::engine::InputManager& input_manager;
		bool is_locked;
		MenuItem* parent;
		int debounce_counter;
	public:
		Menu(memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::InputManager& input_manager, MenuItem* parent = nullptr) 
		: selected_menu_items_index(0), multimedia_manager(multimedia_manager), input_manager(input_manager), is_locked(false), parent(parent), debounce_counter(100) {}

		void set_parent(MenuItem* parent);
		MenuItem& add_menu_item(std::unique_ptr<MenuItem> item);
		MenuItem& create_menu_item(std::string text);
		MenuItem& create_menu_item(std::string text, Menu* sub_menu);
		MenuItem& create_menu_item(std::string text, std::function<void(MenuItem& menu_item)> callback);
		void handle_input();
		void render();
		void unlock();
		void lock();
	};
}
#endif