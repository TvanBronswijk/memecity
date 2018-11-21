#ifndef _STATE_CONTEXT_H
#define _STATE_CONTEXT_H
#include "Engine/SDL/TimerFacade.h"
#include "Engine/InputManager.h"
#include "Engine/MultimediaManager.h"
#include "MemeEngine.h"


namespace memecity::engine::state {

	struct StateContext
	{
		MultimediaManager& multimedia_manager;
		InputManager& input_manager;
		sdl::TimerFacade& timer;

		StateContext(MultimediaManager& mm, InputManager& im, sdl::TimerFacade& t)
			: multimedia_manager(mm), input_manager(im), timer(t) {}
		StateContext(MemeEngine& engine)
			: multimedia_manager(engine.get_multimedia_manager()), input_manager(engine.get_input_manager()), timer(engine.get_timer()) {}
	};
}
#endif
