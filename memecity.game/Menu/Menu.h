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
		std::string title;
		std::unique_ptr<memecity::engine::texture::TextTexture> get_texture() const;
		int reset_debounce_counter();
		MenuItem& add_menu_item(std::unique_ptr<MenuItem> item);


	public:
		Menu(memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::InputManager& input_manager, std::string title, MenuItem* parent = nullptr) 
		: selected_menu_items_index(0), multimedia_manager(multimedia_manager), input_manager(input_manager), is_locked(false), parent(parent), debounce_counter(reset_debounce_counter()), title(title) {}
		void set_parent(MenuItem* parent);

		template<class C, class... Args>
		C& create_menu_item(Args&&... args)
		{
			static_assert(std::is_convertible<C*, MenuItem*>::value, "This function can only construct concrete subclasses of MenuItem");
			static_assert(std::is_constructible<C, memecity::engine::MultimediaManager&, memecity::engine::InputManager&, Menu&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			return add_menu_item(std::make_unique<MenuItem>(multimedia_manager, input_manager, *this, std::forward<Args>(args)...));
		}

		void handle_input();
		void render();
		void unlock();
		void lock();
	};
}
#endif