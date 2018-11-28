#include "MenuItem.h"
#include "Menu.h"

using namespace memecity::engine;
namespace memecity::engine::ui::menu {

	MenuItem::MenuItem(MultimediaManager& multimedia_manager, Menu& parent, std::string text, Menu* sub_menu, std::function<void(MenuItem& menu_item)> callback, bool read_only)
		:  text(text), is_selected(false), is_read_only(read_only), parent(parent), sub_menu(sub_menu), callback(callback)
	{
		standard_texture = multimedia_manager.get_text_texture(text, Menu::default_font, 24, { 255, 255, 255});
		selected_texture = multimedia_manager.get_text_texture(text, Menu::default_font, 24, { 237, 210, 4 });
		if (sub_menu != nullptr)
		{
			sub_menu->set_parent(this);
		}
	}

	void MenuItem::set_selected(bool selected)
	{
		is_selected = selected;
	}

	texture::TextTexture& MenuItem::get_texture() const
	{
		return  is_selected ? *selected_texture : *standard_texture;
	}

	bool MenuItem::get_read_only() const
	{
		return  is_read_only;
	}

	void MenuItem::render() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->render();
		}
	}

	void MenuItem::unlock() const
	{
		parent.unlock();
	}

	void MenuItem::handle()
	{
		if (callback != nullptr)
		{
			callback(*this);
		}
		else if (sub_menu != nullptr)
		{
			parent.lock();
		}
	}

	void MenuItem::next() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->next();
		}
	}

	void MenuItem::previous() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->previous();
		}
	}

	void MenuItem::select() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->select();
		}
	}

	void MenuItem::back() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->back();
		}
	}
}
