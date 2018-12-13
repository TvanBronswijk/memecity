#include "TimerFacade.h"

namespace memecity::engine::sdl {
	TimerFacade::TimerFacade()
	{
		reset();
	}

	void TimerFacade::reset()
	{
		start_ticks = SDL_GetTicks();
		elapsed_ticks = 0;
		delta_time = 0.0f;
	}

	float TimerFacade::get_delta_time() const
	{
		return delta_time;
	}

	void TimerFacade::update()
	{
		elapsed_ticks = SDL_GetTicks() - start_ticks;
		delta_time = elapsed_ticks * 0.001f;
	}
}
