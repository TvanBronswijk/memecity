#include "TimerFacade.h"

///<summary>Constructor.</summary>
TimerFacade::TimerFacade()
{
	reset();
}

///<summary>Resets the elapsed ticks.</summary>
void TimerFacade::reset()
{
	start_ticks = SDL_GetTicks();
	elapsed_ticks = 0;
	delta_time = 0.0f;
}

///<summary>Returns the current delta time.</summary>
float TimerFacade::get_delta_time() const
{
	return delta_time;
}

///<summary>Sets delta time to elapsed time since last update.</summary>
void TimerFacade::update()
{
	elapsed_ticks = SDL_GetTicks() - start_ticks;
	delta_time = elapsed_ticks * 0.001f;
}