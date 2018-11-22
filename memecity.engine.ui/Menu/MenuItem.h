#ifndef _MENU_ITEM_H
#define  _MENU_ITEM_H
#include <functional>
#include <Engine.h>

namespace memecity::engine::ui::menu {
	class Menu;
	class MenuItem
	{
	private:
		std::string text;
		bool is_selected;
		Menu& parent;
		Menu* sub_menu;
		std::function<void(MenuItem& menu_item)> callback;
		std::unique_ptr<texture::TextTexture> standard_texture;
		std::unique_ptr<texture::TextTexture> selected_texture;

	public:
		MenuItem(MultimediaManager& multimedia_manager, Menu& parent, std::string text, Menu* sub_menu = nullptr, std::function<void(MenuItem& menu_item)> callback = nullptr);
			
		void set_selected(bool selected);
		texture::TextTexture& get_texture() const;
		void render() const;
		void unlock() const;
		void handle();

		void next() const;
		void previous() const;
		void select() const;
		void back() const;
	};
};
#endif