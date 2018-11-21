#include "MenuItem.h"
#include "Menu.h"

using namespace memecity::engine;
namespace memecity::engine::ui::menu {

	MenuItem::MenuItem(MultimediaManager& multimedia_manager, InputManager& input_manager, Menu& parent, std::string text, Menu* sub_menu, std::function<void(MenuItem& menu_item)> callback)
		: multimedia_manager(multimedia_manager), input_manager(input_manager), text(text), standard_color(255, 255, 255),
		selected_color(237, 210, 4), is_selected(false), parent(parent), sub_menu(sub_menu), callback(callback)
	{
		if (sub_menu != nullptr)
		{
			sub_menu->set_parent(this);
		}
	}

	void MenuItem::set_selected(bool selected)
	{
		is_selected = selected;
	}

	std::unique_ptr<memecity::engine::texture::TextTexture> MenuItem::get_texture() const
	{
		return  multimedia_manager.get_text_texture(text, "Minecraftia-Regular.ttf", 24, is_selected ? selected_color : standard_color);
	}

	void MenuItem::handle_input()
	{
		if (sub_menu != nullptr)
		{
			sub_menu->handle_input();
		}
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
}