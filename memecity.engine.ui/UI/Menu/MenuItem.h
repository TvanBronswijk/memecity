﻿#ifndef _MENU_ITEM_H
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
		bool is_read_only;
		Menu& parent;
		Menu* sub_menu;
		std::function<void(MenuItem& menu_item)> callback;
		std::unique_ptr<texture::TextTexture> standard_texture;
		std::unique_ptr<texture::TextTexture> selected_texture;

	public:
		MenuItem(MultimediaManager& multimedia_manager, Menu& parent, std::string font_path, std::string text, Menu* sub_menu = nullptr, std::function<void(MenuItem& menu_item)> callback = nullptr, bool read_only = false);
		MenuItem(MultimediaManager& multimedia_manager, Menu& parent, std::string font_path, std::string text, bool read_only) : MenuItem(multimedia_manager, parent, font_path, text, nullptr, nullptr, read_only) {}

		void set_selected(bool selected);
		texture::TextTexture& get_texture() const;
		std::string get_text() { return text; };
		bool get_read_only() const;
		void render() const;
		void unlock() const;
		void handle();

		void next() const;
		void previous() const;
		void select() const;
		bool back() const;
	};
};
#endif