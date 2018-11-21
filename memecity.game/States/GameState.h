#ifndef _GAME_STATE_H
#define  _GAME_STATE_H
#include <Engine.h>
#include <ECS.h>
#include "..\Generate.h"
#include "..\NPCFactory.h"

struct GameState : public memecity::engine::state::State {
private:
	memecity::engine::MultimediaManager& multimedia_manager;
	memecity::engine::InputManager& input_manager;
	memecity::engine::sdl::TimerFacade& timer;
	NPCFactory npc_factory{ multimedia_manager, timer, entity_manager };

	memecity::engine::ecs::EntityManager entity_manager;
	generate::CityGenerator city_generator;
public:
	GameState(memecity::engine::state::StateMachine& sm, memecity::engine::MultimediaManager& mmm, memecity::engine::InputManager& im, memecity::engine::sdl::TimerFacade& tf)
		: State(sm), multimedia_manager(mmm), input_manager(im), timer(tf) {}
	void init() override;
	void update(float dt) override;
	void draw() override;
	~GameState() = default;
};

#endif
