#ifndef _STATE_CONTEXT_H
#define _STATE_CONTEXT_H
#include "Engine/SDL/TimerFacade.h"
#include "Engine/InputManager.h"
#include "Engine/MultimediaManager.h"
#include "MemeEngine.h"


namespace memecity::engine::state {

	struct StateContext
	{
		QuadTree& quad_tree;
		MultimediaManager& multimedia_manager;
		InputManager& input_manager;
		sdl::TimerFacade& timer;

		StateContext(MultimediaManager& mm, InputManager& im, sdl::TimerFacade& t, QuadTree& quad_tree)
			: multimedia_manager(mm), input_manager(im), timer(t), quad_tree(quad_tree) {}
		StateContext(MemeEngine& engine)
			: multimedia_manager(engine.get_multimedia_manager()), input_manager(engine.get_input_manager()), timer(engine.get_timer()), quad_tree(engine.get_quad_tree()) {}
	};
}
#endif
