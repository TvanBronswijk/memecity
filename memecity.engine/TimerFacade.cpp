#include "TimerFacade.h"
#include <SDL.h>


TimerFacade::TimerFacade()
{
	Reset();
}

void TimerFacade::Reset()
{
	startTicks = SDL_GetTicks();
	elaspsedTicks = 0;
	deltaTime = 0.0f;
}

float TimerFacade::DeltaTime()
{
	return deltaTime;
}

void TimerFacade::Update()
{
	elaspsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elaspsedTicks * 0.001f;
}