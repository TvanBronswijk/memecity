#include "MenuItem.h"
#include "Menu.h"

menu::MenuItem::MenuItem(memecity::engine::MultimediaManager& multimedia_manager,
	memecity::engine::InputManager& input_manager, std::string text, Menu& parent, Menu* sub_menu)
	: multimedia_manager(multimedia_manager), input_manager(input_manager), text(text), standard_color(255, 255, 255), selected_color(237, 210, 4), is_selected(false), parent(parent), sub_menu(sub_menu), debounce_counter(100)
{
	if (sub_menu !=nullptr)
	{
		sub_menu->set_parent(this);
	}
}


void menu::MenuItem::set_selected(bool selected)
{
	is_selected = selected;
}

std::unique_ptr<memecity::engine::texture::TextTexture> menu::MenuItem::get_texture()
{
	return  multimedia_manager.get_text_texture(text, "Minecraftia-Regular.ttf", 24, is_selected ? selected_color : standard_color);
}

void menu::MenuItem::handle_input()
{
	if (sub_menu != nullptr)
	{
		sub_menu->handle_input();
	}
	else {
		input_manager.update();
		if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Escape) && debounce_counter == 0)
		{
			parent.unlock();
			debounce_counter = 100;
		}
		else
		{
			debounce_counter--;
			if (debounce_counter < 0)
			{
				debounce_counter = 0;
			}
		}
	}
}

void menu::MenuItem::render()
{
	if (sub_menu != nullptr)
	{
		sub_menu->render();
	}
}

void menu::MenuItem::unlock()
{
	parent.unlock();
}

void menu::MenuItem::handle()
{
	parent.lock();
}
