#ifndef _GAME_STATE_H
#define  _GAME_STATE_H
#include <Engine.h>
#include <ECS.h>
#include "..\Generate.h"
#include "..\Factory\NPCFactory.h"

struct GameState : public memecity::engine::state::State {
private:
	NPCFactory npc_factory{ get_context().multimedia_manager, get_context().timer, entity_manager };
	memecity::engine::ecs::EntityManager entity_manager;
	generate::CityGenerator city_generator;
public:
	GameState(memecity::engine::state::StateMachine& sm, memecity::engine::state::StateContext& sc)
		: State(sm, sc){}
	void init() override;
	void update(float dt) override;
	void draw() override;
	~GameState() = default;
};

#endif
