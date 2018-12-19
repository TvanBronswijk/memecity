#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include <Engine\State.h>
#include <ECS.h>
#include <UI\Overlay\Overlay.h>
#include "..\Systems.h"
#include "..\..\GameManager.h"
#include "..\..\Assets.h"

struct GameState : memecity::engine::state::State {

private:
	GameManager::GameContext* _context;
	memecity::engine::ecs::EntityManager entity_manager;
	memecity::engine::ecs::SystemPool system_pool;
	memecity::engine::ui::overlay::Overlay _hud;
	bool _load_from_file;
	std::string _save_location;

public:
	GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, bool load_from_file = false, std::string save_location = "")
		: State(sm), _context(&gc), _hud(_context->get_multimedia_manager(), _context->get_multimedia_manager().get_texture(assets::sprites::DARK_BACKGROUND, 0, 0, _context->get_multimedia_manager().get_screen_width(), 100), 0, 0), _load_from_file(load_from_file),_save_location(save_location)
	{
		_hud.create_overlay_text_item("HEALTH", "Health", 16, 100.0f, 20.0f);
		_hud.create_overlay_bar_item("HEALTHVALUE", 100, 20, 150, 12, 100, 200, memecity::engine::sdl::Color(255, 0, 0), memecity::engine::sdl::Color(0, 255, 0));
		_hud.create_overlay_text_item("SCORE", "Score:100", 16, 100, 40);
		_hud.create_overlay_text_item("EXP", "Exp:100", 16, 100, 60);

		_hud.create_overlay_text_item("S", "S: 1", 16, 400, 16);
		_hud.create_overlay_text_item("P", "P: 1", 16, 400, 32);
		_hud.create_overlay_text_item("E", "E: 1", 16, 400, 48);
		_hud.create_overlay_text_item("C", "C: 1", 16, 400, 64);
		_hud.create_overlay_text_item("I", "I: 1", 16, 500, 16);
		_hud.create_overlay_text_item("A", "A: 1", 16, 500, 32);
		_hud.create_overlay_text_item("L", "L: 1", 16, 500, 48);

		_hud.create_overlay_text_item("BLIKCOIN", "BlikCoins: 0", 16, 650, 16);

		_hud.create_overlay_text_item("INVENTORY"," Inventory" , 16, 1000, 16);
		_hud.create_overlay_text_item("SIZE"," Size = 1" , 16, 1000, 38);
		_hud.create_overlay_text_item("SELECTED"," Selected = 1" , 16, 1000, 62);
		//images on the side

	}
	~GameState()
	{
		auto& engine = _context->get_engine();
		
		engine.disable_calculate_fps();
		engine.disable_display_gamespeed();
	};
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif
