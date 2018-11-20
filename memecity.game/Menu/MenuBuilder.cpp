#include "MenuBuilder.h"
#include "Menu.h"

using namespace menu;

MenuBuilder& MenuBuilder::create_menu()
{
	menu = std::make_unique<Menu>(multimedia_manager, input_manager);
	return *this;
}

MenuBuilder& MenuBuilder::with_menu_item(std::string text)
{
	menu->create_menu_item(text);
	return *this;
}

MenuBuilder& MenuBuilder::with_menu_item(std::string text, Menu* sub_menu)
{
	menu->create_menu_item(text, sub_menu);
	return *this;
}

MenuBuilder& MenuBuilder::with_menu_item(std::string text,
	std::function<void(MenuItem& menu_item)> callback)
{
	menu->create_menu_item(text, callback);
	return *this;
}

MenuBuilder& MenuBuilder::with_back_menu_item()
{
	menu->create_menu_item("<-Back", [](MenuItem menu_item) {menu_item.unlock(); });
	return *this;
}

std::unique_ptr<Menu> MenuBuilder::get_menu()
{
	return std::move(menu);
}
