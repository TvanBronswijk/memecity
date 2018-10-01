#include "TimerFacade.h"
#include <SDL.h>

TimerFacade::TimerFacade()
{
	Reset();
}

void TimerFacade::Reset()
{
	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;
}

float TimerFacade::DeltaTime() const
{
	return deltaTime;
}

void TimerFacade::Update()
{
	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;
}