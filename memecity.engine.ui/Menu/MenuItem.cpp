#include "MenuItem.h"
#include "Menu.h"

using namespace memecity::engine;
namespace memecity::engine::ui::menu {

	MenuItem::MenuItem(MultimediaManager& multimedia_manager, InputManager& input_manager, Menu& parent, std::string text, Menu* sub_menu, std::function<void(MenuItem& menu_item)> callback)
		: multimedia_manager(multimedia_manager), input_manager(input_manager), text(text),
			is_selected(false), parent(parent), sub_menu(sub_menu), callback(callback)
	{
		standard_texture = multimedia_manager.get_text_texture(text, "Minecraftia-Regular.ttf", 24, { 255, 255, 255});
		selected_texture = multimedia_manager.get_text_texture(text, "Minecraftia-Regular.ttf", 24, { 237, 210, 4 });
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

	void MenuItem::handle_up() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->handle_up();
		}
	}

	void MenuItem::handle_down() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->handle_down();
		}
	}

	void MenuItem::handle_enter() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->handle_enter();
		}
	}

	void MenuItem::handle_escape() const
	{
		if (sub_menu != nullptr)
		{
			sub_menu->handle_escape();
		}
	}
}
