#include "StatsState.h"
#include "..\..\Assets.h"
#include "..\Input.h"

StatsState::StatsState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc, memecity::engine::ui::overlay::Overlay& hud, StatsComponent& stats)
	: State(sm), _context(&gc)
{
	make_new_menu(hud, stats);
}
void StatsState::make_new_menu(memecity::engine::ui::overlay::Overlay& hud, StatsComponent& stats){
	menu = memecity::engine::ui::menu::MenuBuilder(get_context().get_multimedia_manager())
		.create_menu("Stats", assets::fonts::DEFAULT_FONT)
		.with_read_only_menu_item("available points: " + std::to_string(stats.available_points))
		.with_read_only_menu_item(" ")
		.with_menu_item("Strenght: " + std::to_string(stats.strength), nullptr, [&](auto& menu_item) { increase(hud,stats, SPECIAL::Strenght);  })
		.with_menu_item("Perception: " + std::to_string(stats.perception), nullptr, [&](auto& menu_item) { increase(hud,stats, SPECIAL::Perception);  })
		.with_menu_item("Luck: " + std::to_string(stats.luck), nullptr, [&](auto& menu_item) { increase(hud,stats, SPECIAL::Luck);  })
		.with_menu_item("Intelligence: " + std::to_string(stats.intelligence), nullptr, [&](auto& menu_item) { increase(hud,stats, SPECIAL::Intelligence);  })
		.with_menu_item("Endurance: " + std::to_string(stats.endurance), nullptr, [&](auto& menu_item) { increase(hud, stats, SPECIAL::Endurance);  })
		.with_menu_item("Charisma: " + std::to_string(stats.charisma), nullptr, [&](auto& menu_item) { increase(hud,stats, SPECIAL::Charisma);  })
		.with_menu_item("Agility: " + std::to_string(stats.agility), nullptr, [&](auto& menu_item) { increase(hud, stats, SPECIAL::Agility);  })
		.with_read_only_menu_item(" ")
		.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) { back(); })
		.get_menu();
}

void StatsState::increase(memecity::engine::ui::overlay::Overlay& hud, StatsComponent& stats, SPECIAL type){
	if (stats.available_points > 0) {
		switch (type)
		{
		case SPECIAL::Strenght:
			stats.strength++;
			hud.update("S", "S: " + std::to_string(stats.strength));
			break;
			case SPECIAL::Perception:
			stats.perception++;
			hud.update("P", "P: " + std::to_string(stats.perception));
			break;
		case SPECIAL::Luck:
			stats.luck++;
			hud.update("L", "L: " + std::to_string(stats.luck));
			break;
		case SPECIAL::Intelligence:
			stats.intelligence++;
			hud.update("I", "I: " + std::to_string(stats.intelligence));
			break;
		case SPECIAL::Endurance:
			stats.endurance++;
			hud.update("E", "E: " + std::to_string(stats.endurance));
			break;
		case SPECIAL::Charisma:
			stats.charisma++;
			hud.update("C", "C: " + std::to_string(stats.charisma));
			break;
		case SPECIAL::Agility:
			stats.agility++;
			hud.update("A", "A: " + std::to_string(stats.agility));
			break;
		}

		stats.available_points--;
		make_new_menu(hud, stats);

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
