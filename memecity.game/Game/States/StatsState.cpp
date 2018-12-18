#include "StatsState.h"
#include "..\..\Assets.h"
#include "..\Input.h"

StatsState::StatsState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, StatsComponent& stats)
	: State(sm), _context(&gc)
{
	make_new_menu(stats);
}
void StatsState::make_new_menu(StatsComponent& stats){
	menu = memecity::engine::ui::menu::MenuBuilder(get_context().get_multimedia_manager())
		.create_menu("Stats", assets::fonts::DEFAULT_FONT)
		.with_read_only_menu_item("available points: " + std::to_string(stats.available_points))
		.with_read_only_menu_item(" ")
		.with_menu_item("Strenght: " + std::to_string(stats.strength), nullptr, [&](auto& menu_item) { increase(stats, 1);  })
		.with_menu_item("Perception: " + std::to_string(stats.perception), nullptr, [&](auto& menu_item) { increase(stats, 2);  })
		.with_menu_item("Luck: " + std::to_string(stats.luck), nullptr, [&](auto& menu_item) { increase(stats, 3);  })
		.with_menu_item("Intelligence: " + std::to_string(stats.intelligence), nullptr, [&](auto& menu_item) { increase(stats, 4);  })
		.with_menu_item("Endurance: " + std::to_string(stats.endurance), nullptr, [&](auto& menu_item) { increase(stats, 5);  })
		.with_menu_item("Charisma: " + std::to_string(stats.charisma), nullptr, [&](auto& menu_item) { increase(stats, 6);  })
		.with_menu_item("Agility: " + std::to_string(stats.agility), nullptr, [&](auto& menu_item) { increase(stats, 7);  })
		.with_read_only_menu_item(" ")
		.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) { back(); })
		.get_menu();
}

void StatsState::increase(StatsComponent& stats, int id){
	if (stats.available_points > 0) {
		switch (id)
		{
		case 1:
			stats.strength++;
			break;
		case 2:
			stats.perception++;
			break;
		case 3:
			stats.luck++;
			break;
		case 4:
			stats.intelligence++;
			break;
		case 5:
			stats.endurance++;
			break;
		case 6:
			stats.charisma++;
			break;
		case 7:
			stats.agility++;
			break;
		}

		stats.available_points--;
		make_new_menu(stats);

	}
}

void StatsState::on_load()
{

}

void StatsState::update(float dt)
{
	auto& input_manager = _context->get_input_manager();
	if (input_manager.is_pressed(input::UP))
	{
		menu->next();
	}
	else if (input_manager.is_pressed(input::DOWN))
	{
		menu->previous();
	}
	else if (input_manager.is_pressed(input::ENTER))
	{
		menu->select();
	}
}

void StatsState::draw()
{
	menu->render();
}

void StatsState::on_enter()
{

}

void StatsState::on_exit()
{

}
