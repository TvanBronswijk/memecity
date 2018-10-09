#include "TimerFacade.h"

/**
 * Constructor
 */
TimerFacade::TimerFacade()
{
	reset();
}

/**
 * Resets the elapsed ticks
 */
void TimerFacade::reset()
{
	start_ticks = SDL_GetTicks();
	elapsed_ticks = 0;
	delta_time = 0.0f;
}

/**
 * Returns the current delta time
 */
float TimerFacade::get_delta_time() const
{
	return delta_time;
}

/**
 * Sets delta time to elapsed time since last update
 */
void TimerFacade::update()
{
	elapsed_ticks = SDL_GetTicks() - start_ticks;
	delta_time = elapsed_ticks * 0.001f;
}