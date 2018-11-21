#include "MenuBuilder.h"

namespace memecity::engine::ui::menu {

	MenuBuilder& MenuBuilder::create_menu(std::string title)
	{
		menu = std::make_unique<Menu>(multimedia_manager, input_manager, title);
		return *this;
	}

	MenuBuilder& MenuBuilder::with_back_menu_item()
	{
		return with_menu_item("<-Back", nullptr, [&](MenuItem& menu_item) { menu_item.unlock(); });
	}

	std::unique_ptr<Menu> MenuBuilder::get_menu()
	{
		return std::move(menu);
	}
}